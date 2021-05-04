cmake_minimum_required(VERSION 3.8)

set(This TreeDataTest)

enable_testing()
find_package(GTest REQUIRED)
include(Dart)

set(Sources 
    ${This}.cpp
)

add_executable(${This} ${Sources})
target_link_libraries(${This} PUBLIC  
    TreeData
    gtest_main
    ${GTEST_LIBRARIES}
    pthread
)

add_test(
    NAME ${This}
    COMMAND ${This}
)

