#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include <map>
#include <array>
#include <iterator>

/// <summary>
/// Class Iterator for Matrix.
/// </summary>
/// <typeparam name="T">Matrix element type.</typeparam>
/// <param name="N">Number of dimensions.</param>
template<typename T, uint32_t N>
class Iterator : public std::iterator<std::input_iterator_tag, T> {
public:

    using index_type = std::array<std::size_t, N>;
    using iterator_type = typename std::map<index_type, T>::iterator;
    using iterator_value_type = typename std::map<index_type, T>::value_type;

    Iterator(iterator_type data): _data(data) {}
    Iterator(const Iterator &it): _data(it._data) {}

    Iterator& operator=(const Iterator &it) {
        _data = it._data;
        return *this;
    }
    bool operator==(const Iterator &it) const {
        return _data == it._data;
    }
    bool operator!=(const Iterator &it) const {
        return _data != it._data;
    }
    Iterator& operator++() {
        ++_data;
        return *this;
    }
    Iterator& operator--() {
        --_data;
        return *this;
    }
    iterator_value_type& operator*() {
        return *_data;
    }

private:
    iterator_type _data;

 };


#endif //ITERATOR_HPP
