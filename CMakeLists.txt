cmake_minimum_required(VERSION 3.6)
project(xml_test CXX)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp XmlElement.cpp XmlElement.hpp)

#target_link_libraries(xml++-3.0 STATIC /usr/local/lib/libxml++-3.0.so /usr/local/include/libxml++-3.0 )
find_package(CGICC REQUIRED)
include_directories(${CGICC_INCLUDE_DIRS})
set(LIBS ${LIBS} ${CGICC_LIBRARIES})

find_package(LibXML++ REQUIRED)
include_directories(${LibXML++_INCLUDE_DIRS})
set(LIBS ${LIBS} ${LibXML++_LIBRARIES})

add_executable(xml_test ${SOURCE_FILES})