/* rocks_storage.h
 * ACU Implementation
 *
 * <src/rocks_storage.cc>
 */

#include "rocks_storage.h"

namespace beemaster {

    /// Initialise and open DB
    RocksStorage::RocksStorage(std::string db_name)
        : acu::Storage::Storage(db_name) {
            options.create_if_missing = true;
            rocksdb::Status status = rocksdb::DB::Open(options, db_name, &Database);
            assert(status.ok());
        }

    void RocksStorage::Persist(const acu::IncomingAlert *alert) {

    }
}
