cmake_minimum_required(VERSION 3.10)
project(CRCLib)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(${PROJECT_NAME} STATIC "src/CCITTFalse16BitCRC.cpp" "src/XModem16BitCRC.cpp" "src/ICRC.cpp" "src/Modbus16BitCRC.cpp" "src/CRC32Bit.cpp" "src/CRC8Bit.cpp" "src/BZip32BitCRC.cpp")

target_include_directories (${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/inc)

enable_testing()
find_package(GTest MODULE REQUIRED)

set(TEST_EXE "${PROJECT_NAME}_Test")
add_executable(${TEST_EXE} "test/CRC_Test.cpp")
target_link_libraries(${TEST_EXE} PRIVATE ${PROJECT_NAME} GTest::gtest GTest::gtest_main)
