#include <iostream>
#include "unique_pointer.h"
#include "shared_pointer.h"
#include "vector.h"
#include "string/m_string.h"
#include <gtest/gtest.h>

TEST(HelloTest, TestSharedPointer) {
    mstr::shared_pointer<float> shared_pointer_a(mstr::shared_pointer<float>(new float(5.f)));
    ASSERT_TRUE(shared_pointer_a);
    ASSERT_NE(shared_pointer_a.Get(), nullptr);
    ASSERT_EQ(*shared_pointer_a.Get(), 5.f);
    ASSERT_EQ(shared_pointer_a.ReferenceCount(), 1);

    // copy constructor
    mstr::shared_pointer<float> shared_pointer_b(shared_pointer_a);
    ASSERT_TRUE(shared_pointer_a);
    ASSERT_NE(shared_pointer_a.Get(), nullptr);
    ASSERT_EQ(*shared_pointer_a.Get(), 5.f);
    ASSERT_EQ(shared_pointer_a.ReferenceCount(), 2);

    ASSERT_TRUE(shared_pointer_b);
    ASSERT_NE(shared_pointer_b.Get(), nullptr);
    ASSERT_EQ(*shared_pointer_b.Get(), 5.f);
    ASSERT_EQ(shared_pointer_b.ReferenceCount(), 2);
    ASSERT_EQ(shared_pointer_a.ReferenceCount(), shared_pointer_b.ReferenceCount());

    mstr::shared_pointer<float> shared_pointer_c(mstr::shared_pointer<float>(new float(3.f)));
    ASSERT_TRUE(shared_pointer_c);
    ASSERT_NE(shared_pointer_c.Get(), nullptr);
    ASSERT_EQ(*shared_pointer_c.Get(), 3.f);
    ASSERT_EQ(shared_pointer_c.ReferenceCount(), 1);

    // copy assignment
    shared_pointer_c = shared_pointer_b;
    ASSERT_TRUE(shared_pointer_b);
    ASSERT_NE(shared_pointer_b.Get(), nullptr);
    ASSERT_EQ(*shared_pointer_b.Get(), 5.f);
    ASSERT_EQ(shared_pointer_b.ReferenceCount(), 3);

    ASSERT_TRUE(shared_pointer_c);
    ASSERT_NE(shared_pointer_c.Get(), nullptr);
    ASSERT_EQ(*shared_pointer_c.Get(), 5.f);
    ASSERT_EQ(shared_pointer_c.ReferenceCount(), 3);

    // Reset c
    shared_pointer_c.Reset();
    std::cout << shared_pointer_c.Get() << std::endl;
    ASSERT_FALSE(shared_pointer_c);
    ASSERT_EQ(shared_pointer_c.Get(), nullptr);
    ASSERT_EQ(shared_pointer_c.ReferenceCount(), 0);

    ASSERT_TRUE(shared_pointer_b);
    ASSERT_NE(shared_pointer_b.Get(), nullptr);
    ASSERT_EQ(*shared_pointer_b.Get(), 5.f);
    ASSERT_EQ(shared_pointer_b.ReferenceCount(), 2);

    // Reset b
    shared_pointer_b.Reset();
    ASSERT_TRUE(shared_pointer_a);
    ASSERT_NE(shared_pointer_a.Get(), nullptr);
    ASSERT_EQ(*shared_pointer_a.Get(), 5.f);
    ASSERT_EQ(shared_pointer_a.ReferenceCount(), 1);

    // Reset a
    shared_pointer_a.Reset();
    ASSERT_FALSE(shared_pointer_a);
    ASSERT_EQ(shared_pointer_a.Get(), nullptr);
    ASSERT_EQ(shared_pointer_a.ReferenceCount(), 0);
}

TEST(HelloTest, TestUniquePointer) {
    mstr::unique_pointer<float> my_pointer = mstr::unique_pointer<float>(new float(3.f));
    ASSERT_TRUE(my_pointer);
    ASSERT_NE(my_pointer.Get(), nullptr);
    ASSERT_EQ(*my_pointer.Get(), 3.f);
    ASSERT_NE(*my_pointer.Get(), 1.f);

    my_pointer.Reset(nullptr);
    ASSERT_FALSE(my_pointer);
    ASSERT_EQ(my_pointer.Get(), nullptr);

    my_pointer.Reset(new float (5.f));
    ASSERT_TRUE(my_pointer);
    ASSERT_NE(my_pointer.Get(), nullptr);
    ASSERT_EQ(*my_pointer.Get(), 5.f);
    ASSERT_NE(*my_pointer.Get(), 1.f);
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