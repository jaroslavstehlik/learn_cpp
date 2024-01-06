//
// Created by Jaroslav Stehlik on 06.01.2024.
//

#ifndef BASICS_UNIQUE_POINTER_H
#define BASICS_UNIQUE_POINTER_H

namespace mstr {

    template<typename T>
    class unique_pointer {
    private:
        T* pointer_{nullptr};

    public:
        explicit unique_pointer(T* pointer) {
            pointer_ = pointer;
            std::cout << this << ", Constructed unique pointer" << std::endl;
        }

        // copy constructor is prohibited
        unique_pointer(const unique_pointer& other) = delete;
        // copy assignment operator is prohibited
        unique_pointer& operator=(unique_pointer& other) = delete;

        // move constructor
        unique_pointer(unique_pointer&& other) noexcept
        {
            if(this == other)
                return *this;

            this->pointer_ = other.pointer_;
            other.pointer_ = nullptr;

            std::cout << "Moved unique pointer from: " << other << ", to: " << this << std::endl;
        }

        // move assignment operator
        unique_pointer& operator=(unique_pointer&& other) noexcept
        {
            if(this == other)
                return *this;

            this->pointer_ = other.pointer_;
            other.pointer_ = nullptr;

            std::cout << "Moved unique pointer from: " << other << ", to: " << this << std::endl;
        }

        const T* Get() const {
            return pointer_;
        }

        void Reset(T* pointer)
        {
            if(pointer_ == pointer)
                return;

            delete pointer_;
            pointer_ = pointer;
            std::cout << this << ", Reset unique pointer" << std::endl;
        }

        ~unique_pointer<T>() {
            delete pointer_;
            pointer_ = nullptr;

            std::cout << this << ", Destructed unique pointer" << std::endl;
        }
    };
} // mstr

#endif //BASICS_UNIQUE_POINTER_H
