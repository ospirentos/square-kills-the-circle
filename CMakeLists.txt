cmake_minimum_required(VERSION 3.20)
project(square-kills-the-circle)

set(CMAKE_CXX_STANDARD 17)

# raylib
find_package(raylib REQUIRED)

# Lua C API (sol2 kaldırıldı — Clang 22 uyumsuzluğu nedeniyle ham Lua API kullanıyoruz)
find_package(Lua REQUIRED)

# scripts/ dizinini build dizinine kopyala — Lua yolları build içinden çalışır
file(COPY ${CMAKE_SOURCE_DIR}/scripts DESTINATION ${CMAKE_BINARY_DIR})

# Kaynak dosyalar
file(GLOB_RECURSE SOURCES src/*.cpp)

add_executable(square-kills-the-circle ${SOURCES})
target_link_libraries(square-kills-the-circle raylib ${LUA_LIBRARIES})
target_include_directories(square-kills-the-circle PRIVATE src ${LUA_INCLUDE_DIR})
