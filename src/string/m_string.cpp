#include "m_string.h"

#include <cstring>
#include <iostream>

string::string() {}

string::string(const char* value) {
    string_length = strlen(value);
    string_array_ = new char[string_length + 1];
    strcpy(string_array_, value);

    std::cout << this << ", construct string: "<< string_array_ << std::endl;
}

string::~string() {
    std::cout << this << ", destruct string: " << string_array_ << std::endl;

    delete[] string_array_;
    string_array_ = nullptr;
    string_length = 0;
}

const char* string::c_string() const {
    return string_array_;
}

int string::length() const {
    return string_length;
}

// copy constructor
string::string(const string& rhs) {
    this->string_length = rhs.string_length;
    this->string_array_ = new char[rhs.string_length + 1];
    strcpy(string_array_, rhs.string_array_);

    std::cout << "copy string constructor: " << string_array_ << ", from: " << &rhs << ", to: " << this << std::endl;
}

// move constructor
string::string(string&& rhs) noexcept {
    this->string_length = rhs.string_length;
    this->string_array_ = rhs.string_array_;

    rhs.string_array_ = nullptr;
    rhs.string_length = 0;

    std::cout << "move string constructor: " << string_array_ << ", from: " << &rhs << ", to: " << this << std::endl;
}

// copy assignment operator
string& string::operator=(const string& rhs) {
    if (this == &rhs)
        return *this;

    this->string_length = rhs.string_length;
    this->string_array_ = new char[rhs.string_length + 1];
    strcpy(this->string_array_, rhs.string_array_);

    std::cout << "copy string assignment: " << string_array_ << ", from: " << &rhs << ", to: " << this << std::endl;

    return *this;
}

// move assignment operator
string& string::operator=(string&& rhs) noexcept {
    if (this == &rhs)
        return *this;

    this->string_length = rhs.string_length;
    this->string_array_ = rhs.string_array_;

    rhs.string_array_ = nullptr;
    rhs.string_length = 0;

    std::cout << "move string assignment: " << string_array_ << ", from: " << &rhs << ", to: " << this << std::endl;

    return *this;
}