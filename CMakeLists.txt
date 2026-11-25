cmake_minimum_required(VERSION 3.16)
project(bpast LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_library(bpast STATIC
    src/core/kittycat.cpp
    src/core/meowgine.cpp
    src/core/meowindow.cpp
    src/core/meowmera.cpp
    src/core/meowse.cpp
    src/core/meowtime.cpp
    src/graphics/meowbox.cpp
    src/graphics/meowder.cpp
    src/graphics/meowsh.cpp
    src/graphics/meowxture.cpp
    src/graphics/obj-pawrser.cpp
    src/scene/SceneObj.cpp
    src/scene/meowscene.cpp
    third_party/glad/src/glad.c
)

# glm/glad are used by public headers, so consumers need these include dirs too.
target_include_directories(bpast PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/third_party/glm/include
    ${CMAKE_CURRENT_SOURCE_DIR}/third_party/glad/include
)

# stb is only used inside meowxture.cpp.
target_include_directories(bpast PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/third_party/stb/include
)

target_compile_options(bpast PRIVATE -Wall)

find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED)
target_link_libraries(bpast PUBLIC glfw OpenGL::GL)

if(CMAKE_SOURCE_DIR STREQUAL PROJECT_SOURCE_DIR)
    add_executable(bpast_example examples/main.cpp)
    target_link_libraries(bpast_example PRIVATE bpast)
    set_target_properties(bpast_example PROPERTIES OUTPUT_NAME BPAST)

    # copy assets next to the executable so it also runs from inside build/
    add_custom_command(TARGET bpast_example POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${CMAKE_CURRENT_SOURCE_DIR}/assets"
            "$<TARGET_FILE_DIR:bpast_example>/assets")
endif()
