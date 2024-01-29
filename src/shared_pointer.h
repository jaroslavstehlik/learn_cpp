//
// Created by Jaroslav Stehlik on 07.01.2024.
//

namespace mstr {

    template <typename T>
    class shared_pointer {
    private:
        int* reference_counter_{nullptr};
        T* pointer_{nullptr};

        void Clear()
        {
            delete reference_counter_;
            reference_counter_ = nullptr;

            delete pointer_;
            pointer_ = nullptr;

            std::cout << this << ", cleared reference counter" << std::endl;
        }

        void IncrementReferenceCounter() {
            if(!reference_counter_)
                reference_counter_ = new int(0);
            (*reference_counter_)++;
        }

        void DecrementReferenceCounter() {
            if(!reference_counter_ ||
                *reference_counter_ == 0)
                return;

            (*reference_counter_)--;
            if(*reference_counter_ == 0)
                this->Clear();
        }

        int ReferenceCount() {
            if(!reference_counter_)
                return 0;

            return (*reference_counter_);
        }

    public:
        explicit shared_pointer(T* pointer) {
            pointer_ = pointer;

            if(!reference_counter_)
                reference_counter_ = new int();

            IncrementReferenceCounter();
            std::cout << this << ", constructed reference counter, reference count:" << ReferenceCount() << std::endl;
        }

        // copy constructor
        shared_pointer(const shared_pointer& other) {
            this->reference_counter_ = other.reference_counter_;
            this->pointer_ = other.pointer_;

            IncrementReferenceCounter();
            std::cout << this << ", constructed reference counter via copy constructor, reference count:" << ReferenceCount() << std::endl;
        }

        // copy assignment operator
        shared_pointer& operator= (shared_pointer& other) {
            if(this == &other)
                return *this;

            if(this->reference_counter_ != other.reference_counter_) {
                this->DecrementReferenceCounter();
            }

            this->reference_counter_ = other.reference_counter_;
            this->pointer_ = other.pointer_;

            this->IncrementReferenceCounter();
            std::cout << this << ", copied reference counter via copy assigment, reference count:" << ReferenceCount() << std::endl;

            return *this;
        }

        // move constructor
        shared_pointer(shared_pointer&& other) noexcept {
            this->reference_counter_ = other.reference_counter_;
            this->pointer_ = other.pointer_;

            // invalidate other
            other.Reset();
            std::cout << this << ", moved reference counter via move constructor, reference count:" << ReferenceCount() << std::endl;
        }

        // move assignment operator
        shared_pointer& operator= (shared_pointer&& other) {
            if(this == other)
                return *this;

            this->reference_counter_ = other.reference_counter_;
            this->pointer_ = other.pointer_;

            other.reference_counter_ = nullptr;
            other.pointer_ = nullptr;

            std::cout << this << ", moved reference counter via move assigment, reference count:" << ReferenceCount() << std::endl;

            return *this;
        }

        explicit operator bool() const noexcept {
            return pointer_ != nullptr;
        }

        const T* Get() const {
            return pointer_;
        }

        void Reset(T* pointer) {
            if(this->pointer_ == pointer)
                return;

            this->DecrementReferenceCounter();

            if(pointer)
            {
                this->pointer_ = pointer;
                this->IncrementReferenceCounter();
            }
        }

        void Reset() {
            Reset(nullptr);
        }

        ~shared_pointer() {
            // decrement reference counter
            this->DecrementReferenceCounter();
        }
    };
}