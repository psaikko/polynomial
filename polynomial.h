#pragma once
#include <iosfwd>
#include <map>
#include <utility> // std::pair
#include <string>

template<typename T>
class Polynomial {
 private:
    std::map<unsigned, T> terms;

 public:
    Polynomial() = default;

    Polynomial(std::map<unsigned, T>);

    size_t length();

    T coefficient(unsigned term) {
        if (terms.count(term) != 0) {
            return terms[term];
        } else {
            return (T)0;
        }
    }

    Polynomial<T> operator+ (Polynomial<T> const &other);

    Polynomial<T> operator- (Polynomial<T> const &other);

    Polynomial<T> operator* (Polynomial<T> const &other);

    void print(std::ostream& os, std::string variable="x");
    
    std::ostream& operator<< (std::ostream& os);

    Polynomial<T> differentiate();

    T operator() (T value);
};

#include "polynomial_impl.h"