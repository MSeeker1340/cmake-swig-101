# cmake-swig-101

## Overview

Minimal example for setting up a modern [Cmake](https://cmake.org) project with [Swig](https://swig.org/).

Currently, the only available binding example is Lua. I plan to add examples for Python and Javascript as well in the furture. 

## File layout

* `CMakeLists.txt`: global cmake config. Simply includes the `lua` subdirectory.

* `cpp`: contains sources and cmake config for a simple C++ library `mylib`
    
    * `mylib.h`, `mylib.cpp`: sources for `mylib`. Defines and exports a simple `addOne` function.
    
    * `mylib.i`: Swig wrapper interface file for `mylib.h`.

    * `mylib.cmake`: cmake config script. Defines file constants and sets include paths.

* `lua`: contains sources and cmake project config for the minimal test program `lua-binding-test`.

    * `lua-binding-test.cpp`: source file for the test program. Loads the `mylibLua` extension module and calls a Lua script testing the `addOne` extension.
    
    * `CMakeLists.txt`: The cmake config generates the `mylibLua` wrapper library from `mylib.i` using Swig, which is then linked by `lua-binding-test`.

Note: the wrapper interface file `mylib.i` is set in `mylib.cmake` as C++ so that Swig knows to generate `mylibLua` with C++ extension. This is not necessary for the simple example I provided, but needed if the interface contains C++ constructs like classes.

Furthermore, even though Swig is run with C++ extension turned on, the corresponding wrapper is still presented to the main program as a C library. This is why in `lua-binding-test.cpp` we need to declare `luaopen_mylib` as `extern "C"`, along with the main Lua C API headers.

## Prerequisites

Install cmake (>= 3.8) and swig. For example on Ubuntu

```bash
sudo apt-get install cmake swig
```

To build the lua example, build lua 5.4 from source directly

```bash
curl -R -O http://www.lua.org/ftp/lua-5.4.4.tar.gz
tar -xvf lua-5.4.4.tar.gz && cd lua-5.4.4
sudo make install # installs the headers and `liblua.a` needed by `lua-binding-test`
```

## How to run

Setup, build and run the cmake project normally using the IDE of your choice. For example, the command-line-only approach is

```bash
cmake -B build # cmake setup
cd build && make # build
./lua/lua-binding-test # run
```

You should see the following results on stdout

```
Testing mylib extension module ...
mylib.addOne(1.0) = 2.0
```

You may inspect the Swig generated wrapper module source at `build/lua/CMakeFiles/mylibLua.dir/mylibLUA_wrap.cxx`.

## References

* CMake's [documentation](https://cmake.org/cmake/help/latest/module/UseSWIG.html) on its Swig module. This [StackOverflow answer](https://stackoverflow.com/questions/1498969/generating-swig-bindings-with-cmake) also contains a good example on the Swig module (although slightly outdated).

* Swig's official [Lua integration guide](https://swig.org/Doc4.0/Lua.html#Lua_nn24). The building instructions, however, is outdated and cannot be used with Lua 5.4.

* The official [Programming in Lua](https://www.lua.org/pil/24.html) e-book contains excellent explanation of the Lua C API.
