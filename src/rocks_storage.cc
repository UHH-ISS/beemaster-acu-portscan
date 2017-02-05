/* rocks_storage.h
 * ACU Implementation
 *
 * <src/rocks_storage.cc>
 */

#include "rocks_storage.h"
#include "utils.h"
#include <rocksdb/merge_operator.h>


namespace beemaster {

    char delimiter = '|';

    RocksStorage::RocksStorage(std::string db_name)
        : acu::Storage::Storage(db_name) {

        options = rocksdb::Options();
        writeOptions = rocksdb::WriteOptions();

        writeOptions.sync = true;

        options.create_if_missing = true;
        options.IncreaseParallelism();
        options.OptimizeLevelStyleCompaction();
        rocksdb::Status status = rocksdb::DB::Open(options, db_name, &database);
        //assert(status.ok());
    }

    // Gracefully closes DB
    RocksStorage::~RocksStorage() {
        delete database;
    }

    void RocksStorage::Persist(const acu::IncomingAlert *alert) {
        this->Append(alert->destination_ip(), std::to_string(alert->destination_port()));

        auto key = "date/" + alert->destination_ip();
        database->Put(writeOptions, key, this->time_to_string(alert->timestamp()));
    }

    bool RocksStorage::Append(const std::string key, const std::string value){
        auto existing = this->Get(key);
        if (existing.empty()) {
            return database->Put(writeOptions, key, value).ok();
        } else if(!contains_string(existing, value, delimiter)) {
            return database->Put(writeOptions, key, existing + delimiter + value).ok();
        }
        return true;
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
