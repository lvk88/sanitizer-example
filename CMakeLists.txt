CMAKE_MINIMUM_REQUIRED(VERSION 3.1)

PROJECT(sanitizer_example)

ADD_EXECUTABLE(main main.cpp)

if (NOT CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
  MESSAGE(WARNING "You are not using clang to build this code. Sanitizer might not work properly!")
endif()

TARGET_COMPILE_OPTIONS(main PUBLIC -fsanitize=address)
TARGET_LINK_OPTIONS(main PUBLIC -fsanitize=address)

