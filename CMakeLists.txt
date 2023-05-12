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

#get googletest
include(FetchContent)
FetchContent_Declare(googletest
	GIT_REPOSITORY https://github.com/google/googletest
	GIT_TAG release-1.11.0)
FetchContent_GetProperties(googletest)
#googletest_POPULATED
#googletest_SOURCE_DIR
#googletest_BUILD_DIR
if(NOT googletest_POPULATED)
  FetchContent_Populate(googletest)
  add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BUILD_DIR})
endif()

FetchContent_Declare(
    SPDlog
    GIT_REPOSITORY https://github.com/gabime/spdlog
    GIT_TAG v1.11.0
    GIT_SHALLOW TRUE)
FetchContent_MakeAvailable(SPDlog)

FetchContent_Declare(
    PNGwriter
    GIT_REPOSITORY https://github.com/pngwriter/pngwriter
    GIT_TAG 0.7.0
    GIT_SHALLOW TRUE)
FetchContent_MakeAvailable(PNGwriter)

add_subdirectory(src)
#if (COMPILE_EXECUTABLE)
add_subdirectory(app)
#endif()

add_subdirectory(tests)
