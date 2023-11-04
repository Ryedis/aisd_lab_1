#pragma once
#include <iostream>
#include <cmath>
#include <stdexcept>
#include <complex>

using namespace std;
namespace pol {


    template<typename T>
    class Polynomial {
    private:
        T* _data;
        size_t _size;
        inline static const double EPSILION = 0.001;
    public:
        Polynomial(size_t size) : _data(new T[size]()), _size(size) {}

        Polynomial(T* data, size_t size) : _data(new T[size]), _size(size) {
            for (size_t i = 0; i < _size; i++) {
                _data[i] = data[i];
            }
        }

        Polynomial(const Polynomial<T>& poly) : _data(new T[poly._size]), _size(poly._size) {
            for (size_t i = 0; i < _size; i++) {
                _data[i] = poly[i];
            }
        }

        ~Polynomial() {
            delete[] _data;
            _data = nullptr;
            _size = 0;
        }

        Polynomial<T>& operator=(Polynomial<T> poly) {
            swap(poly);
            return *this;
        }

        void swap(Polynomial<T>& poly) {
            std::swap(_data, poly._data);
            std::swap(_size, poly._size);
        }

        T operator[](size_t index) const {
            if (_size <= index) {
                return 0;
            }
            return _data[index];
        }

        Polynomial<T>& operator+= (const Polynomial<T>& p) {
            if (p.size() > _size) {
                expand(p.size());
            }
            for (size_t i = 0; i < p._size; i++) {
                _data[i] += p[i];
            }
            return *this;
        }

        Polynomial<T>& operator-= (const Polynomial<T>& p) {
            if (p.size() > _size) {
                expand(p.size());
            }
            for (size_t i = 0; i < p._size; i++) {
                _data[i] -= p[i];
            }
            return *this;
        }

        Polynomial<T> operator- (Polynomial<T> p) const {
            return p -= *this;
        }

        Polynomial<T> operator+ (Polynomial<T> p)  const {
            return p += *this;
        }

        Polynomial<T>& operator*(const T& p) {
            for (size_t i = 0; i < _size; i++) {
                _data[i] *= p;
            }
            return *this;
        }

        bool operator== (Polynomial<T> p) const {
            p.shrink_to_fit();
            Polynomial<T> copy(*this);
            copy.shrink_to_fit();
            if (copy._size != p._size) { 
                return false;
            }
            for (size_t i = 0; i < p._size; i++) {
                if (std::abs(_data[i] - p._data[i]) > EPSILION) {
                    return false;
                }
            }
            return true;
        }

        bool operator!= (const Polynomial<T>& p) const {
            return !(a == *this);
        }

        friend Polynomial<T> operator* (const T& p, const Polynomial<T>& pol) {
            Polynomial<T> res = pol;
            res = res * p;
            return res;
        }
        T calculate_x(const T& x) {
            T res = 0;
            for (size_t i = 0; i < _size; i++) {
                res += _data[i] * pow(x, i);
            }
            return res;
        }
    };

    template<typename T>
    std::ostream& operator << (std::ostream& stream, const Polynomial<T>& a) {
        for (size_t i = 0; i < a.size(); ++i) {
            if (i == 0) {
                stream << a[i];
            }
            else if (i == 1) {
                stream << " + " << a[i] << "*x";
            }
            else {
                stream << " + " << a[i] << "*x^" << i;
            }
        }
        return stream;
    }
}
