cmake_minimum_required(VERSION 3.0)
project(PROJECT_NAME LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-std=c++17 -Wall -Werror -Wextra --coverage")

include(FetchContent)
FetchContent_Declare(
        googletest
        # Specify the commit you depend on and update it regularly.
        URL https://github.com/google/googletest/archive/5376968f6948923e2411081fd9372e71a59d8e77.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(MatrixTests
        S21_Matrix_Methods.cpp 
        S21_Matrix_Operations.cpp 
        S21_Matrix_overload.cpp
        s21_matrix_test.cpp
)

target_link_libraries(MatrixTests gtest_main)
add_test(NAME MatrixTests_TEST COMMAND MatrixTests)