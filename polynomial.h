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

    Polynomial(Polynomial<T> const &p) : terms{p.terms} 
    {}

    explicit Polynomial(std::map<unsigned, T> terms) {
        for (auto &p : terms) {
            if (p.second != T()) {
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
            return T();
        }
    }

    Polynomial<T> operator+ (Polynomial<T> const &other) const {
        Polynomial<T> result(*this);
        for (auto &term : other.terms) {
            unsigned exponent = term.first;
            T coefficient = term.second;

            if (result.terms.count(exponent)) {
                result.terms[exponent] += coefficient;
            } else {
                result.terms[exponent] = coefficient;
            }

            // Remove zero-coefficient terms
            if (result.terms[exponent] == T()) 
                result.terms.erase(exponent);
        }
        return result;
    }

    Polynomial<T> operator- () const {
        Polynomial<T> result(*this);
        for (auto &p : result.terms) {
            p.second = -p.second;
        }
        return result;
    }

    Polynomial<T> operator- (Polynomial<T> const &other) const {
        return *this + -other;
    }

    Polynomial<T> operator* (Polynomial<T> const &other) const {
        return other;
    }

    bool operator== (Polynomial<T> const &other) const {
        return terms == other.terms;
    }

    bool operator!= (Polynomial<T> const &other) const {
        return !(*this == other);
    }

    void print(std::ostream& os, std::string variable="x") const {
        // Handle zero polynomial
        if (terms.size() == 0) {
            os << T();
            return;
        }

        // First term
        auto it = terms.rbegin();
        os << it->second;
        if (it->first > 0)
            os << variable;
        if (it->first > 1)
            os << "^" << it->first;

        // Rest of the terms
        while (++it != terms.rend()) {
            if (it->second < 0) {
                os << " - ";
            } else {
                os << " + ";
            }

            os << abs(it->second);
            if (it->first > 0)
                os << variable;
            if (it->first > 1)
                os << "^" << it->first;
        }
    }

    Polynomial<T> differentiate() {
        return *this;
    }

    T operator() (T value) {
        return value;
    }
};

template<typename T>
std::ostream& operator<< (std::ostream& os, Polynomial<T> const &p) {
    p.print(os);
    return os;
}
