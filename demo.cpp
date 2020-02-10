#include <iostream>
#include <map>
#include "polynomial.h"

using namespace std;

int main() {
    map<unsigned,float> terms = {{0,-1},{3,1}};
    Polynomial<float> f(terms);
    cout << "f(x) = " << f << endl;
    cout << "f'(x) = " << f.differentiate() << endl;

    auto x = Polynomial<float>::LinearTerm();
    auto g = 4.5*x*x - 7.1*x + 0.5;

    cout << "g(x) = " << g << endl;
    cout << "g'(x) = " << g.differentiate() << endl;
    cout << "g''(x) = " << g.differentiate().differentiate() << endl;
    cout << "g'''(x) = " << g.differentiate().differentiate().differentiate() << endl;
    cout << "g''''(x) = " << g.differentiate().differentiate().differentiate().differentiate() << endl;

    cout << "g(3.0) = " << g(3.0) << endl;
}