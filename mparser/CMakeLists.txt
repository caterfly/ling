cmake_minimum_required(VERSION 3.21)
project(mparser)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)
FetchContent_Declare(
        pugixml
        GIT_REPOSITORY https://github.com/zeux/pugixml
)
FetchContent_MakeAvailable(pugixml)


target_include_directories(pugixml INTERFACE
        $<BUILD_INTERFACE:${pugixml_SOURCE_DIR}/src>)

add_executable(mparser main.cpp src/DictParse.cpp src/DictParse.h src/Lemma.cpp src/Lemma.h src/Form.cpp src/Form.h src/Dict.cpp src/Dict.h)


target_link_libraries(mparser pugixml)

get_property(dirs DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY INCLUDE_DIRECTORIES)
foreach(dir ${dirs})
    message(STATUS "dir='${dir}'")
endforeach()