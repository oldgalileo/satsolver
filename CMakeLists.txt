cmake_minimum_required(VERSION 3.16)
project(sat_solver)

set(CMAKE_CXX_STANDARD 17)

include(FetchContent)

set(BENCHMARK_ENABLE_TESTING OFF)
FetchContent_Declare(googlebenchmark
        GIT_REPOSITORY https://github.com/google/benchmark
        )
FetchContent_MakeAvailable(googlebenchmark)

add_executable(sat_solver src/main.cpp src/sat.h src/sat.cpp)

target_link_libraries(sat_solver benchmark::benchmark)
