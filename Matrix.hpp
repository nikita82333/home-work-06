#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <map>
#include <array>
#include <cassert>

#include "Iterator.hpp"

/// <summary>
/// Class N-dimensional matrix.
/// </summary>
/// <typeparam name="T">Matrix element type.</typeparam>
/// <param name="DefaultValue">Еhe default value of the element.</param>
/// <param name="N">Number of dimensions (N = 2 by default).</param>
template<typename T, T DefaultValue, uint32_t N = 2>
class Matrix {

    using index_type = std::array<std::size_t, N>;
    using iterator = Iterator<T, N>;
    using const_iterator = const Iterator<T, N>;

/// <summary>
/// Class Proxy - proxy element returned by the operator [].
/// </summary>
    class Proxy {
    public:
        explicit Proxy(Matrix& matrix) : _matrix(matrix), _dimension(0) {};
        ~Proxy() = default;

        void first_index(std::size_t index) {
            _dimension = 0;
            _index[_dimension] = index;
        }
        Proxy& operator[](std::size_t index) {
            _index[++_dimension] = index;//next index
            return *this;
        }
        operator T() {
            assert(_dimension == N - 1);
            return _matrix.get_value(_index);
        }
        void operator=(const T& value) {
            assert(_dimension == N - 1);
            _matrix.set_value(_index, value);
        }

    private:
        Matrix& _matrix;
        index_type _index;
        uint32_t _dimension;
    };

public:
    Matrix() = default;
    ~Matrix() = default;

    Proxy& operator[](std::size_t index) {
        _proxy.first_index(index);
        return _proxy;
    }
    iterator begin() {
        return iterator(_data.begin());
    }
    iterator end() {
        return iterator(_data.end());
    }
    const_iterator begin() const {
        return const_iterator(_data.begin());
    }
    const_iterator end() const {
        return const_iterator(_data.end());
    }
    std::size_t size() {
        return _data.size();
    }

private:
    T& get_value(index_type index);
    void set_value(index_type index, const T& value);

    std::map<index_type, T> _data;
    Proxy _proxy {*this};
    T _default_value {DefaultValue};
};

template<typename T, T DefaultValue, uint32_t N>
T& Matrix<T, DefaultValue, N>::get_value(index_type index) {
    if (auto it = _data.find(index); it != _data.end()) {
        return it->second;
    } else {
        return _default_value;
    }
}

template<typename T, T DefaultValue, uint32_t N>
void Matrix<T, DefaultValue, N>::set_value(index_type index, const T &value) {
    if (value == DefaultValue) {
        _data.erase(index);
    } else {
        _data.insert_or_assign(index, value);
    }
}


#endif //MATRIX_HPP
