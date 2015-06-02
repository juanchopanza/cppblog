#ifndef CPPBLOG_VALUE_PTR_HPP_
#define CPPBLOG_VALUE_PTR_HPP_
//
// Copyright (c) 2015 Juan Palacios juan.palacios.puyana@gmail.com
// Subject to the BSD 2-Clause License
// - see < http://opensource.org/licenses/BSD-2-Clause>
//

#include <algorithm> // C++03 std::swap

namespace blg
{
/// A trivial (and incomplete) C++03 value pointer example.
///
/// Requires T to have a T* T::clone() member function.
/// Intended for polymorphic types where value semantics are required.
///
template <typename T>
struct value_ptr
{
    typedef T* pointer;
    typedef T& reference;

    explicit value_ptr(pointer p) : ptr_(p) {}

    value_ptr(const value_ptr& other) : ptr_(other->clone()) {}

    value_ptr& operator=(value_ptr rhs) {
        swap(rhs);
        return *this; 
    }

    ~value_ptr() { delete ptr_; }

    reference operator*() const { return *get(); }

    pointer operator->() const { return get(); }

    pointer get() const { return ptr_; }

    pointer release()
    {
        pointer old = ptr_;
        ptr_ = NULL;
        return old;
    }

    void reset(pointer p = pointer())
    {
        std::swap(p, ptr_);
        delete p;
    }

    void swap(value_ptr& other) { std::swap(ptr_, other.ptr_); }

 private:
    pointer ptr_;
};

} // namespace blg

#endif
