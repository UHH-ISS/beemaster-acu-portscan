/* test_rocks_storage.h
 * ACU Implementation (test)
 *
 * Test functionality of RocksStorage
 *
 * @author: 1jost
 */

#include "catch.hpp"

#include <rocks_storage.h>
#include <iostream>

TEST_CASE("Testing RocksDB initialisation", "[rocks_storage]") {
    // TODO FIXME XXX DIRTY AF
    std::system("rm -rf /tmp/test_storage");
    auto storage = new beemaster::RocksStorage<int>("/tmp/test_storage");

    delete storage;
}

TEST_CASE("Testing RocksStorage operations", "[rocks_storage]") {
    // TODO FIXME XXX DIRTY AF
    std::system("rm -rf /tmp/test_storage");
    auto path = "/tmp/test_storage";

    SECTION("Int, one key, single increment") {
        auto storage = new beemaster::RocksStorage<int>(path);
        auto key1 = "custom_key1";

        // INSERT
        REQUIRE(storage->Increment(key1, 1));
        // GET
        REQUIRE(storage->Get(key1) == 1);
        // INCREMENT
        REQUIRE(storage->Increment(key1, 2));
        REQUIRE(storage->Get(key1) == 3);

        delete storage;
    }

    SECTION("Float, two keys, multiple increments") {
        auto storage = new beemaster::RocksStorage<float>(path);
        auto key1 = "custom_key1";
        auto key2 = "custom_key2";

        // INSERT
        REQUIRE(storage->Increment(key1, 0.5));
        REQUIRE(storage->Increment(key2, 1.0));

        // GET
        REQUIRE(storage->Get(key1) == 0.5);
        REQUIRE(storage->Get(key2) == 1.0);

        // INCREMENT
        REQUIRE(storage->Increment(key2, 1.2));
        REQUIRE(storage->Increment(key1, 0.75));
        REQUIRE(storage->Increment(key2, 0.05));

        // CHECK
        REQUIRE(storage->Get(key1) == 1.25);
        REQUIRE(storage->Get(key2) == 2.25);

        delete storage;
    }
}
