#pragma once

//
// Created by Jaroslav Stehlik on 06.01.2024.
//
#include <algorithm>

// the resize of the vector is not using capacity just for the sake of code simplicity

// TODO: implement custom iterator
// https://www.internalpointers.com/post/writing-custom-iterators-modern-cpp

namespace mstr {
    template<typename T>
    class vector {
    private:
        T* array_ptr{nullptr};
        std::size_t size_{0};
        std::allocator<T> allocator_;

    public:
        explicit vector() {
            array_ptr = nullptr;
            size_ = 0;
        }

        explicit vector(std::size_t size) {
            array_ptr = allocator_.allocate(size);
            size_ = size;
        }

        explicit vector(std::size_t size, const T& value) {
            array_ptr = allocator_.allocate(size);
            size_ = size;
            for(std::size_t i = 0; i < size; i++) {
                array_ptr[i] = value;
            }
        }

        // copy constructor
        vector(const vector& other) {
            array_ptr = allocator_.allocate(other.size_);
            size_ = other.size_;
            for(std::size_t i = 0; i < size_; i++) {
                array_ptr[i] = other.array_ptr[i];
            }
        }

        // move constructor
        vector(vector&& other) noexcept {
            array_ptr = other->array_ptr;
            other.array_ptr = nullptr;
            size_ = other->size_;
            other->size_ = 0;
        }

        // assignment copy operator
        vector& operator=(const vector& other) {
            if(this == &other)
                return *this;

            if(size_ == other.size_) {
                for(std::size_t i = 0; i < size_; i++) {
                    array_ptr[i] = other[i];
                }
                return *this;
            }

            this->clear();
            if(other.size_ > 0)
            {
                this->array_ptr = allocator_.allocate(other.size_);
                for(std::size_t i = 0; i < other.size_; i++) {
                    this->array_ptr[i] = other.array_ptr[i];
                }
            }

            this->size_ = other.size_;
            return *this;
        }

        // assignment move operator
        vector& operator=(vector&& other) noexcept {
            if(this == other)
                return *this;

            clear();

            array_ptr = other.array_ptr;
            other.array_ptr = nullptr;

            size_ = other.size_;
            other.size_ = 0;
            return *this;
        }

        T& operator[](std::size_t index) {
            return array_ptr[index];
        }

        const T& operator[](std::size_t index) const {
            return array_ptr[index];
        }

        void assign(const std::size_t index, const T& value) {
            array_ptr[index] = value;
        }

        const std::size_t size() const {
            return size_;
        }

        const bool empty() const {
            return size_ == 0;
        }

        void clear() {
            if(!array_ptr)
                return;

            allocator_.deallocate(array_ptr, size_);
            array_ptr = nullptr;
            size_ = 0;
        }

        void resize(std::size_t new_size) {
            if(size_ == new_size)
                return;

            T* array_candidate_ptr = allocator_.allocate(new_size);
            std::size_t min_array_size = std::min(new_size, size_);
            for(std::size_t i = 0; i < min_array_size; i++) {
                array_candidate_ptr[i] = std::move(array_ptr[i]);
            }

            allocator_.deallocate(array_ptr, size_);
            array_ptr = array_candidate_ptr;
            size_ = new_size;
        }

        void push_back(const T& value) {
            resize(size_ + 1);
            array_ptr[size_ - 1] = value;
        }

        void pop_back() {
            if(size_ == 0)
                return;

            resize(size_ - 1);
        }

        void insert(const T* array, std::size_t array_size) {
            std::size_t begin = size_;
            resize(size_ + array_size);
            for(std::size_t i = begin; i < size_; i++) {
                array_ptr[i] = array[i - begin];
            }
        }

        void insert(const vector& vector) {
            std::size_t begin = size_;
            resize(size_ + vector.size_);
            for(std::size_t i = begin; i < size_; i++) {
                array_ptr[i] = vector.array_ptr[i - begin];
            }
        }

        T& front() const {
            return array_ptr[0];
        }

        T& back() const  {
            return array_ptr[size_ - 1];
        }

        const T* data() const {
            return array_ptr;
        }

        ~vector() {
            clear();
        }
    };
}