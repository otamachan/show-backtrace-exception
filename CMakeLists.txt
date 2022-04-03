cmake_minimum_required(VERSION 3.0.2)
project(hook)
include(ExternalProject)
ExternalProject_Add(libunwind
  SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/third_party/libunwind
  CONFIGURE_COMMAND autoreconf -i ${CMAKE_CURRENT_SOURCE_DIR}/third_party/libunwind && ${CMAKE_CURRENT_SOURCE_DIR}/third_party/libunwind/configure --prefix ${CMAKE_CURRENT_BINARY_DIR}/libunwind CFLAGS=-fPIC
  BUILD_COMMAND ${MAKE})
  
add_library(hook SHARED hook.cpp ${CMAKE_CURRENT_SOURCE_DIR}/third_party/sblz/src/demangler.cc)
add_dependencies(hook libunwind)
target_include_directories(hook PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/libunwind/include ${CMAKE_CURRENT_SOURCE_DIR}/third_party/sblz/include)
target_link_libraries(hook dl ${CMAKE_CURRENT_BINARY_DIR}/libunwind/lib/libunwind-generic.a ${CMAKE_CURRENT_BINARY_DIR}/libunwind/lib/libunwind.a)
set_property(TARGET hook PROPERTY POSITION_INDEPENDENT_CODE ON)
