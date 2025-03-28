cmake_minimum_required(VERSION 3.18)
project(cuda_integral LANGUAGES C CXX CUDA)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CUDA_STANDARD 14)

set(EXECUTABLE cuda_integrate)

set(WARNINGS_AS_ERRORS OFF)
set(ENABLE_PVS_STUDIO OFF)
set(ENABLE_UBSan OFF)
set(ENABLE_ASAN OFF)
set(ENABLE_TSan OFF)
set(ENABLE_MSAN OFF)

if (NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE Release)
endif ()


add_executable(${EXECUTABLE}
    main.cpp
    options_parser/options_parser.cpp
    src/parse_string.cpp
		src/functions.cu
    src/riemann_sum_cuda.cu

    options_parser/options_parser.h
    include/parse_string.h
		include/functions.h
    include/timeMeasurement.h
    include/riemann_sum_cuda.h
)


target_include_directories(${EXECUTABLE}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        ${CMAKE_CURRENT_SOURCE_DIR}/options_parser
)

find_package(Boost 1.71 REQUIRED COMPONENTS program_options system)
find_package(Threads REQUIRED)

target_include_directories(${EXECUTABLE} PRIVATE ${Boost_INCLUDE_DIR})
target_link_libraries(${EXECUTABLE}
    PRIVATE
        Boost::program_options
        Boost::system
        Threads::Threads
)


set_target_properties(${EXECUTABLE} PROPERTIES
    CUDA_SEPARABLE_COMPILATION ON
    CUDA_ARCHITECTURES 86
)


include(cmake/main-config.cmake)
include(cmake/CompilerWarnings.cmake)
