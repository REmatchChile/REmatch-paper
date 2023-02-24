# **REmatch**: a novel regex engine for finding all matches


This repository functions as a companion piece for the paper _REmatch: a novel regex engine for finding all matches_. The repository contains:
1. A snapshot of the source code repository for the paper.
2. The extended version of the paper.

## **Important Links**

- **Official repository for the REmatch library**:
[https://github.com/REmatchChile/REmatch-paper/edit/main/README.md](https://github.com/REmatchChile/REmatch-paper/edit/main/README.md)

- **Link to the extended verison of the paper**: 
[https://github.com/REmatchChile/REmatch-paper/blob/main/paper.pdf](https://github.com/REmatchChile/REmatch-paper/blob/main/documents/paper.pdf)


## **Setup**
### **Configuring**

REmatch is a C++ library. We recommend using LLVM's `clang` or GNU's `g++` as a compiler. 

REmatch uses CMake for configuration and [vcpkg](https://vcpkg.io/en/index.html) to manage its dependencies. This repository already comes with the vcpkg repository as a submodule. To install it, run the following commands:
```
git submodule update --init --recursive
./vcpkg/bootstrap-vcpkg.sh
```

A cmake portable will be provided by the vcpkg installation if CMake is not installed. To setup the project configuration run:
```
mkdir build
cmake -B build -S . -DCMAKE_BUILD_TYPE=Release -DCMAKE_TOOLCHAIN_FILE=./vcpkg/scripts/buildsystems/vcpkg.cmake
```
The command may take some time to finish as it downloads and installs all the dependencies necessary to build the project.

### **Building**

To build the library after configuration, run the following command:
```
cmake --build build
```
This will build the library and the necessary binaries to make experiments. All binaries will be located in the `build/bin` directory.

## **Usage**
### **CLI Tool**
The project provides the rematch CLI tool to run experiments. The tool is located in the `build/bin` directory. To run the tool, run the following command:
```
build/bin/rematch <input_file> <regex-file>
```

#### **Examples**

Get all spans corresponding to a single letter `a`:
```
build/bin/rematch document.txt -e '!x{a}'
```
Same as above but giving the text explicitly from args:
```
build/bin/rematch -t "aaa" -e '!x{a}'
```
Get all spans corresponding to a pattern in a file:
```
build/bin/rematch document.txt regex.txt
```
Get benchmark stats (execution time, number of outputs, memory usage, etc.):
```
build/bin/rematch document.txt regex.txt --mode=benchmark
```
To see learn about the options of the CLI tool, run the following command:
```
build/bin/rematch --help
```

### **Experiments**
The project provides a set of experiments to evaluate the performance of the library. The experiments are located in the `datasets` directory. To run the experiments, run the following commands:
```
python scripts/benchmark.py
```
