cmake_minimum_required(VERSION 3.10)
project(MatrixCalculator)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add main executable
add_executable(Matrix_Calculator src/Matrix_Calculator.cpp)

# Add test executable (compile separately)
add_executable(test_matrix tests/test_matrix.cpp)

# Add test executable (compile separately)
add_executable(determinant_test tests/determinant_test.cpp)

# Add test executable (compile separately)
add_executable(inverse_test tests/inverse_test.cpp)