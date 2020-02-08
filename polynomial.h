#pragma once
#include <iosfwd>
#include <map>
#include <utility> // std::pair

template<typename T>
class Polynomial {
 private:
    std::map<unsigned, T> coefficients;

 public:
    Polynomial() = default;

    Polynomial(std::map<unsigned, T>);

    size_t length();

    Polynomial<T> operator+ (Polynomial<T> const &other);

    Polynomial<T> operator- (Polynomial<T> const &other);

    Polynomial<T> operator* (Polynomial<T> const &other);
    
    std::ostream& operator<< (std::ostream& os);

    Polynomial<T> differentiate();

    T operator() (T value);
};

#include "polynomial_impl.h"