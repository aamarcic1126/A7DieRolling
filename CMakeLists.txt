cmake_minimum_required(VERSION 3.10)

# Set the C++ standard to C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# used internally by CMake to identify your project
project(A7DieRolling)

# Include the directory headers location
include_directories(${CMAKE_SOURCE_DIR}/include)

# Add the main executable
add_executable(A7DieRolling src/main.cpp src/die_rolling_simulation.cpp)

################################################################

# Add the test executable
add_executable(my_test src/die_rolling_simulation.cpp test/test.cpp)

# Include directories for the test target
target_include_directories(my_test PRIVATE ${PROJECT_SOURCE_DIR}/include)

# Enable testing
enable_testing()

# Register the test executable with CTest (optional)
# add_test(NAME my_test COMMAND my_test)