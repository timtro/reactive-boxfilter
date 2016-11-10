cmake_minimum_required (VERSION 2.8)

#set(CMAKE_C_COMPILER /usr/bin/clang)
#set(CMAKE_CXX_COMPILER /usr/bin/clang++)

project(reactive-boxfilter)

set( CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR} )


set(c++std "-std=c++1z")

set(warnings_debug "-Wall -Wextra -pedantic")
set(optimizations_debug "-O0")
set(debug "-g")

set(warnings_release "-Wall")
set(optimizations_release "-O2 -flto -ffast-math")
set(perf_bench "-fno-omit-frame-pointer")

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} ${c++std} ${debug} ${warnings_debug} ${optimizations_debug}")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} ${c++std} ${warnings_debug} ${optimizations_release}")

find_package( Threads )
find_package(Boost 1.53.0)
# find_package(MathGL2 2.1 REQUIRED Qt)

include_directories(${MATHGL2_INCLUDE_DIRS})

MESSAGE( STATUS "CMAKE_MODULE_PATH: " ${CMAKE_MODULE_PATH}/cmake )


add_subdirectory(src)
