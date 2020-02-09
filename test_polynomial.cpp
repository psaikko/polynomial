#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "polynomial.h"
#include <string>
#include <sstream>

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

    REQUIRE( p1 == p1 );
    REQUIRE( p1 == p2 );
    REQUIRE( p2 == p1 );
    REQUIRE( p1 == p3 );
    REQUIRE( p3 == p1 );
    REQUIRE( p1 != p4 );
    REQUIRE( p4 != p1 );
    REQUIRE( p1 != p5 );
    REQUIRE( p5 != p1 );
}

TEST_CASE( "Stream formatting" ) {
    Polynomial<int> zero;
    Polynomial<int> constant( std::map<unsigned,int>({{0,5}}) );
    Polynomial<int> negative_constant( std::map<unsigned,int>({{0,-5}}) );
    Polynomial<int> linear( std::map<unsigned,int>({{1,2}}) );
    Polynomial<int> quadratic( {{0,-7}, {1,3}, {2,5}});

    std::stringstream ss;
    std::string output;

    ss << zero;
    REQUIRE( ss.str() == "0" );

    ss.str("");
    ss << constant;
    REQUIRE( ss.str() == "5" );

    ss.str("");
    ss << negative_constant;
    REQUIRE( ss.str() == "-5" );

    ss.str("");
    ss << linear;
    REQUIRE( ss.str() == "2x" );

    ss.str("");
    ss << quadratic;
    REQUIRE( ss.str() == "5x^2 + 3x - 7" );

    ss.str("");
    quadratic.print(ss, "y");
    REQUIRE( ss.str() == "5y^2 + 3y - 7" );
}