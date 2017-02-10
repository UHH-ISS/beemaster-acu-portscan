/* test_utiles.cc
 * ACU Implementation (test)
 *
 * Tests for some of the utility functions.
 *
 * @author: 1wilkens
 */

#include "catch.hpp"

#include <utils.h>

using namespace beemaster;

TEST_CASE("Test utils", "[utils]") {
    const char delimiter = '|';

    std::string val1 = "VALUE_1";
    std::string val2 = "VALUE_2";
    std::string val3 = "VALUE_3";

    REQUIRE(val1 != val2);
    REQUIRE(val1 != val3);
    REQUIRE(val2 != val3);

    REQUIRE_FALSE(contains_string(val1, val2, delimiter));
    REQUIRE_FALSE(contains_string(val1, val3, delimiter));
    REQUIRE_FALSE(contains_string(val2, val3, delimiter));

    REQUIRE(contains_string(val1 + '|' + val2, val1, delimiter));
    REQUIRE(contains_string(val1 + '|' + val2, val2, delimiter));

    REQUIRE(contains_string(val1 + '|' + val3, val1, delimiter));
    REQUIRE(contains_string(val1 + '|' + val3, val3, delimiter));

    REQUIRE(contains_string(val2 + '|' + val3, val2, delimiter));
    REQUIRE(contains_string(val2 + '|' + val3, val3, delimiter));

    REQUIRE(contains_string(val2 + '|' + val1, val1, delimiter));
    REQUIRE(contains_string(val2 + '|' + val1, val2, delimiter));

    REQUIRE(contains_string(val3 + '|' + val1, val1, delimiter));
    REQUIRE(contains_string(val3 + '|' + val1, val3, delimiter));

    REQUIRE(contains_string(val3 + '|' + val2, val2, delimiter));
    REQUIRE(contains_string(val3 + '|' + val2, val3, delimiter));
}
