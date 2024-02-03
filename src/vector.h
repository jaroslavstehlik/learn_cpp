//
// Created by Jaroslav Stehlik on 06.01.2024.
//
#include <algorithm>

// the resize of the vector is not using capacity just for the sake of code simplicity

namespace mstr {
    template<typename T>
    class vector {
    private:
        T* array_ptr{nullptr};
        std::size_t length_{0};

    public:
        explicit vector() {
            array_ptr = nullptr;
            length_ = 0;
        }

        explicit vector(std::size_t length) {
            array_ptr = new T[length];
            length_ = length;
        }

        explicit vector(std::size_t length, const T& value) {
            array_ptr = new T[length];
            length_ = length;
            for(std::size_t i = 0; i < length; i++) {
                array_ptr[i] = value;
            }
        }

        // copy constructor
        explicit vector(const vector& other) {
            array_ptr = new T[other.length_];
            length_ = other.length_;
            for(std::size_t i = 0; i < length_; i++) {
                array_ptr[i] = other.array_ptr[i];
            }
        }

        // move constructor
        explicit vector(vector&& other) noexcept {
            array_ptr = other->array_ptr;
            other.array_ptr = nullptr;
            length_ = other->length_;
            other->length_ = 0;
        }

        // assignment copy operator
        vector& operator=(const vector& other) {
            if(length_ == other.length_) {
                for(std::size_t i = 0; i < length_; i++) {
                    array_ptr[i] = other[i];
                }
                return *this;
            }

            this->clear();
            if(other.length_ > 0)
            {
                this->array_ptr = new T[other.length_];
                for(std::size_t i = 0; i < other.length_; i++) {
                    this->array_ptr[i] = other.array_ptr[i];
                }
            }

            this->length_ = other.length_;
            return *this;
        }

        // assignment move operator
        vector& operator=(vector&& other) {
            if(this == other)
                return *this;
            clear();

            array_ptr = other.array_ptr;
            other.array_ptr = nullptr;

            length_ = other.length_;
            other.length_ = 0;
            return *this;
        }

        /*
        // https://www.internalpointers.com/post/writing-custom-iterators-modern-cpp
        explicit vector(InputIt begin, std::size_t end) {

        }
         */

        T& operator[](std::size_t index) {
            return array_ptr[index];
        }

        const T& operator[](std::size_t index) const {
            return array_ptr[index];
        }

        std::size_t length() const {
            return length_;
        }

        void clear() {
            if(!array_ptr)
                return;

            delete[] array_ptr;
            array_ptr = nullptr;
            length_ = 0;
        }

        void resize(std::size_t new_length) {
            if(length_ == new_length)
                return;

            T* array_candidate_ptr = new T[new_length];
            std::size_t min_array_length = std::min(new_length, length_);
            for(std::size_t i = 0; i < min_array_length; i++) {
                array_candidate_ptr[i] = std::move(array_ptr[i]);
            }
            delete[] array_ptr;
            array_ptr = array_candidate_ptr;
            length_ = new_length;
        }

        void push_back(const T& value) {
            resize(length_ + 1);
            array_ptr[length_ - 1] = value;
        }

        void pop_back() {
            if(length_ == 0)
                return;

            resize(length_ - 1);
        }

        void insert(const T* array, std::size_t array_length) {
            std::size_t begin = length_;
            resize(length_ + array_length);
            for(std::size_t i = begin; i < length_; i++) {
                array_ptr[i] = array[i - begin];
            }
        }

        void insert(const vector& vector) {
            std::size_t begin = length_;
            resize(length_ + vector.length_);
            for(std::size_t i = begin; i < length_; i++) {
                array_ptr[i] = vector.array_ptr[i - begin];
            }
        }

        ~vector() {
            clear();
        }
    };
}