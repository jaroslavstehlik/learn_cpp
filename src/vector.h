//
// Created by Jaroslav Stehlik on 06.01.2024.
//
#include <cstring>

namespace mstr {
    template<typename T>
    class vector {
    private:
        T* array_ptr;
        int length_;

    public:

        explicit vector() {
            array_ptr = nullptr;
            length_ = 0;
        }

        explicit vector(int length) {
            array_ptr = new T[length];
            length_ = length;
        }

        explicit vector(int length, const T& value) {
            array_ptr = new T[length];
            length_ = length;
            for(int i = 0; i < length; i++) {
                array_ptr[i] = value;
            }
        }

        // copy constructor
        explicit vector(const vector& other) {
            array_ptr = new T[other.length_];
            length_ = other.length_;
            for(int i = 0; i < length_; i++) {
                array_ptr[i] = other.array_ptr[i];
            }
        }

        // move constructor
        explicit vector(vector&& other) noexcept {
            array_ptr = other->array_ptr;
            length_ = other->length_;
            other->Clear();
        }

        // assignment copy operator
        vector& operator=(const vector& other) {
            if(length_ == other.length_) {
                for(int i = 0; i < length_; i++) {
                    array_ptr[i] = other[i];
                }
                return *this;
            }

            this->Clear();
            if(other.length_ != 0)
            {
                this->array_ptr = new T[other.length_];
                for(int i = 0; i < other.length_; i++) {
                    this->array_ptr[i] = other.array_ptr[i];
                }
                // TODO:
            }

            this->length_ = other.length_;

            return *this;
        }

        /*
        // https://www.internalpointers.com/post/writing-custom-iterators-modern-cpp
        explicit vector(InputIt begin, int end) {

        }
         */

        T& operator[](int index) {
            return array_ptr[index];
        }

        const T& operator[](int index) const {
            return array_ptr[index];
        }

        int length() const {
            return length_;
        }

        void Clear() {
            if(!array_ptr)
                return;

            delete[] array_ptr;
            array_ptr = nullptr;
            length_ = 0;
        }

        ~vector() {
            Clear();
        }
    };
}