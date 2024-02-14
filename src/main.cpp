#include <iostream>
#include "unique_pointer.h"
#include "shared_pointer.h"
#include "vector.h"
#include "string/m_string.h"
#include <gtest/gtest.h>

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

TEST(HelloTest, TestVector) {
    mstr::vector<int> vector_empty{};
    ASSERT_EQ(vector_empty.size(), 0);

    mstr::vector<int> vector_uninitialized(10);
    ASSERT_EQ(vector_uninitialized.size(), 10);

    mstr::vector<int> vector_initialized(10, 5);
    ASSERT_EQ(vector_initialized.size(), 10);
    for(int i = 0; i < 10; i++) {
        ASSERT_EQ(vector_initialized[i], 5);
    }

    mstr::vector<int> vector_push{};
    for(int i = 0; i < 10; i++) {
        vector_push.push_back(i);
        ASSERT_EQ(vector_push[i], i);
    }
    ASSERT_EQ(vector_push.size(), 10);

    for(int i = 9; i > -1; i--) {
        ASSERT_EQ(vector_push.back(), i);
        vector_push.pop_back();
    }
    ASSERT_EQ(vector_push.size(), 0);
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