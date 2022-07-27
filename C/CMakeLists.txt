cmake_minimum_required(VERSION 2.4)
project(Chengine)

add_subdirectory("./include")

add_executable(Chengine "./src/driver.c")

target_link_libraries(Chengine PUBLIC GameLibrary)
target_include_directories(Chengine PUBLIC
                          "${PROJECT_BINARY_DIR}"
                          "${PROJECT_SOURCE_DIR}/include"
                          )


