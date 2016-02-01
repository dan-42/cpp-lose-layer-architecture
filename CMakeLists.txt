cmake_minimum_required(VERSION 3.3)


include("cmake/HunterGate.cmake")
HunterGate(
        URL "https://github.com/dan-42/hunter/archive/v0.12.42-dan.tar.gz"
        SHA1 "e20106adbd1dfe0f437515d0bd4152ecd755b0a7"
)

project(lose-layer-architecture)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")


# boost
hunter_add_package(Boost COMPONENTS system)
find_package(Boost 1.60 COMPONENTS system REQUIRED )
link_directories (${Boost_LIBRARY_DIRS})
include_directories (${Boost_INCLUDE_DIRS})
ADD_DEFINITIONS(-DBOOST_LOG_DYN_LINK)
#ADD_DEFINITIONS(-DBOOST_ERROR_CODE_HEADER_ONLY)

# pre
#hunter_add_package(lib-cpp-pre)
find_package(lib-cpp-pre 1.3.2 REQUIRED)
include_directories(AFTER ${LIB_CPP_PRE_INCLUDE_DIRS})


set(SOURCE_FILES main.cpp)
add_executable(main ${SOURCE_FILES})