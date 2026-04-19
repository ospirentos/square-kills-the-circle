cmake_minimum_required(VERSION 3.20)
project(square-kills-the-circle)

set(CMAKE_CXX_STANDARD 17)

# raylib
find_package(raylib REQUIRED)

# sol2 + Lua
find_package(Lua REQUIRED)
include(FetchContent)
FetchContent_Declare(sol2
    GIT_REPOSITORY https://github.com/ThePhD/sol2.git
    GIT_TAG v3.3.0
)
FetchContent_MakeAvailable(sol2)

# Kaynak dosyalar
file(GLOB_RECURSE SOURCES src/*.cpp)

add_executable(square-kills-the-circle ${SOURCES})
target_link_libraries(square-kills-the-circle raylib ${LUA_LIBRARIES} sol2)
target_include_directories(square-kills-the-circle PRIVATE src ${LUA_INCLUDE_DIR})
