#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "polynomial.h"

TEST_CASE( "Default constructor creates zero polynomial" ) {
    Polynomial<int> p;
    REQUIRE( p.length() == 0 );
}

TEST_CASE( "Constructor sets coefficients" ) {
    Polynomial<int> p({{0,4},{1,-2},{2,2}});
    REQUIRE( p.coefficient(0) == 4 );
    REQUIRE( p.coefficient(1) == -2 );
    REQUIRE( p.coefficient(2) == 2 );
}

TEST_CASE( "Constructor doesn't set 0-terms" ) {
    Polynomial<int> p({{0,0},{1,1},{2,0}});
    REQUIRE( p.length() == 1 );
}

TEST_CASE( "Equality checks" ) {
    Polynomial<int> p1( std::map<unsigned,int>({{1,1}}) );
    Polynomial<int> p2( std::map<unsigned,int>({{1,1}}) );
    Polynomial<int> p3( {{0,0},{1,1},{2,0}} );
    Polynomial<int> p4( {{1,1},{3,1}} );
    Polynomial<int> p5( std::map<unsigned,int>({{1,2}}) );

    REQUIRE( p1 == p2 );
    REQUIRE( p1 == p3 );
    REQUIRE( p1 != p3 );
    REQUIRE( p1 != p4 );
}