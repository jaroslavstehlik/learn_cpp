#pragma once
#include <iostream>
#include <vector>

//
// Created by Jaroslav Stehlik on 12.02.2024.
//

class TestClass {
public:
    TestClass() {
        std::cout << "TestClass.Create" << std::endl;
    }

    TestClass(const TestClass& other) {
        std::cout << "TestClass.CopyConstructor" << std::endl;
    }

    TestClass(TestClass&& other) noexcept {
        std::cout << "TestClass.MoveConstructor" << std::endl;
    }

    TestClass& operator= (const TestClass& other)
    {
        if(this == &other)
            return *this;

        std::cout << "TestClass.CopyAssignment" << std::endl;
        return *this;
    }

    TestClass& operator= (TestClass&& other)
    {
        if(this == &other)
            return *this;

        std::cout << "TestClass.MoveAssignment" << std::endl;
        return *this;
    }

    ~TestClass() {
        std::cout << "TestClass.Destroy" << std::endl;
    }
};

void TestMain()
{
    std::vector<TestClass> test_class{};
    std::cout << "create vector.Capacity: " << test_class.capacity()<< std::endl;
    std::cout << "vector.emplace_back, capacity: " << test_class.capacity()<< std::endl;
    test_class.emplace_back();
    std::cout << "vector.pop_back, capacity: " << test_class.capacity()<< std::endl;
    test_class.pop_back();
    std::cout << "vector.emplace_back, capacity: " << test_class.capacity()<< std::endl;
    test_class.emplace_back();
    std::cout << "vector.emplace_back, capacity: " << test_class.capacity()<< std::endl;
    test_class.emplace_back();
    std::cout << "vector.emplace_back, capacity: " << test_class.capacity()<< std::endl;
    test_class.emplace_back();
}