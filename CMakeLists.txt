# 0.) Create Source and CMakeFile
# 1.) mkdir build
# 2.) cd build
# 3.) cmake ..   -  Generting the Build Files / Configure the Project
# 4.) cmake --build .
# 5.) ./Executable

cmake_minimum_required(VERSION 3.16)

project(CppProjectTemplate VERSION 1.0.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD          17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS        OFF)

set(LIBRARY_NAME gof_lib)
set(EXECUTABLE_NAME Executable)

#option(COMPILE_EXECUTABLE "Whether to compile the executable" ON)

add_subdirectory(src)
#if (COMPILE_EXECUTABLE)
add_subdirectory(app)
#endif()
