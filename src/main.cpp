#include <iostream>
#include "unique_pointer.h"
#include "shared_pointer.h"
#include "vector.h"
#include <gtest/gtest.h>

TEST(HelloTest, TestUniquePointer) {
    mstr::unique_pointer<float> my_pointer = mstr::unique_pointer<float>(new float(3.f));
    ASSERT_TRUE(my_pointer);
    ASSERT_NE(my_pointer.Get(), nullptr);
    ASSERT_EQ(*my_pointer.Get(), 3.f);
    ASSERT_NE(*my_pointer.Get(), 1.f);

    my_pointer.Reset();
    ASSERT_FALSE(my_pointer);
    ASSERT_EQ(my_pointer.Get(), nullptr);

    my_pointer.Reset(new float (5.f));
    ASSERT_TRUE(my_pointer);
    ASSERT_NE(my_pointer.Get(), nullptr);
    ASSERT_EQ(*my_pointer.Get(), 5.f);
    ASSERT_NE(*my_pointer.Get(), 1.f);
}

TEST(HelloTest, TestSharedPointer) {
    const float five = 5.f;
    const float three = 3.f;

    mstr::shared_pointer<float> shared_pointer_a(mstr::shared_pointer<float>(new float(five)));
    ASSERT_TRUE(shared_pointer_a);
    ASSERT_NE(shared_pointer_a.Get(), nullptr);
    ASSERT_EQ(*shared_pointer_a.Get(), five);
    ASSERT_EQ(shared_pointer_a.ReferenceCount(), 1);

    // copy constructor
    mstr::shared_pointer<float> shared_pointer_b(shared_pointer_a);
    ASSERT_TRUE(shared_pointer_a);
    ASSERT_NE(shared_pointer_a.Get(), nullptr);
    ASSERT_EQ(*shared_pointer_a.Get(), five);
    ASSERT_EQ(shared_pointer_a.ReferenceCount(), 2);

    ASSERT_TRUE(shared_pointer_b);
    ASSERT_NE(shared_pointer_b.Get(), nullptr);
    ASSERT_EQ(*shared_pointer_b.Get(), five);
    ASSERT_EQ(shared_pointer_b.ReferenceCount(), 2);
    ASSERT_EQ(shared_pointer_a.ReferenceCount(), shared_pointer_b.ReferenceCount());

    mstr::shared_pointer<float> shared_pointer_c(mstr::shared_pointer<float>(new float(three)));
    ASSERT_TRUE(shared_pointer_c);
    ASSERT_NE(shared_pointer_c.Get(), nullptr);
    ASSERT_EQ(*shared_pointer_c.Get(), three);
    ASSERT_EQ(shared_pointer_c.ReferenceCount(), 1);

    // copy assignment
    shared_pointer_c = shared_pointer_b;
    ASSERT_TRUE(shared_pointer_b);
    ASSERT_NE(shared_pointer_b.Get(), nullptr);
    ASSERT_EQ(*shared_pointer_b.Get(), five);
    ASSERT_EQ(shared_pointer_b.ReferenceCount(), 3);

    ASSERT_TRUE(shared_pointer_c);
    ASSERT_NE(shared_pointer_c.Get(), nullptr);
    ASSERT_EQ(*shared_pointer_c.Get(), five);
    ASSERT_EQ(shared_pointer_c.ReferenceCount(), 3);

    // Reset c
    shared_pointer_c.Reset();
    std::cout << shared_pointer_c.Get() << std::endl;
    ASSERT_FALSE(shared_pointer_c);
    ASSERT_EQ(shared_pointer_c.Get(), nullptr);
    ASSERT_EQ(shared_pointer_c.ReferenceCount(), 0);

    ASSERT_TRUE(shared_pointer_b);
    ASSERT_NE(shared_pointer_b.Get(), nullptr);
    ASSERT_EQ(*shared_pointer_b.Get(), five);
    ASSERT_EQ(shared_pointer_b.ReferenceCount(), 2);

    // Reset b
    shared_pointer_b.Reset();
    ASSERT_TRUE(shared_pointer_a);
    ASSERT_NE(shared_pointer_a.Get(), nullptr);
    ASSERT_EQ(*shared_pointer_a.Get(), five);
    ASSERT_EQ(shared_pointer_a.ReferenceCount(), 1);

    // Reset a
    shared_pointer_a.Reset();
    ASSERT_FALSE(shared_pointer_a);
    ASSERT_EQ(shared_pointer_a.Get(), nullptr);
    ASSERT_EQ(shared_pointer_a.ReferenceCount(), 0);
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