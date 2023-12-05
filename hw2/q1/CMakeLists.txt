cmake_minimum_required(VERSION 3.10)
project(SharedMemoryExample)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Boost REQUIRED COMPONENTS system)
include_directories(${Boost_INCLUDE_DIRS})

add_executable(producer producer.cpp)
add_executable(consumer consumer.cpp)

target_link_libraries(producer ${Boost_LIBRARIES})
target_link_libraries(consumer ${Boost_LIBRARIES})
