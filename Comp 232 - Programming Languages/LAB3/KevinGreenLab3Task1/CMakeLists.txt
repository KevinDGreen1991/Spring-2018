cmake_minimum_required(VERSION 3.9)
project(scanner1)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES src/main.c src/scanner.h src/scanner.c)

include_directories(AFTER src)

add_executable(scanner1 ${SOURCE_FILES})