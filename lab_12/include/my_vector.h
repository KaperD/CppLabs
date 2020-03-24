#ifndef MY_VECTOR_H_
#define MY_VECTOR_H_

#include <cstddef>
#include <iosfwd>

namespace my_vector {

template<typename T>
class my_vector {
public:
    my_vector();
    explicit my_vector(std::size_t n);
    my_vector(const my_vector& other);
    my_vector(my_vector&& other) noexcept;
    my_vector& operator=(const my_vector& other);
    my_vector& operator=(my_vector&& other) noexcept;
    ~my_vector() = default;

    std::size_t size() const noexcept;
    std::size_t capacity() const noexcept;
    bool empty() const noexcept;

    void resize(std::size_t n);
    void reserve(std::size_t n);

    const T& operator[](std::size_t index) const;
    T& operator[](std::size_t index);

    void push_back(T&& t);
    void push_back(const T& t);
    void pop_back() noexcept;
    void clear() noexcept;

private:
    struct my_vector_impl {
        my_vector_impl();
        my_vector_impl(size_t n);
        ~my_vector_impl() noexcept;

        my_vector_impl(const my_vector_impl&) = delete;
        my_vector_impl& operator=(const my_vector_impl&) = delete;

        void pop_back() noexcept;

        size_t capacity_;
        size_t size_;
        T* array_;
    };

    static void swap(my_vector_impl& lhs, my_vector_impl& rhs) noexcept;

    my_vector_impl storage_;
};

} // namespace my_vector

#include "my_vector_impl.h"

#endif  // MY_VECTOR_H_
