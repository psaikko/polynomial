#include "polynomial.h"

template<typename T>
Polynomial<T>::Polynomial(std::map<unsigned, T> cs) :
    coefficients(cs) {
}

template<typename T>
Polynomial<T> Polynomial<T>::operator+ (Polynomial<T> const &other) {
    return other;
}

template<typename T>
Polynomial<T> Polynomial<T>::operator- (Polynomial<T> const &other) {
    return other;
}

template<typename T>
Polynomial<T> Polynomial<T>::operator* (Polynomial<T> const &other) {
    return other;
}

template<typename T>
std::ostream& Polynomial<T>::operator<< (std::ostream& os) {
    return os;
}

template<typename T>
Polynomial<T> differentiate() {
    return *this;
}

template<typename T>
T Polynomial<T>::opetator() (T value) {
    return value;
}