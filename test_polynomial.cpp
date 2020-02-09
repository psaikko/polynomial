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
    // Explicit cast to std::map required 
    // likely due to gcc (v. 7.4.0, 9.2.0) bug 
    // https://gcc.gnu.org/bugzilla/show_bug.cgi?id=84849
    // Works without cast using e.g. Intel compiler (v. 19.1.0)
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

TEST_CASE( "Addition" ) {
    Polynomial<int> p1( {{0,1}, {1,1}} );
    Polynomial<int> p2( {{1,1}, {2,1}} );

    Polynomial<int> p3 = p1 + p2;

    // Result coefficients are added
    REQUIRE( p3.coefficient(0) == 1 );
    REQUIRE( p3.coefficient(1) == 2 );
    REQUIRE( p3.coefficient(2) == 1 );

    // Terms of the sum are unchanged
    REQUIRE( p1.coefficient(0) == 1);
    REQUIRE( p1.coefficient(1) == 1);
    REQUIRE( p2.coefficient(1) == 1);
    REQUIRE( p2.coefficient(2) == 1);

    // Polynomials have correct length
    REQUIRE( p1.length() == 2 );
    REQUIRE( p2.length() == 2 );
    REQUIRE( p3.length() == 3 );
}

TEST_CASE( "Subtraction" ) {
    Polynomial<int> p1( {{0,1}, {1,1}} );
    Polynomial<int> p2( {{1,1}, {2,1}} );

    Polynomial<int> p3 = p1 - p2;

    // Result coefficients are subtracted
    REQUIRE( p3.coefficient(0) == 1 );
    REQUIRE( p3.coefficient(1) == 0 );
    REQUIRE( p3.coefficient(2) == -1 );

    // Terms of the sum are unchanged
    REQUIRE( p1.coefficient(0) == 1);
    REQUIRE( p1.coefficient(1) == 1);
    REQUIRE( p2.coefficient(1) == 1);
    REQUIRE( p2.coefficient(2) == 1);

    // Polynomials have correct length
    REQUIRE( p1.length() == 2 );
    REQUIRE( p2.length() == 2 );
    REQUIRE( p3.length() == 2 );
}

TEST_CASE( "Negation" ) {
    Polynomial<int> p( {{0,-7}, {1,3}, {2,5}});
    Polynomial<int> negation = -p;

    REQUIRE( negation.coefficient(0) == 7 );
    REQUIRE( negation.coefficient(1) == -3 );
    REQUIRE( negation.coefficient(2) == -5 );
}

TEST_CASE( "Multiplication" ) {
    REQUIRE(false);
}

TEST_CASE( "Differentiation" ) {
    REQUIRE(false);
}

TEST_CASE( "Evaluation" ) {
    REQUIRE(false);
}