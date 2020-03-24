#ifndef MY_VECTOR_IMPL_H_
#define MY_VECTOR_IMPL_H_

#include <cstdlib>
#include <iostream>
#include <memory>
#include <stdexcept>

namespace my_vector {

template<typename T>
std::ostream& operator<<(std::ostream& os, const my_vector<T>& vec) {
    for (size_t k = 0; k < vec.size(); ++k) {
        os << vec[k];
        if (k + 1 != vec.size()) std::cout << ' ';
    }
    return os;
}

namespace {

size_t log2_ceil(size_t n) {
    if (n * 2 < n) {
        throw (std::logic_error("Very big")); // Иначе будет бесконечный цикл
    }
    size_t rez = 1;
    while (rez < n) {
        rez *= 2;
    }
    return rez;
}

} // namespace

template<typename T>
void my_vector<T>::swap(my_vector_impl& lhs, my_vector_impl& rhs) noexcept {
    std::swap(lhs.capacity_, rhs.capacity_);
    std::swap(lhs.size_, rhs.size_);
    std::swap(lhs.array_, rhs.array_);
}

template<typename T>
my_vector<T>::my_vector_impl::my_vector_impl() 
    : capacity_(0)
    , size_(0)
    , array_(nullptr) {
}

template<typename T>
my_vector<T>::my_vector_impl::my_vector_impl(size_t n)
    : capacity_(log2_ceil(n))
    , size_(0)
    , array_(static_cast<T*>(aligned_alloc(alignof(T), sizeof(T) * log2_ceil(n)))) {
        if (array_ == nullptr) {
            throw (std::bad_alloc());
        }
}

template<typename T>
my_vector<T>::my_vector_impl::~my_vector_impl() noexcept {
    while (size_ > 0) {
        pop_back();
    }
    std::free(array_);
}

template<typename T>
void my_vector<T>::my_vector_impl::pop_back() noexcept {
    if (size_ > 0) {
        array_[size_ - 1].~T();
        --size_;
    }
}

template<typename T>
my_vector<T>::my_vector() : storage_() { }

template<typename T>
my_vector<T>::my_vector(std::size_t n) : storage_(n) {
    for (; storage_.size_ < n; ++storage_.size_) {
        new (storage_.array_ + storage_.size_) T();
    }
}

template<typename T>
my_vector<T>::my_vector(const my_vector<T>& other) : storage_(other.storage_.size_) {
    for (; storage_.size_ < other.storage_.size_; ++storage_.size_) {
        new (storage_.array_ + storage_.size_) T(other.storage_.array_[storage_.size_]);
    }
}

template<typename T>
my_vector<T>::my_vector(my_vector<T>&& other) noexcept {
    swap(this->storage_, other.storage_);
}

template<typename T>
my_vector<T>& my_vector<T>::operator=(const my_vector<T>& other) {
    if (this == &other) return *this;

    my_vector<T> newv(other);
    swap(this->storage_, newv.storage_);

    return *this;
}

template<typename T>
my_vector<T>& my_vector<T>::operator=(my_vector&& other) noexcept {
    if (this == &other) return *this;

    swap(this->storage_, other.storage_);

    return *this;
}

template<typename T>
std::size_t my_vector<T>::size() const noexcept {
    return storage_.size_;
}


template<typename T>
std::size_t my_vector<T>::capacity() const noexcept {
    return storage_.capacity_;
}

template<typename T>
bool my_vector<T>::empty() const noexcept {
    return (storage_.size_ == 0);
}

template<typename T>
void my_vector<T>::resize(std::size_t n) {
    if (n <= storage_.size_) {
        while (storage_.size_ > n) {
            storage_.pop_back();
        }
    } else {
        my_vector_impl newimpl(n);
        for (; newimpl.size_ < storage_.size_; ++newimpl.size_) {
            new (newimpl.array_ + newimpl.size_) T(storage_.array_[newimpl.size_]);
        }
        for (; newimpl.size_ < n; ++newimpl.size_) {
            new (newimpl.array_ + newimpl.size_) T();
        }
        swap(this->storage_, newimpl);
    }
}

template<typename T>
void my_vector<T>::reserve(std::size_t n) {
    if (n > storage_.capacity_) {
        my_vector_impl newimpl(n);
        for (; newimpl.size_ < storage_.size_; ++newimpl.size_) {
            new (newimpl.array_ + newimpl.size_) T(std::move(storage_.array_[newimpl.size_]));
        }
        swap(this->storage_, newimpl);
    }
}

template<typename T>
const T& my_vector<T>::operator[](std::size_t index) const {
    return storage_.array_[index];
}

template<typename T>
T& my_vector<T>::operator[](std::size_t index) {
    return storage_.array_[index];
}

template<typename T>
void my_vector<T>::push_back(T&& t) {
    if (storage_.size_ == storage_.capacity_) {
        if (storage_.capacity_ == 0) {
            reserve(1);
        } else {
            reserve(storage_.capacity_ * 2);
        }
    }
    new (storage_.array_ + storage_.size_) T(std::move(t));
    ++storage_.size_;
}

template<typename T>
void my_vector<T>::push_back(const T& t) {
    T x(t);
    if (storage_.size_ == storage_.capacity_) {
        if (storage_.capacity_ == 0) {
            reserve(1);
        } else {
            reserve(storage_.capacity_ * 2);
        }
    }
    new (storage_.array_ + storage_.size_) T(std::move(x));
    ++storage_.size_;
}

template<typename T>
void my_vector<T>::pop_back() noexcept {
    storage_.pop_back();
}

template<typename T>
void my_vector<T>::clear() noexcept {
    while (storage_.size_ > 0) {
        storage_.pop_back();
    }
}


} // namespace my_vector

#endif  // MY_VECTOR_IMPL_H_
