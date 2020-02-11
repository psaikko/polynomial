#pragma once
#include <iosfwd>
#include <map>
#include <utility> // std::pair
#include <string>
#include <complex>

// Helper functions for printing
template<typename T> bool tSign(T t) {
    if (t < 0) return true;
    return false;
}
template<typename T> T tAbs(T t) {
    if (t < 0) return -t;
    return t;
}

// Specialization for complex type
template<typename U>
bool tSign(std::complex<U>) {
    return false;
}
template<typename U>
std::complex<U> tAbs(std::complex<U> t) {
    return t;
}

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

    // Enable implicit conversion from coefficient type to constant term
    Polynomial(T value) : terms{{0,value}} 
    {}

    // Construct a linear term / variable for convenience
    static Polynomial<T> LinearTerm(T coefficient = T(1)) {
        Polynomial<T> p;
        p.terms[1] = coefficient;
        return p;
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

    // Declaration as non-templated friend function to allow 
    // implicit conversions from numeric types.
    // See https://web.mst.edu/~nmjxv3/articles/templates.html
    friend Polynomial operator+ (const Polynomial &lhs, const Polynomial &rhs) {
        Polynomial<T> result(lhs);
        for (auto &term : rhs.terms) {
            unsigned exponent = term.first;
            T coefficient = term.second;

            result.terms[exponent] += coefficient;

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

    friend Polynomial operator- (const Polynomial &lhs, const Polynomial &rhs) {
        return lhs + -rhs;
    }

    friend Polynomial operator* (const Polynomial &lhs, const Polynomial &rhs) {
        Polynomial<T> result;
        for (auto &p1 : lhs.terms) {
            unsigned exponent_1 = p1.first;
            T coefficient_1 = p1.second;

            for (auto &p2 : rhs.terms) {
                unsigned exponent_2 = p2.first;
                T coefficient_2 = p2.second;

                unsigned result_exponent = exponent_1 + exponent_2;
                T result_coefficient = coefficient_1 * coefficient_2;

                result.terms[result_exponent] += result_coefficient;

                // Remove zero-coefficient terms
                if (result.terms[result_exponent] == T()) 
                    result.terms.erase(result_exponent);
            }
        }
        return result;
    }

    Polynomial<T> differentiate() {
        Polynomial<T> result;
        for (auto &term : terms) {
            unsigned exponent = term.first;
            T coefficient = term.second;

            if (exponent > 0) {
                coefficient *= exponent;
                exponent--;

                result.terms[exponent] = coefficient;
            }
        }
        return result;
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
            os << (tSign(it->second) ? " - " : " + ");
            os << tAbs(it->second);

            if (it->first > 0)
                os << variable;
            if (it->first > 1)
                os << "^" << it->first;
        }
    }

    // evaluate the polynomial at a point
    template<typename U>
    U operator() (U value) {
        U result = U();
        U tmp = value;
        unsigned tmp_exponent = 1;

        for (auto &term : terms) {
            unsigned exponent = term.first;
            T coefficient = term.second;

            if (exponent == 0) {
                result += coefficient;
            } else if (exponent == 1) {
                result += value * coefficient;
            } else {
                while (tmp_exponent < exponent) {
                    tmp *= value;
                    tmp_exponent += 1;
                }
                result += tmp * coefficient;
            }
        }

        return result;
    }
};

template<typename T>
std::ostream& operator<< (std::ostream& os, Polynomial<T> const &p) {
    p.print(os);
    return os;
}
