#include <iostream>
#include <memory>

#include "src/unique_pointer.h"

int main() {
    std::unique_ptr<float> unique_ptr = std::make_unique<float>(5);

    mstr::unique_pointer<float> my_pointer = mstr::unique_pointer<float>(new float(3));
    std::cout << my_pointer.Get() << std::endl;
    my_pointer.Reset(nullptr);
    std::cout << my_pointer.Get() << std::endl;
    my_pointer.Reset(new float(5));
    std::cout << my_pointer.Get() << std::endl;

    return 0;
}
