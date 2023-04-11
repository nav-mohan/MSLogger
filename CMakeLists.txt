cmake_minimum_required(VERSION 3.11)
project(MSLoggerExample LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)

get_filename_component(PROJECT_BASE_DIR ./ ABSOLUTE)

message(${PROJECT_BASE_DIR})

add_subdirectory(${PROJECT_BASE_DIR}/lib)

add_executable(${PROJECT_NAME} main.cpp)
target_include_directories(
    ${PROJECT_NAME} PUBLIC
    ${PROJECT_BASE_DIR}/lib
)
target_link_libraries(
    ${PROJECT_NAME} PUBLIC
    MSLogger
)
