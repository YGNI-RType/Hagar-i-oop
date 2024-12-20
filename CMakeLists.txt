cmake_minimum_required(VERSION 3.10)
project(rtype)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_CXX_EXTENSIONS NO)

include(cmake/automate-vcpkg-gengine.cmake)
vcpkg_bootstrap()
vcpkg_install_gengine()

include_directories(include)

file(GLOB_RECURSE SOURCES source/*.cpp)

add_executable(hiop_server ${SOURCES})
add_executable(hiop_client ${SOURCES})

find_package(GEngine CONFIG REQUIRED)
target_link_libraries(hiop_server PRIVATE GEngine)
target_link_libraries(hiop_client PRIVATE GEngine)

target_compile_definitions(hiop_server PRIVATE GEngine_Server)
target_compile_definitions(hiop_client PRIVATE GEngine_Client)
