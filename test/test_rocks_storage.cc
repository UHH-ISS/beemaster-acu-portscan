/* test_rocks_storage.cc
 * ACU Implementation (test)
 *
 * Test functionality of RocksStorage
 *
 * @author: 1jost
 */

#include "catch.hpp"

#include <rocks_storage.h>
#include <iostream>

TEST_CASE("Testing RocksStorage initialisation", "[rocks_storage]") {
    // TODO FIXME XXX DIRTY AF
    std::system("rm -rf /tmp/test_storage");
    auto storage = new beemaster::RocksStorage("/tmp/test_storage");

    delete storage;
}

TEST_CASE("Test RocksStorage write operations", "[rocks_storage]") {
    std::system("rm -rf /tmp/test_storage");
    auto path = "/tmp/test_storage";

    auto storage = new beemaster::RocksStorage(path);
    auto key = "KEY";
    std::string value1 = "VALUE1";
    std::string value2 = "VALUE2";

    SECTION("Append on empty field") {
        REQUIRE(storage->Append(key, value1));
        REQUIRE(storage->Get(key) == value1);
        delete storage;
    }

    SECTION("Append with merge") {
        REQUIRE(storage->Append(key, value1));
        REQUIRE(storage->Append(key, value2));
        REQUIRE(storage->Get(key) == value1 + "|" + value2);
        delete storage;
    }
}

/*TEST_CASE("Testing RocksStorage iterator", "[rocks_storage]") {
    // TODO FIXME XXX DIRTY AF
    std::system("rm -rf /tmp/test_storage");
    auto path = "/tmp/test_storage";

    auto storage = new beemaster::RocksStorage<int>(path);
    std::string keys[] = {"key1", "key2", "key3"};
    int values[] = {1, 3, 2};

    // FILL
    for (auto i = 0; i < 3; ++i) {
        REQUIRE(storage->Increment(keys[i], values[i]));
    }

    // ITERATE
    auto it = storage->GetIterator();

    auto i = 0;
    for (it->SeekToFirst();
         it->Valid() && i < 3;
         it->Next(), ++i) {
        // test key
        REQUIRE(it->key() == keys[i]);
        // test value
        REQUIRE(*(int*)it->value().data() == values[i]);
    }

    delete it;
    delete storage;
}*/
