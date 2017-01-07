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
#include <cstdint>

namespace beemaster {

    class RocksStorage : public acu::Storage {
    public:
        rocksdb::DB* Database;
        rocksdb::Options Options;

        RocksStorage(std::string db_name);
        ~RocksStorage();

        void Persist(const acu::IncomingAlert *alert);

        template<typename count_t>
        bool Increment(const std::string key, const count_t value);
    };
}

#endif //ACU_IMPL_ROCKSSTORAGE_H
