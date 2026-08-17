cmake_minimum_required(VERSION 3.20)

project(Minecraft-C++)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
    src/*.cpp
    src/*.c
)

add_executable(Minecraft-C++ ${SOURCES})

target_include_directories(Minecraft-C++ PRIVATE
    include
)

target_link_libraries(Minecraft-C++ PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/libglfw3.a
)

#target_link_options(Minecraft-C++ PRIVATE
    #-lkernel32        
#)
