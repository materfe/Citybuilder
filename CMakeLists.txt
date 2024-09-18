cmake_minimum_required(VERSION 3.18)
project(CityBuilder)


set (CMAKE_CXX_STANDARD 20)
set (CMAKE_CXX_STANDARD_REQUIRED ON)

enable_testing()

find_package(GTest CONFIG REQUIRED)
find_package(SFML COMPONENTS system window graphics audio CONFIG REQUIRED)

#profiler
if(ENABLE_PROFILING)
    find_package(Tracy CONFIG REQUIRED)
endif(ENABLE_PROFILING)

add_subdirectory(core/)
add_subdirectory(api/)

add_executable(main main.cc)
target_link_libraries(main PRIVATE api core sfml-system sfml-network sfml-graphics sfml-window sfml-audio)

#copy resources in build
file(COPY ${CMAKE_SOURCE_DIR}/resources DESTINATION ${CMAKE_BINARY_DIR})

option(ENABLE_PROFILING "Enable Tracy Profiling" OFF)