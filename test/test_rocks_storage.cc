/* test_rocks_storage.cc
 * ACU Implementation (test)
 *
 * Test functionality of RocksStorage
 *
 * @author: 1wilkens, 0ortmann
 */

#include "catch.hpp"
#include <rocks_storage.h>

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
    std::string value1 = "VALUE_1";
    std::string value2 = "VALUE_2";
    std::string value3 = "VAL_3";

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

    SECTION("Append ordered dedupe") {
        REQUIRE(storage->Append(key, value1));
        REQUIRE(storage->Get(key) == value1);

        REQUIRE(storage->Append(key, value2));
        REQUIRE(storage->Get(key) == value1 + "|" + value2);

        REQUIRE(storage->Append(key, value3));
        REQUIRE(storage->Get(key) == value1 + "|" + value2 + "|" + value3);

        REQUIRE(storage->Append(key, value1));
        REQUIRE(storage->Append(key, value2));
        REQUIRE(storage->Append(key, value3));

        REQUIRE(storage->Get(key) == value1 + "|" + value2 + "|" + value3);
        delete storage;
    }

    SECTION("Append unordered dedupe") {
        REQUIRE(storage->Append(key, value2));
        REQUIRE(storage->Append(key, value1));
        REQUIRE(storage->Append(key, value3));

        REQUIRE(storage->Append(key, value3));
        REQUIRE(storage->Append(key, value2));
        REQUIRE(storage->Append(key, value1));
        REQUIRE(storage->Append(key, value2));

        REQUIRE(storage->Get(key) == value2 + "|" + value1 + "|" + value3);
        delete storage;
    }
}
