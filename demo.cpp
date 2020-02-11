#include <iostream>
#include <map>
#include <complex>
#include "polynomial.h"

using namespace std;

int main() {
    cout << "Polynomials can be constructed from a std::map of terms" << endl;
    map<unsigned,float> terms = {{0,-1},{3,1}};
    Polynomial<float> f(terms);
    cout << "f(x) = " << f << endl << endl;

    cout << "Or by composition from other polynomials" << endl;
    auto x = Polynomial<float>::LinearTerm();
    auto g = 4.5*x*x - 7.1*x + 0.5;
    cout << "g(x) = " << g << endl << endl;

    cout << "The printed variable can be specified using the print function" << endl;
    cout << "g(y) = ";
    g.print(cout, "y");
    cout << endl << endl;

    cout << "Polynomials can be differentiated" << endl;
    cout << "g'(x) = " << g.differentiate() << endl;
    cout << "g''(x) = " << g.differentiate().differentiate() << endl << endl;

    cout << "And evaluated at arbitrary points" << endl;
    cout << "g(3.0) = " << g(3.0) << endl << endl;

    cout << "Arithmeric operations + - * and negation are also implemented" << endl;
    auto p = x - 2;
    auto q = x + 2;
    cout << "p(x) = " << p << endl;
    cout << "q(x) = " << q << endl;
    cout << "(p * q)(x) = " << p*q << endl;
    cout << "(p + q)(x) = " << p+q << endl;
    cout << "(p - q)(x) = " << p-q << endl << endl;

    cout << "The polynomial class is templated so it can be " << endl;
    cout << "instantiated for e.g. complex coefficients as well" << endl;
    Polynomial<complex<float>> h({{0,{1,-1}}, {1,{-2,1}}});
    cout << "h(x) = " << h << endl;
}