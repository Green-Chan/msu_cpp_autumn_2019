#pragma once
#include <iterator>
#include <memory>

template <class T>
class Allocator
{
public:
    using value_type = T;
    using pointer = T*;
    using size_type = size_t;
    pointer allocate(size_type n) {
        return static_cast<pointer> (::operator new(n * sizeof(value_type)));
    }

    void deallocate(pointer ptr, size_type sz) {
        ::operator delete[](ptr, sizeof(value_type) * sz);
    }

    template<class ... Args>
    void construct(pointer ptr, Args&&... args) {
        ::new(ptr) value_type(std::forward<Args>(args)...);
    }

    void destroy(pointer ptr) {
        ptr->~value_type();
    }
};

template <class T>
class Iterator
{
public:
    using reference = T&;
    using pointer = T*;
    Iterator(pointer p, bool is_rev) {
        ptr = p;
        rev = is_rev;
    }
    Iterator(pointer p) {
        ptr = p;
    }

    reference operator*() const {
        return *ptr;
    }

    Iterator& operator[](int val) {
        return *(ptr + val);
    }

    bool operator==(const Iterator& a) const {
        return ptr == a.ptr;
    }

    bool operator!=(const Iterator& a) const {
        return ptr != a.ptr;
    }

    bool operator < (const Iterator& a) const {
        if (rev) {
            ptr > a.ptr;
        }
        return ptr < a.ptr;
    }

    bool operator > (const Iterator& a) const {
        if (rev) {
            ptr < a.ptr;
        }
        return ptr > a.ptr;
    }

    bool operator >= (const Iterator& a) const {
        if (rev) {
            ptr <= a.ptr;
        }
        return ptr >= a.ptr;
    }

    bool operator <= (const Iterator& a) const {
        if (rev) {
            ptr >= a.ptr;
        }
        return ptr <= a.ptr;
    }

    Iterator& operator++() {
        if (rev) {
            ptr--;
        } else {
            ptr++;
        }
        return *this;
    }

    Iterator& operator--() {
        if (rev) {
            ptr++;
        } else {
            ptr--;
        }
        return *this;
    }

    Iterator& operator+=(int n) {
        if (rev) {
            ptr -= n;
        } else {
            ptr += n;
        }
        return *this;
    }

    Iterator& operator-=(int n) {
        if (rev) {
            ptr += n;
        } else {
            ptr -= n;
        }
        return *this;
    }

private:
    pointer ptr;
    bool rev;
};

template <class T, class Alloc = Allocator<T>>
class Vector
{
public:
    using iterator = Iterator<T>;
    using value_type = T;
    using pointer = T*;
    using size_type = size_t;
    using reference = T&;
    Vector(size_type vec_size = 0) {
        v_size = vec_size;
        if (v_size > 0) {
            real_size = v_size;
        }
        data = alloc.allocate(real_size);
        for (size_type i = 0; i < v_size; ++i) {
            alloc.construct(data + i);
        }
    }

    ~Vector() {
        for (auto i = data; i != data + v_size; i++) {
            alloc.destroy(i);
        }
        alloc.deallocate(data, real_size);
    }

    reference operator[] (size_type n) {
        if (n >= v_size) {
            throw std::out_of_range("Out of range");
        }
        return data[n];
    }
    const reference operator[] (size_type n) const {
        if (n >= v_size)
            throw std::out_of_range("Out of range");
        return data[n];
    }

    void push_back(value_type&& value) {
        if (v_size == real_size) {
            reserve(real_size * 2);
        }
        data[v_size++] = std::move(value);
    }
    void push_back(const value_type& value) {
        if (v_size == real_size) {
            reserve(real_size * 2);
        }
        new (data + v_size++) value_type(value);
    }

    void pop_back()
    {
        if (v_size > 0) {
            alloc.destroy(data + --v_size);
        }
    }

    bool empty() const {
        return v_size == 0;
    }

    size_type size() const {
        return v_size;
    }

    size_type capacity() const {
        return real_size;
    }

    void clear() noexcept {
        resize(0);
    }

    iterator begin() const noexcept {
        return iterator(data, false);
    }

    iterator end() const noexcept {
        return iterator(data + v_size, false);
    }

    iterator rbegin() const noexcept {
        return iterator(data + v_size - 1, true);
    }

    iterator rend() const noexcept {
        return iterator(data - 1, true);
    }

    void resize(size_type n) {
        if (real_size < n) {
            reserve(n);
        }
        for (size_type i = n; i < v_size; i++) {
            alloc.destroy(data + i);
        }
        for (size_type i = v_size; i < n; i++) {
            alloc.construct(data + i);
        }
        v_size = n;
    }

    void reserve(size_type n) {
        pointer new_data = alloc.allocate(n);
        for (size_type i = 0; i < real_size; ++i) {
            alloc.construct(new_data + i, *(data + i));
            alloc.destroy(data + i);
        }
        alloc.deallocate(data, real_size);
        data = new_data;
        real_size = n;
    }

private:
    size_type v_size, real_size = 1;
    pointer data;
    Alloc alloc;
};
