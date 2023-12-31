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

        size_t get_size() const {
            return _size;
        }

        T* get_data() const {
            return _data;
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

        void set(T data, size_t index) {
            if (index > _size) {
                expand(index + 1);
            }
            _data[index] = data;
        }

        void expand(size_t size) {
            if (size < _size) {
                throw std::out_of_range("operator[] Index is out of range.");
            }
            T* temp_arr = (new T[size]());
            for (size_t i = 0; i < _size; i++) {
                temp_arr[i] = _data[i];
            }
            delete[] _data;
            _data = temp_arr;
            _size = size;
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
            return !(p == *this);
        }

        friend Polynomial<T> operator* (const T& p, const Polynomial<T>& pol) {
            Polynomial<T> res = pol;
            res = res * p;
            return res;
        }
        T calc_x (const T& x) {
            T res = 0;
            for (size_t i = 0; i < _size; i++) {
                res += _data[i] * pow(x, i);
            }
            return res;
        }
        
        void shrink_to_fit() {
            T zero = T(0);
            for (size_t i = _size - 1; i > 0; i--) {
                if (_data[i] != zero) {
                    i++;
                    T* temp = (new T[i]());
                    for (size_t j = 0; j < i; j++) {
                        temp[j] = _data[j];
                    }
                    delete[] _data;
                    _data = temp;
                    _size = i;
                    break;
                }
            }
        }
    };

    template<typename T>
    double calc_root_1(Polynomial<T> polynomial) {
        T* data = polynomial.get_data();
        if (data[1] == 0) {
            throw std::out_of_range("calc_root() There is no solution.");
        }
        return (-1.0) * data[0] / data[1];
    }

    template<typename T>
    complex<double>* calc_root_2(complex<double>* roots, Polynomial<T> polynomial) {
        T* data = polynomial.get_data();
        T a = data[2];
        T b = data[1];
        T c = data[0];
        T discriminant = b * b - 4 * a * c;

        if (discriminant >= 0) {
            roots[0] = (-b + std::sqrt(discriminant)) / (2.0 * a);
            roots[1] = (-b - std::sqrt(discriminant)) / (2.0 * a);
        }
        else {
            std::complex<double> complexRoot(-b / (2.0 * a), std::sqrt(-discriminant) / (2 * a)); //������ �������� ������������ �����, ������ ������
            roots[0] = complexRoot;
            roots[1] = std::conj(complexRoot); //�����������
        }
        return roots;
    }

    template<typename T>
    std::ostream& operator << (std::ostream& stream, const Polynomial<T>& p) {
        for (size_t i = 0; i < p.get_size(); ++i) {
            if (i == 0) {
                stream << p[i];
            }
            else if (i == 1) {
                stream << " + " << p[i] << "*x";
            }
            else {
                stream << " + " << p[i] << "*x^" << i;
            }
        }
        return stream;
    }
}
