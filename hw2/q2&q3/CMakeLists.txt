cmake_minimum_required(VERSION 3.23)
project(products)

set(CMAKE_CXX_STANDARD 20)

find_package(Boost REQUIRED COMPONENTS system)
include_directories(${Boost_INCLUDE_DIRS})

add_executable(products
        products.hpp
        productservice.hpp
        soa.hpp
        test_products.cpp)
