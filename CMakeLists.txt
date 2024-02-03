cmake_minimum_required(VERSION 3.27)
project(basics)

set(CMAKE_CXX_STANDARD 17)

add_executable(basics "src/main.cpp" "src/unique_pointer.h" "src/vector.h" "src/string/m_string.h" "src/string/m_string.cpp"
        src/shared_pointer.h)
