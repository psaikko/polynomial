template<typename T>
Polynomial<T>::Polynomial(std::map<unsigned, T> ts) :
    terms(ts) {
}

template<typename T>
size_t Polynomial<T>::length() {
    return terms.size();
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
    print(os);
    return os;
}

template<typename T>
void Polynomial<T>::print(std::ostream& os, std::string variable) {
}

template<typename T>
Polynomial<T> Polynomial<T>::differentiate() {
    return *this;
}

template<typename T>
T Polynomial<T>::operator() (T value) {
    return value;
}