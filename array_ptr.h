#pragma once
#include "algorithm"
#include "cstdlib"


namespace BMSTU{
    template <typename Type>
    class ArrayPtr{
    public:
        ArrayPtr() = default;

        explicit ArrayPtr(size_t size){
            if (size == 0){
                raw_ptr_ = nullptr;
            } else {
                raw_ptr_ = new Type[size];
            }
        }

        explicit ArrayPtr(Type *raw_ptr) noexcept {
            raw_ptr_ = raw_ptr;
        }

        ArrayPtr(const ArrayPtr&) = delete;

        [[nodiscard]] Type *Release() noexcept {
            auto ptr = raw_ptr_;
            raw_ptr_ = nullptr;
            return ptr;
        }

        Type &operator[](size_t index) noexcept {
            return raw_ptr_[index];
        }

        const Type &operator[](size_t index) const noexcept {
            return raw_ptr_[index];
        }

        explicit operator bool() const {
            return (raw_ptr_ != nullptr);
        }

        Type * Get() const noexcept {
            return raw_ptr_;
        }

        void SetRawPtr(Type *rawPtr) {
            raw_ptr_ = rawPtr;
        }

        void swap(ArrayPtr &other_array) noexcept {
            std::swap(raw_ptr_, other_array.raw_ptr_);
        }

        ~ArrayPtr(){
            delete [] raw_ptr_;
            raw_ptr_ = nullptr;
        }

    private:
        Type * raw_ptr_ = nullptr;
    };
}