/* rocks_storage.h
 * ACU Implementation
 *
 * <src/rocks_storage.cc>
 */

#include "rocks_storage.h"
#include "utils.h"
#include <rocksdb/merge_operator.h>


namespace beemaster {

    const char delimiter = '|';

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
        database->Put(writeOptions, key, time_to_string(alert->timestamp()));
    }

    bool RocksStorage::Append(const std::string key, const std::string value){
        auto existing = this->Get(key);
        if (existing.empty()) {
            return database->Put(writeOptions, key, value).ok();
        } else if(!contains_string(existing, value, delimiter)) {
            auto insert = existing + delimiter + value;
            auto status = database->Put(writeOptions, key, insert);
            return status.ok();
        }
        return true;
    }

    std::string RocksStorage::Get(const std::string key) {
        std::string str = "";
        database->Get(rocksdb::ReadOptions(), key, &str);
        return str;
    }

    bool RocksStorage::Delete(const std::string key) {
        auto status = database->Delete(writeOptions, key);
        return status.ok();
    }

    rocksdb::Iterator* RocksStorage::GetIterator() {
        return database->NewIterator(rocksdb::ReadOptions());
    }
}
