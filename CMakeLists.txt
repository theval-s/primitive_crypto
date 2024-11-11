cmake_minimum_required (VERSION 3.15)

project ("crypto_lab1")
set(CMAKE_CXX_STANDARD 20)

#in case Windows is used with MinGW or similar layer
#set(CMAKE_EXE_LINKER_FLAGS ${CMAKE_EXE_LINKER_FLAGS} "-static")

add_executable (crypto_lab1 "crypto_lab1.cpp" "crypto_lab1.h")




