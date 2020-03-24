#ifndef MY_ARRAY_H_
#define MY_ARRAY_H_

#include <cstddef>
#include <stdexcept>
#include <cstring>

namespace lab_13 {

namespace {
    const size_t BITS_IN_BYTE = 8;
} // namespace

template<typename T, std::size_t N>
class my_array {
public:
    constexpr T& at(std::size_t index);
    constexpr const T& at(std::size_t index) const;
    constexpr T& operator[](std::size_t index);
    constexpr const T& operator[](std::size_t index) const;

    constexpr bool empty() const noexcept;
    constexpr std::size_t size() const noexcept;

    constexpr void fill(T val);

private:
    T array_[N];
};

template<typename T, std::size_t N>
inline constexpr T& my_array<T, N>::at(std::size_t index) {
    if (index >= N) {
        throw (std::out_of_range(""));
    }
    return array_[index];
}

template<typename T, std::size_t N>
inline constexpr const T& my_array<T, N>::at(std::size_t index) const {
    if (index >= N) {
        throw (std::out_of_range(""));
    }
    return array_[index];
}

template<typename T, std::size_t N>
inline constexpr T& my_array<T, N>::operator[](std::size_t index) {
    return array_[index];
}

template<typename T, std::size_t N>
inline constexpr const T& my_array<T, N>::operator[](std::size_t index) const {
    return array_[index];
}

template<typename T, std::size_t N>
inline constexpr bool my_array<T, N>::empty() const noexcept {
    return (N == 0);
}

template<typename T, std::size_t N>
inline constexpr std::size_t my_array<T, N>::size() const noexcept {
    return N;
}

template<typename T, std::size_t N>
inline void constexpr my_array<T, N>::fill(T val) {
    for (std::size_t k = 0; k < N; ++k) {
        array_[k] = val;
    }
}



template<std::size_t N>
class my_array<bool, N> {
private:
    struct arrayBoolProxy {
        arrayBoolProxy(uint8_t* byte, std::size_t bit);
        arrayBoolProxy& operator=(bool value);
        arrayBoolProxy& operator=(const arrayBoolProxy& other);
        operator bool() const;
    private:
        uint8_t* byte_;
        std::size_t bit_;
    };
public:
    constexpr my_array();
    constexpr arrayBoolProxy at(std::size_t index);
    constexpr bool at(std::size_t index) const;
    constexpr arrayBoolProxy operator[](std::size_t index);
    constexpr bool operator[](std::size_t index) const;

    constexpr bool empty() const noexcept;
    constexpr std::size_t size() const noexcept;

    constexpr void fill(bool val);

private:
    uint8_t array_[(N + (BITS_IN_BYTE - 1))/BITS_IN_BYTE];
};

template<std::size_t N>
inline my_array<bool, N>::arrayBoolProxy::arrayBoolProxy(uint8_t* byte, std::size_t bit) 
    : byte_(byte), bit_(bit) { }

template<std::size_t N>
inline typename my_array<bool, N>::arrayBoolProxy& my_array<bool, N>::arrayBoolProxy::operator=(bool value) {
    bool current = ((*byte_ & (1 << bit_)) != 0);
    if (current != value) {
        *byte_ ^= (1 << bit_);
    }
    return *this;
}

template<std::size_t N>
inline typename my_array<bool, N>::arrayBoolProxy& my_array<bool, N>::arrayBoolProxy::operator=(const typename my_array<bool, N>::arrayBoolProxy& other) {
    (*this) = static_cast<bool>(other);
    return *this;
}

template<std::size_t N>
inline my_array<bool, N>::arrayBoolProxy::operator bool() const {
    return ((*byte_ & (1 << bit_)) != 0);
}
 



template<std::size_t N>
inline constexpr my_array<bool, N>::my_array() {
    fill(false);
}

template<std::size_t N>
inline constexpr typename my_array<bool, N>::arrayBoolProxy my_array<bool, N>::at(std::size_t index) {
    if (index >= N) {
        throw (std::out_of_range(""));
    }
    return arrayBoolProxy(&array_[index / BITS_IN_BYTE], index % BITS_IN_BYTE);
}

template<std::size_t N>
inline constexpr bool my_array<bool, N>::at(std::size_t index) const {
    if (index >= N) {
        throw (std::out_of_range(""));
    }
    return ((array_[index / BITS_IN_BYTE] & (1 << (index % BITS_IN_BYTE))) != 0);
}

template<std::size_t N>
inline constexpr typename my_array<bool, N>::arrayBoolProxy my_array<bool, N>::operator[](std::size_t index) {
    return arrayBoolProxy(&array_[index / BITS_IN_BYTE], index % BITS_IN_BYTE);
}

template<std::size_t N>
inline constexpr bool my_array<bool, N>::operator[](std::size_t index) const {
    return ((array_[index / BITS_IN_BYTE] & (1 << (index % BITS_IN_BYTE))) != 0);
}

template<std::size_t N>
inline constexpr bool my_array<bool, N>::empty() const noexcept {
    return (N == 0);
}

template<std::size_t N>
inline constexpr std::size_t my_array<bool, N>::size() const noexcept {
    return N;
}

template<std::size_t N>
inline void constexpr my_array<bool, N>::fill(bool val) {
    if (val) {
        memset(array_, UINT8_MAX, (N + (BITS_IN_BYTE - 1))/BITS_IN_BYTE);
    } else {
        memset(array_, 0, (N + (BITS_IN_BYTE - 1))/BITS_IN_BYTE);
    }
}


}  // namespace lab_13

#endif  // MY_ARRAY_H_
