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

TEST_CASE( "Conversions from base type" ) {
    std::map<unsigned,int> term = {{0,1}};
    Polynomial<int> constant(term);

    Polynomial<int> p1(1);
    Polynomial<int> p2 = 1;
    Polynomial<int> p3;
    p3 = p3 + 1;

    REQUIRE( p1 == constant );
    REQUIRE( p2 == constant );
    REQUIRE( p3 == constant );   
}

TEST_CASE( "Symmetry of implicit conversion for arithemetic operations" ) {
    Polynomial<int> p({{0,1},{1,1}});

    REQUIRE( 2*p == p*2 );
    REQUIRE( 2+p == p+2 );
    REQUIRE( 2-p == -p-(-2) );
}

TEST_CASE( "Static constructor for linear term" ) {
    auto one_x = Polynomial<int>::LinearTerm();
    auto two_x = Polynomial<int>::LinearTerm(2);

    std::map<unsigned,int> term = {{1,1}};
    Polynomial<int> x(term);
    Polynomial<int> two = 2;

    REQUIRE( x == one_x );
    REQUIRE( x*two == two_x ); 
}

TEST_CASE( "Composability" ) {
    std::map<unsigned, int> terms = {{0,4}, {1,-3}, {2,1}};

    Polynomial<int> p1(terms);

    auto x = Polynomial<int>::LinearTerm();
    auto p2 = x*x - 3*x + 4;

    REQUIRE( p1 == p2 );
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

TEST_CASE( "Stream formatting (int)" ) {
    Polynomial<int> zero;
    Polynomial<int> constant( std::map<unsigned,int>({{0,5}}) );
    Polynomial<int> negative_constant( std::map<unsigned,int>({{0,-5}}) );
    Polynomial<int> linear( std::map<unsigned,int>({{1,2}}) );
    Polynomial<int> quadratic( {{0,-7}, {1,3}, {2,5}});

    std::stringstream ss;

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

TEST_CASE( "Stream formatting (float)" ) {
    Polynomial<float> quadratic( {{0,3.3}, {1,-1.5}, {2,0.22}});

    std::stringstream ss;

    ss << quadratic;
    REQUIRE( ss.str() == "0.22x^2 - 1.5x + 3.3" );
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
    Polynomial<int> p( {{0,-7}, {1,3}, {2,5}} );
    Polynomial<int> neg_p( {{0,7}, {1,-3}, {2,-5}} );

    REQUIRE( neg_p == -p );
}

TEST_CASE( "Multiplication" ) { 
    Polynomial<int> p( {{0,2},{1,-2}} );
    Polynomial<int> q( {{0,2},{1, 2}} );
    Polynomial<int> p_times_q( {{0,4},{2,-4}} );

    REQUIRE( p*q == p_times_q);

    Polynomial<int> r( {{0,1},{1,-1}} );
    Polynomial<int> r_times_r( {{0,1}, {1,-2}, {2,1}} );

    REQUIRE( r*r == r_times_r);
}

TEST_CASE( "Differentiation" ) {
    Polynomial<int> p( {{0,3},{1,-2},{2,2}} );
    Polynomial<int> dp( {{0,-2},{1,4},{2,0}} );
    Polynomial<int> ddp( {{0,4},{1,0},{2,0}} );
    Polynomial<int> dddp;

    REQUIRE( p.differentiate() == dp );
    REQUIRE( p.differentiate().differentiate() == ddp );
    REQUIRE( p.differentiate().differentiate().differentiate() == dddp );
}

TEST_CASE( "Evaluation" ) {
    Polynomial<int> linear( {{0,-2},{1,1}} );

    for (int i = -10; i <= 10; ++i) {
        REQUIRE( linear(i) == i-2 );
    }

    Polynomial<int> quadratic( {{0,-2},{1,1},{2,-2}} );

    for (int i = -10; i <= 10; ++i) {
        REQUIRE( quadratic(i) == -2*i*i + i - 2 );
    }
}