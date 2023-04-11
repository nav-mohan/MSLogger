cmake_minimum_required(VERSION 3.15)
project(MSLoggerTests LANGUAGES CXX)
set (CMAKE_CXX_STANDARD 17)

find_package(Boost REQUIRED COMPONENTS headers thread atomic regex)
add_definitions(-DTESTING="TRUE")

get_filename_component(PROJECT_BASE_DIR ../ ABSOLUTE)

add_subdirectory(
    ${PROJECT_BASE_DIR}/lib
    ${PROJECT_SOURCE_DIR}/build/lib
)

# ***********************
# SingleThreaded Tests
# ***********************
add_executable(constructor_st_test constructor_st.test.cpp)
add_executable(stdout_st_test stdout_st.test.cpp)
add_executable(pointers_st_test pointers_st.test.cpp)

target_include_directories(
    constructor_st_test PUBLIC 
    "/opt/homebrew/Cellar/boost/1.81.0_1/include"
    ${PROJECT_BASE_DIR}/lib
)

target_link_libraries(
    constructor_st_test PUBLIC 
    MSLogger
    Boost::headers 
)

target_include_directories(
    stdout_st_test PUBLIC 
    "/opt/homebrew/Cellar/boost/1.81.0_1/include"
    ${PROJECT_BASE_DIR}/lib
)

target_link_libraries(
    stdout_st_test PUBLIC 
    MSLogger
    Boost::headers 
    Boost::regex
)

target_include_directories(
    pointers_st_test PUBLIC 
    "/opt/homebrew/Cellar/boost/1.81.0_1/include"
    ${PROJECT_BASE_DIR}/lib
)

target_link_libraries(
    pointers_st_test PUBLIC 
    MSLogger
    Boost::headers 
    Boost::regex
)


# ***********************
# Multithreaded Tests
# ***********************

add_executable(constructor_mt_test constructor_mt.test.cpp)
add_executable(stdout_mt_test stdout_mt.test.cpp)

target_include_directories(
    constructor_mt_test PUBLIC 
    "/opt/homebrew/Cellar/boost/1.81.0_1/include"
    ${PROJECT_BASE_DIR}/lib
)

target_link_libraries(
    constructor_mt_test PUBLIC 
    MSLogger
    Boost::headers 
    Boost::thread
    Boost::atomic
)

target_include_directories(
    stdout_mt_test PUBLIC 
    "/opt/homebrew/Cellar/boost/1.81.0_1/include"
    ${PROJECT_BASE_DIR}/lib
)

target_link_libraries(
    stdout_mt_test PUBLIC 
    MSLogger
    Boost::headers 
    Boost::thread
    Boost::atomic
    Boost::regex
)
