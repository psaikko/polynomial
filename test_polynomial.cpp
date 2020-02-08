#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "polynomial.h"

TEST_CASE( "Default constructor creates zero polynomial" ) {
    Polynomial<int> p;
    REQUIRE( p.length() == 0 );
}
