# QCGPU

> An Open Source, GPU Accelerated, Quantum Computer Simulator

* Uses the parallel programing library [ArrayFire](http://arrayfire.org/docs/index.htm), which supports CUDA and OpenCL kernels.
* Runs Cross Platform (x86, ARM, CUDA, and OpenCL devices)

This is currently a work in progress, not suitable for use.

## Prerequisites:
* A C++11 compiler, like gcc or clang
* [CMake](http://www.cmake.org) 3.0.0 or newer
* ArrayFire 3.0.1 or newer via. [pre-built binaries](http://arrayfire.com/download)

## Building this project

### Linux and OSX
To build this project simply:

```
mkdir build
cd build
cmake ..
make
```

### Windows
Download the project and files into your working directory. For simplicity,
lets assume the project is at `C:\workspace\qcgpu`.

Open the CMake GUI.

In the source directory field, enter the working directory
`C:\workspace\qcgpu`. In the build directory field, enter the build
directory `C:\workspace\qcgpu\build`.

Click `Configure`.

If there are no errors, click `Generate` in the CMake GUI.

Now, the solution files will be created in the build directory. There will be
different projects created for CPU, CUDA and OpenCL. Setting one of these
projects as start project and then running it will run the example with the
specified backend.

## Notes

The minimum filling time of a matrix with (n_1 * n_2) X (m_1 * m_2) is O(n_1 * n_2 * m_1 * m_2). 
This is relevent to the kronecker product.
Some other considerations for the future development of this software, and the speedup of this function is:

* Parallelize
* Store on the fly (i.e. store M as kron of A and B, and calculate only when single element is needed)
* Could Use ArrayFire Tile Function

Can also max at 30 qubits, or the number storage will have to be changed

`grammar.pegjs` needs to be formatted and parts rewritten, conditionals not implemented yet.

## License

This software is licensed under the MIT licence (see `LICENSE.md`)

Copyright (c) 2018 Adam Kelly

## Citations

```
@misc{Yalamanchili2015,
abstract = {ArrayFire is a high performance software library for parallel computing with an easy-to-use API. Its array based function set makes parallel programming simple. ArrayFire's multiple backends (CUDA, OpenCL and native CPU) make it platform independent and highly portable. A few lines of code in ArrayFire can replace dozens of lines of parallel computing code, saving you valuable time and lowering development costs.},
address = {Atlanta},
author = {Yalamanchili, Pavan and Arshad, Umar and Mohammed, Zakiuddin and Garigipati, Pradeep and Entschev, Peter and Kloppenborg, Brian and Malcolm, James and Melonakos, John},
publisher = {AccelerEyes},
title = {{ArrayFire - A high performance software library for parallel computing with an easy-to-use API}},
url = {https://github.com/arrayfire/arrayfire},
year = {2015}
}
```

