cmake_minimum_required(VERSION 3.10) # CMake 3.9+ for OpenMP::OpenMP_CXX target
project(HeatDiffusionSimulation LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Find OpenMP
find_package(OpenMP REQUIRED)

add_executable(heat_simulation src/main.cpp)

# Link OpenMP libraries
if(OpenMP_CXX_FOUND)
    target_link_libraries(heat_simulation PUBLIC OpenMP::OpenMP_CXX)
    message(STATUS "OpenMP found and enabled for CXX.")
else()
    message(WARNING "OpenMP CXX not found. Building without OpenMP parallelization.")
endif()

# Optional: Add compiler flags for optimization or debugging
# For Release builds (optimized)
# target_compile_options(heat_simulation PRIVATE $<$<CONFIG:Release>:-O3 -DNDEBUG>)
# For Debug builds
# target_compile_options(heat_simulation PRIVATE $<$<CONFIG:Debug>:-g>)

# To ensure OpenMP flags are passed during compilation (especially for some compilers/CMake versions)
if(OpenMP_CXX_FOUND)
    target_compile_options(heat_simulation PUBLIC ${OpenMP_CXX_FLAGS})
    # Some linkers might also need OpenMP flags
    # target_link_options(heat_simulation PUBLIC ${OpenMP_CXX_FLAGS}) # Less common, but can be needed
endif()

install(TARGETS heat_simulation DESTINATION bin)