cmake_minimum_required(VERSION 2.8)

project(student_toolkit)
add_executable(${PROJECT_NAME} "main.cpp" "png_toolkit.cpp" "png_toolkit.h"
    "stb_image.h" "stb_image_write.h" "manager.cpp" "manager.h" "png_filters.cpp" "png_filters.h" "buf_picture.cpp" "buf_picture.h"
    "ker.cpp" "ker.h")
