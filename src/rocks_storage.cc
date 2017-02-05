/* rocks_storage.h
 * ACU Implementation
 *
 * <src/rocks_storage.cc>
 */

#include "rocks_storage.h"
#include <rocksdb/merge_operator.h>


namespace beemaster {

    const char delimeter = '|';

    class SetMergeOperator : public rocksdb::AssociativeMergeOperator {
    public:
        SetMergeOperator(char delimeter)
                : delimeter(delimeter) {
        }
        virtual bool Merge(const rocksdb::Slice& key, const rocksdb::Slice* existing_value,
                           const rocksdb::Slice& value, std::string* new_value, rocksdb::Logger* logger)
        const override {
            if (!existing_value) {
                // No existing_value. Set *new_value = value
                new_value->assign(value.data(),value.size());
                return true;
            } else if (existing_value->ToString().find(value.ToString()) != std::string::npos) {
                return false;
            }
            else {
                // Generic append (existing_value != null).
                // Reserve *new_value to correct size, and apply concatenation.
                new_value->reserve(existing_value->size() + 1 + value.size());
                new_value->assign(existing_value->data(), existing_value->size());
                new_value->append(1, delimeter);
                new_value->append(value.data(), value.size());
                return true;
            }
        }
        virtual const char* Name() const override { return "SetMergeOperator"; }
    private:
        char delimeter;
    };

    RocksStorage::RocksStorage(std::string db_name)
        : acu::Storage::Storage(db_name) {
            options.create_if_missing = true;
            options.merge_operator.reset(new SetMergeOperator(delimeter));
            rocksdb::Status status = rocksdb::DB::Open(options, db_name, &database);
            //assert(status.ok());
        }

    // Gracefully closes DB
    RocksStorage::~RocksStorage() {
        delete database;
    }

    void RocksStorage::Persist(const acu::IncomingAlert *alert) {
        this->Append(alert->destination_ip(), (char*)alert->destination_port());

        database->Put(rocksdb::WriteOptions(), "date" + delimeter +  alert->destination_ip(),
                      this->time_to_string(alert->timestamp()));
    }

    bool RocksStorage::Append(const std::string key, const std::string value){
        rocksdb::Status status = database->Merge(rocksdb::WriteOptions(), key, value);
        return status.ok();
    }

    std::string RocksStorage::Get(const std::string key) {
        std::string str = "";
        database->Get(rocksdb::ReadOptions(), key, &str);
        return str;
    }

    rocksdb::Iterator* RocksStorage::GetIterator() {
        return database->NewIterator(rocksdb::ReadOptions());
    }

    std::string RocksStorage::increment_minutes(const std::chrono::time_point<std::chrono::system_clock> ts,
                                                uint16_t interval) {
        auto ts_inc = ts + std::chrono::minutes(interval);
        return this->time_to_string(ts_inc);
    }

    std::string RocksStorage::time_to_string(const std::chrono::time_point<std::chrono::system_clock> ts) {
        auto value = std::chrono::duration_cast<std::chrono::milliseconds>(ts.time_since_epoch());
        return std::to_string(value.count());
    }
}
