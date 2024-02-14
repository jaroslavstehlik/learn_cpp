#include <iostream>
#include <memory>

#include "unique_pointer.h"
#include "shared_pointer.h"
#include "vector.h"
#include "string/m_string.h"
#include "test.h"

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

void PrintVector(const char* name, const mstr::vector<int>& vector) {
    std::string output{};
    for(int i = 0; i < vector.size(); i++)
    {
        output += std::to_string(vector[i]);
        output += ",";
    }
    std::cout << name << ": " << output << std::endl;
}

void TestVector() {
    mstr::vector<int> vector_empty{};
    PrintVector("vector_empty", vector_empty);

    mstr::vector<int> vector_uninitialized(10);
    PrintVector("vector_uninitialized", vector_uninitialized);

    mstr::vector<int> vector_initialized(10, 5);
    PrintVector("vector_initialized", vector_initialized);

    mstr::vector<int> vector_copied(vector_empty);
    PrintVector("vector_copied", vector_copied);

    vector_uninitialized = vector_initialized;
    PrintVector("vector_uninitialized", vector_uninitialized);

    vector_uninitialized.push_back(1);
    vector_uninitialized.push_back(2);
    vector_uninitialized.push_back(3);
    vector_uninitialized.push_back(4);
    PrintVector("vector_pushed_back", vector_uninitialized);
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

    TestMain();
    return 0;
}
