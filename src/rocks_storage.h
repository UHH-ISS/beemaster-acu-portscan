/* rocks_storage.h
 * ACU Implementation
 *
 * Provide a interface to RocksDB as an implementation of
 * abstract Storage class.
 *
 * @author: 1wilkens, 1jost
 */

#ifndef ACU_IMPL_ROCKSSTORAGE_H
#define ACU_IMPL_ROCKSSTORAGE_H

#include <acu/storage.h>
#include <rocksdb/db.h>

namespace beemaster {

    class RocksStorage : public acu::Storage {
    public:
        rocksdb::DB* Database;
        rocksdb::Options Options;

        RocksStorage(std::string db_name);
        ~RocksStorage();

        void Persist(const acu::IncomingAlert *alert);

        void Persist(const rocksdb::Slice& key, const rocksdb::Slice& value);
    };
}

#endif //ACU_IMPL_ROCKSSTORAGE_H
