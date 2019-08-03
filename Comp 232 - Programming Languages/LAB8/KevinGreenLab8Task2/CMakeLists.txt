cmake_minimum_required(VERSION 3.8)

project(calc)

set(CMAKE_C_STANDARD 99)

SET(CMAKE_C_FLAGS "-m64 -g -O0 -D_DEBUG -Wall")

set(SOURCE_FILES
        calc/calc.c
        ${CMAKE_CURRENT_BINARY_DIR}/calcScanner.c
        ${CMAKE_CURRENT_BINARY_DIR}/calcParser.c
        )

include_directories(AFTER calc)

find_package(BISON)
find_package(FLEX)

BISON_TARGET(calcParser calc/calc.y ${CMAKE_CURRENT_BINARY_DIR}/calcParser.c)
FLEX_TARGET(calcScanner calc/calc.l  ${CMAKE_CURRENT_BINARY_DIR}/calcScanner.c)

ADD_FLEX_BISON_DEPENDENCY(calcScanner calcParser)

add_executable(
        calc
        ${SOURCE_FILES}
        ${BISON_calcParser_OUTPUTS}
        ${FLEX_calcScanner_OUTPUTS}
)