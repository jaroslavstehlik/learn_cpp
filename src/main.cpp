#include <iostream>
#include <memory>

#include "unique_pointer.h"
#include "string/m_string.h";

void TestUniquePointer() {
    mstr::unique_pointer<float> my_pointer = mstr::unique_pointer<float>(new float(3));
    std::cout << my_pointer.Get() << std::endl;
    my_pointer.Reset(nullptr);
    std::cout << my_pointer.Get() << std::endl;
    my_pointer.Reset(new float(5));
    std::cout << my_pointer.Get() << std::endl;
}

void TestString() {
    string original_string("prdelka");
    std::cout << original_string.c_string() << std::endl;

    string copied_string_via_copy_constructor(original_string);
    std::cout << copied_string_via_copy_constructor.c_string() << std::endl;

    string moved_string_via_move_constructor(std::move(copied_string_via_copy_constructor));
    std::cout << moved_string_via_move_constructor.c_string() << std::endl;

    if (copied_string_via_copy_constructor.length() == 0 && copied_string_via_copy_constructor.c_string() == nullptr) {
        std::cout << "moving passed" << std::endl;
    }
    else {
        std::cout << "moving failed" << std::endl;
    }

    string copied_string_via_copy_assignment = moved_string_via_move_constructor;
    std::cout << copied_string_via_copy_assignment.c_string() << std::endl;

    string moved_string_via_move_assignment = std::move(copied_string_via_copy_assignment);
    std::cout << moved_string_via_move_assignment.c_string() << std::endl;

    if (copied_string_via_copy_assignment.length() == 0 && copied_string_via_copy_assignment.c_string() == nullptr) {
        std::cout << "moving passed" << std::endl;
    }
    else {
        std::cout << "moving failed" << std::endl;
    }
}

int main() {

    TestUniquePointer();
    TestString();

    return 0;
}
