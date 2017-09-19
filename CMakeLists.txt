cmake_minimum_required(VERSION 3.8)
project(DESTime)

set(CMAKE_CXX_STANDARD 11)

include_directories(./)

find_package(Boost COMPONENTS unit_test_framework REQUIRED)
include_directories(include ${Boost_INCLUDE_DIRS})

set(TEST_SOURCES ./)

enable_testing()
FILE(GLOB TestSources RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} test/*_test.cpp)
foreach(testSrc ${TestSources})
    get_filename_component(testName ${testSrc} NAME_WE)
    add_executable(${testName} test/main-test.cpp ${testSrc} ${TEST_SOURCES})
    target_link_libraries(${testName} ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})
    add_test(${testName} ${testName})
endforeach(testSrc)