//
// Created by Jaroslav Stehlik on 06.01.2024.
//

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
            this->pointer_ = other.Release();
            std::cout << "Moved unique pointer from: " << other << ", to: " << this << std::endl;
        }

        // move assignment operator
        unique_pointer& operator=(unique_pointer&& other) noexcept {
            if(this == other)
                return *this;

            this->pointer_ = other.Release();
            std::cout << "Moved unique pointer from: " << other << ", to: " << this << std::endl;
        }

        explicit operator bool() const noexcept {
            return pointer_ != nullptr;
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

        void Reset() {
            Reset(nullptr);
        }

        const T* Release() {
            T* output = pointer_;
            Reset();
            return output;
        }

        ~unique_pointer() {
            Reset();
            std::cout << this << ", Destructed unique pointer" << std::endl;
        }
    };
} // mstr
