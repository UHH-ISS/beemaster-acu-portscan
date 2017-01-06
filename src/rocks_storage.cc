/* rocks_storage.h
 * ACU Implementation
 *
 * <src/rocks_storage.cc>
 */

#include "rocks_storage.h"
#include <rocksdb/merge_operator.h>
#include <cstdlib>
#include <cstring>

namespace beemaster {
    class AlertMergeOperator : public rocksdb::AssociativeMergeOperator {
        public:
            /// Gives the client a way to express the read -> modify -> write semantics
            ///
            /// key:           (IN) The key that's associated with this merge operation.
            /// existing_value:(IN) null indicates the key does not exist before this op
            /// value:         (IN) the value to update/merge the existing_value with
            /// new_value:    (OUT) Client is responsible for filling the merge result
            ///                     here. The string that new_value is pointing
            ///                     to will be empty.
            /// logger:        (IN) Client could use this to log errors during merge.
            ///
            /// Return true on success.
            /// All values passed in will be client-specific values. So if this method
            /// returns false, it is because client specified bad data or there was
            /// internal corruption. The client should assume that this will be treated
            /// as an error by the library.
            virtual bool Merge(const rocksdb::Slice& key,
                               const rocksdb::Slice* existing_value,
                               const rocksdb::Slice& value,
                               std::string* new_value,
                               rocksdb::Logger* logger) const override {
                size_t current_size = existing_value != nullptr ? existing_value->size() : 0;
                auto add_size = value.size();
                auto new_size = current_size + add_size;

                char *new_mem = (char*)std::malloc(new_size);
                if (existing_value != nullptr)
                    if (!std::memcpy(new_mem, existing_value->data(), current_size))
                        return false;
                if (!std::memcpy(new_mem + current_size, value.data(), add_size))
                    return false;

                // TODO CHECK MEMORY BEHAVIOUR (leaks)

                *new_value = new_mem;   // TODO as if...

                return true;
            }

            virtual const char* Name() const override { return "AlertMergeOperator"; }
    };

    /// Initialise and open DB
    ///
    /// @param db_name  The path for the database
    RocksStorage::RocksStorage(std::string db_name)
        : acu::Storage::Storage(db_name) {
            Options.create_if_missing = true;
            Options.merge_operator.reset(new AlertMergeOperator);
            // TODO what about unified read/writeOptions?
            rocksdb::Status status = rocksdb::DB::Open(Options, db_name, &Database);
            assert(status.ok());
        }

    // Gracefully closes DB
    RocksStorage::~RocksStorage() {
        delete Database;
    }

    void RocksStorage::Persist(const acu::IncomingAlert *alert) {
        // insert for source
        auto key = "srcIP:" + alert->source_ip();
        Persist(key, rocksdb::Slice((char*)alert, sizeof(acu::IncomingAlert)));
        // insert for destination
        key = "destIP:" + alert->destination_ip();
        Persist(key, rocksdb::Slice((char*)alert, sizeof(acu::IncomingAlert)));
        // insert for topic
        key = "topic:" + *alert->topic;
        Persist(key, rocksdb::Slice((char*)alert, sizeof(acu::IncomingAlert)));
    }

    void RocksStorage::Persist(const rocksdb::Slice& key, const rocksdb::Slice& value) {
        Database->Merge(rocksdb::WriteOptions(), key, value);
    }
}
