cmake_minimum_required(VERSION 3.20)

project(FindMinimumInRotatedSortedArray CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(programa
    src/main.cpp
    src/solution.cpp
    src/utils.cpp
)

add_executable(executable_test 
    test/test.cpp
    src/solution.cpp
    src/utils.cpp
)

add_executable(benchmark
    bench/benchmark.cpp
    src/solution.cpp
    src/utils.cpp
)

#Activa CTest
enable_testing()

add_test(NAME pruebas COMMAND executable_test)