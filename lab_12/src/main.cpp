#include <iostream>
#include <utility>
#include <cstring>
#include <cassert>

#include "my_vector.h"

namespace product {

class Product {
public:
    Product() = delete;
    Product(const char* name, int quantity, double price)
    : quantity_(quantity)
    , price_(price) {
        name_ = new char[strlen(name) + 1];
        strcpy(name_, name);
    }
    Product(const Product& p) 
    : quantity_(p.quantity_)
    , price_(p.price_) {
        name_ = new char[strlen(p.name_) + 1];
        strcpy(name_, p.name_);
    }
    ~Product() {
        delete[] name_;
    }

    friend std::ostream& operator<<(std::ostream& os, const Product& p) {
        return os << p.name_ << ' ' << p.quantity_ << ' ' << p.price_;
    }

    friend bool operator==(const Product& lhs, const Product& rhs) {
        if (strcmp(lhs.name_, rhs.name_) != 0) {
            return false;
        }
        if (lhs.price_ != rhs.price_ || lhs.quantity_ != rhs.quantity_) {
            return false;
        }
        return true;
    }

private:
    char *name_;  // Указатель владеет C-style строкой, на которую указывает.
    int quantity_;
    double price_;
};

void print(const my_vector::my_vector<Product>& v) {
    std::cout << v << std::endl;
}

}  // namespace product

namespace {

template<typename T>
void test_my_vector(T a, T b) {
    { // Check Default constructor creates my_vector with size == 0 and capacity == 1
    my_vector::my_vector<T> v;
    assert(v.size() == 0 && v.capacity() == 0);
    }

    { // Check Copy constructor creates a copy..
    my_vector::my_vector<T> empty;
    my_vector::my_vector<T> v;
    v.push_back(b);
    assert(empty.size() != v.size());
    my_vector::my_vector<T> copy(v);
    assert(copy.size() == v.size() && copy.capacity() == v.capacity());
    }

    { // Check Move constructor
    my_vector::my_vector<T> v;
    v.push_back(b);
    v.push_back(a);
    my_vector::my_vector<T> moved(std::move(v));
    assert(v.size() == 0 && v.capacity() == 0);
    assert(moved.size() == 2 && moved.capacity() == 2);
    }

    { // Check operator= copy
    my_vector::my_vector<T> v;
    v.push_back(b);
    v.push_back(a);
    my_vector::my_vector<T> copy;
    copy.push_back(a);
    copy = v;
    assert(v.size() == copy.size() && v.capacity() == copy.capacity());
    }

    { // Check operator= move
    my_vector::my_vector<T> v;
    v.push_back(b);
    v.push_back(a);
    my_vector::my_vector<T> moved;
    moved.push_back(a);
    moved = std::move(v);
    assert(v.size() == 1 && v.capacity() == 1);
    assert(moved.size() == 2 && moved.capacity() == 2);
    }

    { // Check empty() is correct
    my_vector::my_vector<T> v;
    assert(v.empty());
    v.push_back(a);
    assert(!v.empty());
    }

    { // Check reserve()
    my_vector::my_vector<T> v;
    v.reserve(10);
    assert(v.size() == 0 && v.capacity() == 16);
    v.reserve(10);
    assert(v.size() == 0 && v.capacity() == 16);
    v.reserve(1);
    assert(v.size() == 0 && v.capacity() == 16);
    }

    { // Check operator[] and push_back()
    my_vector::my_vector<T> v;
    for (int k = 0; k < 100; ++k) {
        v.push_back(a);
        assert(v[k] == a);
    }
    assert(v.size() == 100 && v.capacity() == 128);
    }

    { // Check operator[]
    my_vector::my_vector<T> v;
    for (int k = 0; k < 100; ++k) {
        v.push_back(a);
        assert(v[k] == a);
    }
    assert(v.size() == 100 && v.capacity() == 128);
    }

    { // Check pop_back()
    my_vector::my_vector<T> v;
    for (int k = 0; k < 100; ++k) {
        v.push_back(a);
        v.pop_back();
        assert(v.empty());
    }
    }

    { // Check clear()
    my_vector::my_vector<T> v;
    for (int k = 0; k < 100; ++k) {
        v.push_back(a);
    }
    v.clear();
    assert(v.size() == 0 && v.capacity() == 128);
    }
}

template<typename T>
void test_my_vector_default_constructible(T a, T b) {
    test_my_vector(a, b);

    { // Check constructor(size_t)
    my_vector::my_vector<T> v(100);
    assert(v.size() == 100 && v.capacity() == 128);
    assert(v[7] == 0 && v[99] == 0);
    }

    { // Check resize() increase
    my_vector::my_vector<T> v;
    v.resize(100);
    assert(v.size() == 100 && v.capacity() == 128);
    assert(v[7] == 0 && v[99] == 0);
    }

    { // Check resize() decrease
    my_vector::my_vector<T> v(100);
    v.resize(1);
    assert(v.size() == 1 && v.capacity() == 128);
    }
}

} // namespace


int main() {
    test_my_vector_default_constructible<int>(5, 10);
    test_my_vector<product::Product>(product::Product("asdf", 4, 12.0), product::Product("qwe", -1, 7.5));

    return 0;
}
