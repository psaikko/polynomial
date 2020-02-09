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

    explicit Polynomial(std::map<unsigned, T> terms) {
        for (auto &p : terms) {
            if (p.second != (T)0) {
                this->terms[p.first] = p.second;
            }
        }
    }

    size_t length() {
        return terms.size();
    }

    T coefficient(unsigned term) {
        if (terms.count(term) != 0) {
            return terms[term];
        } else {
            return (T)0;
        }
    }

    Polynomial<T> operator+ (Polynomial<T> const &other) {
        return other;
    }

    Polynomial<T> operator- (Polynomial<T> const &other) {
        return other;
    }

    Polynomial<T> operator* (Polynomial<T> const &other) {
        return other;
    }

    bool operator== (Polynomial<T> const &other) const {
        return terms == other.terms;
    }

    bool operator!= (Polynomial<T> const &other) const {
        return !(*this == other);
    }

    void print(std::ostream& os, std::string variable="x") {

    }
    
    std::ostream& operator<< (std::ostream& os) {
        print(os);
        return os;
    }

    Polynomial<T> differentiate() {
        return *this;
    }

    T operator() (T value) {
        return value;
    }
};