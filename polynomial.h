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

    Polynomial(std::map<std::pair<unsigned, T>>);

    Polynomial<T> operator+ (Polynomial<T> const &other);

    Polynomial<T> operator- (Polynomial<T> const &other);

    Polynomial<T> operator* (Polynomial<T> const &other);
    
    std::ostream& operator<< (std::ostream& os);

    Polynomial<T> differentiate();

    T opetator() (T value);
}