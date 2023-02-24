# **REmatch**: a novel regex engine for finding all matches


This repository functions as a companion piece for the paper _REmatch: a novel regex engine for finding all matches_. The repository contains:
1. A snapshot of the source code repository for the paper.
2. The extended version of the paper.

## **Important Links**

- **Official repository for the REmatch library**:
[https://github.com/REmatchChile/REmatch-paper/edit/main/README.md](https://github.com/REmatchChile/REmatch-paper/edit/main/README.md)

- **Link to the extended verison of the paper**: 
[https://github.com/REmatchChile/REmatch-paper/blob/main/paper.pdf](https://github.com/REmatchChile/REmatch-paper/blob/main/paper.pdf)


## **Setup**

### **Dependencies**

REmatch is a C++ library. We recommend using LLVM's `clang` or GNU's `g++`. 

REmatch depends on CMake for configuring and building. To install CMake in Ubuntu, run the following command:
```bash
sudo apt-get install cmake
```
To install it in MacOS,
```bash
brew install cmake
```

To install it in Windows, you can download the installer from [https://cmake.org/install/](https://cmake.org/install/)


### **Building**

REmatch uses [vcpkg](https://vcpkg.io/en/index.html) to manage its dependencies. This repository already comes with the vcpkg repository as a submodule. To install it, run the following commands:
```
git submodule update --init --recursive
./vcpkg/bootstrap-vcpkg.sh
```

To build the library, run the following commands:
```
mkdir build
cmake -B build -S . -DCMAKE_BUILD_TYPE=Release -DCMAKE_TOOLCHAIN_FILE=./vcpkg/scripts/buildsystems/vcpkg.cmake
cmake --build build
```

These commands may take some time to finish as they download and install dependencies, and build the library and the binaries to make experiments. 

## **Usage**
### **CLI Tool**
The project provides the rematch CLI tool to run experiments. The tool is located in the `build/bin` directory. To run the tool, run the following command:
```
build/bin/rematch <input_file> <regex-file>
```

### **Experiments**
The project provides a set of experiments to evaluate the performance of the library. The experiments are located in the `datasets` directory. To run the experiments, run the following commands:
```
python scripts/benchmark.py
```
