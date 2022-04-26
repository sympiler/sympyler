# sympyler
This is a work in progress to create a python interface to sympiler and NASOQ packages. 
## Boost library
This python interface is based on the boost::python library. The build is tested on version 1.75.0.

To install on macOS, simply used
```
brew install boost boost-python3
```
On Ubuntu, use
```
sudo apt-get install libboost-all-dev
```
Or one can also build the boost library from source following the [documentation here](https://www.boost.org/doc/libs/1_75_0/more/getting_started/unix-variants.html). 
## Build Flags
You might need to specify your python directory to cmake if you are using venv or pyenv. 

For example,
```
-DPYTHON_VERSION=3.9 -DPYTHON_LIBRARY=/Users/.pyenv/versions/3.9.0/Python.framework/Versions/3.9/lib/libpython3.9.dylib -DPYTHON_INCLUDE_DIR=/Users/.pyenv/versions/3.9.0/Python.framework/Versions/3.9/Headers/
```

One can specify the compiler by setting the `CMAKE_CXX_COMPILER` flag.

