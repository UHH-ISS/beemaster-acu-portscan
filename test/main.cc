/* main.cc
 * ACU Implementation (test)
 *
 * Main entrypoint to the tests.
 *
 * @author: 1wilkens
 */

// Stub file for catch main function.
// Write tests in separate source files

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

// This prevents CLion to accidentally optimize out
// the #include and #define
TEST_CASE("IGNORE", "IGNORE") {
    CATCH_CONFIG_MAIN
}
