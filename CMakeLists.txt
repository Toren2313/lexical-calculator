cmake_minimum_required(VERSION 3.29)
project(lexical_calculator)

file(GLOB_RECURSE lexical_calculator_SOURCES CONFIGURE_DEPENDS "src/*.cpp")
file(GLOB_RECURSE lexical_calculator_HEADERS CONFIGURE_DEPENDS "src/*.h")
set(lexical_calculator_INCLUDE_DIRS "")

include_directories(${lexical_calculator_INCLUDE_DIRS} ${CMAKE_SOURCE_DIR}/src)
add_executable(${PROJECT_NAME} ${lexical_calculator_SOURCES})

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-allow-multiple-definition")

foreach(_headerFile ${lexical_calculator_HEADERS})
get_filename_component(_dir ${_headerFile} PATH)
list(APPEND lexical_calculator_INCLUDE_DIRS ${_dir})
endforeach()
