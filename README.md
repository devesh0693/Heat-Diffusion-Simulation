# Heat Diffusion Simulation

This repository contains a C++ project for simulating heat diffusion using parallel processing capabilities provided by OpenMP. The project is configured with CMake for building and linking.

## Features

- Utilizes OpenMP for parallelization to enhance performance.
- Modular and easy-to-understand C++ codebase.
- Configurable for both debug and release builds.

## Requirements

To build and run the project, you need the following:

- **CMake** (minimum version 3.10)
- **C++ Compiler** with C++17 support
- **OpenMP** (compatible with your compiler)

## Building the Project

1. **Clone the repository:**
   git clone <repository-url>
   cd heat_diffusion_simulation
2. ***Create a build directory:***
mkdir build && cd build
3. ***Configure the build with CMake:***
 cmake ..
4. ***Build the project:***
cmake --build .
Running the Simulation
After building, the executable heat_simulation will be located in the bin directory (if installed) or the build directory. Run it with:
./heat_simulation
Customization
To enable or disable OpenMP parallelization, ensure that your system supports OpenMP, as specified in the CMakeLists.txt file.

You can add compiler flags for optimization or debugging by modifying the CMakeLists.txt file.

License
This project is licensed under the MIT License.
