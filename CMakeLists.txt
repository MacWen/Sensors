cmake_minimum_required(VERSION 3.8)
project(VSCodeProj)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/external/tinyXML)

SET(TINYXML_DIR ${CMAKE_CURRENT_SOURCE_DIR}/external/tinyXML)
add_library(tinyxml2 ${TINYXML_DIR}/tinyxml2.h ${TINYXML_DIR}/tinyxml2.cpp)

set( NAME_SRC src/main.cpp src/sensorfactory.cpp src/server.cpp src/temp.cpp)
add_executable(program ${NAME_SRC})
target_link_libraries(program tinyxml2)

#add_executable(server src/server.cpp)
add_executable(client client/client.cpp)
