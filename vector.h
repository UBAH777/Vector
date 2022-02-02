#pragma once

#include "array_ptr.h"
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <ostream>


namespace BMSTU{
    template<typename Type>
    class Vector{
    public:
        using Iterator = Type *;
        using ConstIterator = const Type *;

        Vector() = default;

        Vector(size_t size, const Type &value) : _size(size), _capacity(size), _data(size) {
            std::fill(begin(), end(), value);
        }

        Vector(const BMSTU::Vector<Type> &other) noexcept : Vector(other.GetSize(),0) {
            std::copy(other.cbegin(), other.cend(), begin());
        }

        BMSTU::Vector<Type>& operator=(BMSTU::Vector<Type>& other) noexcept {
            std::copy(other.cbegin(), other.cend(), begin());
            return *this;
        }

        Vector(BMSTU::Vector<Type> && other) {
            if (this != &other) {
                delete[] _data.Get();
                _size = other.GetSize();
                _capacity = other.GetCapacity();
                _data = other._data;
                other.SetSize(0);
                other.SetCapacity(0);
                other._data.SetRawPtr(nullptr);
            }
        }

        Vector& operator=(Vector&& other) noexcept {
            if (this != &other) {
                delete[] _data.Get();
                _size = other.GetSize();
                _capacity = other.GetCapacity();
                _data = other._data;
                other.SetSize(0);
                other.SetCapacity(0);
                other._data.SetRawPtr(nullptr);
            }
            return *this;
        }

        Vector(std::initializer_list<Type> init) {
            Vector<Type> tmp(0,0);
            for (const auto &val : init) {
                tmp.PushBack(val);
            }
            swap(tmp);
        }

        Iterator begin() {
            return _data.Get();
        }

        Iterator end() {
            return _data.Get() + _size;
        }

        ConstIterator cbegin() const {
            return _data.Get();
        }

        ConstIterator cend() const {
            return _data.Get() + _size;
        }

        size_t GetSize() const noexcept {
            return _size;
        }

        size_t GetCapacity() const noexcept {
            return _capacity;
        }

        void Reserve(size_t new_capacity){
            if (new_capacity > _capacity){
                ArrayPtr<Type> tmp(new_capacity);
                std::move(begin(), end(), tmp.Get());
                _data.swap(tmp);
                _capacity = new_capacity;
            }
        }

        void PushBack(const Type &value){
            auto tmp = value;
            PushBack(std::move(tmp));
        }

        void PushBack(Type &&value){
            Insert(end(), std::move(value));
        }

        void PopBack() noexcept {
            _size--;
        }

        void swap(BMSTU::Vector<Type> &other) noexcept {
            size_t tmp;
            tmp = this->GetSize();
            _size = other.GetSize();
            other._size = tmp;

            tmp = this->GetCapacity();
            _capacity = other.GetCapacity();
            other._capacity = tmp;

            _data.swap(other._data);
        }


        friend void swap(BMSTU::Vector<Type> &lhs, BMSTU::Vector<Type> &rhs) noexcept {
            lhs.swap(rhs);
        }

        Type& operator[](size_t index) noexcept {
            return _data[index];
        }

    private:
        Iterator Insert(ConstIterator pos, const Type &value){
            Type copy_value = value;
            return Insert(pos, std::move(copy_value));
        }

        Iterator Insert(ConstIterator pos, Type &&value){
            size_t n = pos - begin();
            if (_capacity == 0){
                Reserve(1);
            }
            if (_size == _capacity){
                _capacity *= 2;
            }
            ArrayPtr<Type> temp(_capacity);
            std::move(begin(), begin() + n, temp.Get());
            std::move_backward(begin() + n, begin() + _size, temp.Get() + _size + 1);
            temp[n] = std::move(value);
            _data.swap(temp);
            _size++;
            return begin() + n;
        }

        void SetSize(size_t size) {
            _size = size;
        }

        void SetCapacity(size_t capacity) {
            _capacity = capacity;
        }

    private:
        size_t _size;
        size_t _capacity;
        ArrayPtr<Type> _data;
    };
}