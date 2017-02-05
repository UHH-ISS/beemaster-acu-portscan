/* rocks_storage.h
 * ACU Implementation
 *
 * Provide a interface to RocksDB as an implementation of
 * abstract Storage class.
 *
 * @author: 0ortmann, 1wilkens
 */

#ifndef ACU_IMPL_ROCKSSTORAGE_H
#define ACU_IMPL_ROCKSSTORAGE_H

#include <acu/storage.h>
#include <rocksdb/db.h>
#include <cstdint>

namespace beemaster {

    class RocksStorage : public acu::Storage {
    public:
        rocksdb::DB* database;
        rocksdb::Options options;
        rocksdb::WriteOptions writeOptions;

        /// Initialise and open DB
        ///
        /// @param db_name  The path for the database
        RocksStorage(std::string db_name);
        virtual ~RocksStorage();

        /// Persist an alert
        void Persist(const acu::IncomingAlert *alert);


        /// Appends the given *value* to values currently nested under *key*.
        ///
        /// @param key      The key which will be set
        /// @param value    The value to set
        ///
        /// @return         Success boolean
        bool Append(const std::string key, const std::string value);

        /// Get the value of *key*.
        ///
        /// @param key      The key which value will be returned
        ///
        /// @return         The stored value
        std::string Get(const std::string key);

        /// Returns the Iterator over the rocksdb, which allows for key-value
        /// traversal:
        ///
        /// ```
        /// for (it->SeekToFirst(); it->Valid(); it->Next()) {
        ///   ... it->key(); ... it->value();
        /// }
        /// delete it;
        /// ```
        /// Be aware, that the value is a rocksdb::Slice here. Cast via
        /// `*(count_t*)it->value().data()
        rocksdb::Iterator* GetIterator();

    private:
        /// Increments the given date by the specified interval and returns the result as string representation
        std::string increment_minutes(std::chrono::time_point<std::chrono::system_clock> ts, uint16_t interval);
        std::string time_to_string(std::chrono::time_point<std::chrono::system_clock> ts);
    };
}

#endif //ACU_IMPL_ROCKSSTORAGE_H
