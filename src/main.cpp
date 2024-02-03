#include <iostream>
#include <memory>

#include "unique_pointer.h"
#include "shared_pointer.h"
#include "vector.h"
#include "string/m_string.h"

void TestSharedPointer() {
    std::cout << "TestSharedPointer" << std::endl;
    mstr::shared_pointer<float> shared_pointer_a(mstr::shared_pointer<float>(new float(5.f)));
    mstr::shared_pointer<float> shared_pointer_b(shared_pointer_a);
    mstr::shared_pointer<float> shared_pointer_c(mstr::shared_pointer<float>(new float(5.f)));
    shared_pointer_c = shared_pointer_b;
}

void TestUniquePointer() {
    std::cout << "TestUniquePointer" << std::endl;
    mstr::unique_pointer<float> my_pointer = mstr::unique_pointer<float>(new float(3));
    std::cout << my_pointer.Get() << std::endl;
    my_pointer.Reset(nullptr);
    std::cout << my_pointer.Get() << std::endl;
    my_pointer.Reset(new float(5));
    std::cout << my_pointer.Get() << std::endl;
}

void TestVector() {
    mstr::vector<int> vector_a{};
    mstr::vector<int> vector_b(10);
    mstr::vector<int> vector_c(10, 5);
    mstr::vector<int> vector_d(vector_a);
    vector_c = vector_b;
}

void TestString() {
    std::cout << "TestString" << std::endl;
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
    TestSharedPointer();
    TestVector();
    TestString();
    return 0;
}
