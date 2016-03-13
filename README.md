# ESys
System framework suited for resource constrained embedded applications

## Features
- simple application framework with OS signal support
- OOD multithreading abstraction layer
- minimalistic UDP networking
- reduce the heap usage to minimum, use the automatic/stack variables whenever possible
- template based containers: Automatic Arrays and String stack-memory analogues
- extends the generic C++11 implementation
- posix and WinAPI compatible

## Building project
### Dependencies
- Requires the [CMake][11] installed. Minimum version required is 3.0.0.

### Building

In the project root directory execute the shell script *configure.sh* with root
privileges, if you intend to install the binary output and headers:
```
sudo ./configure.sh
```
This script will create a new output directory, named *build*,
to enable an _out-of-place_ build.

Single static library will be created: *libesys.a*. It contains the whole
framework code.

If you choose to install the project, then the binaries, headers and example code will
be copied to default directory, which, on Linux systems is normally _/usr/local/_.

|Location|Content|
|---|---|
|/usr/local/bin|demo executables|
|/usr/local/lib|libraries|
|/usr/local/include/ESys|headers|

## Usage
### Integration into user code
#### Example
TBD

### Linking
Link your binaries with the *esys* static library.

**Remark**: For the posix builds you have to link the executable with the *-pthread* flag.
```
g++ example/main.o -lesys -pthread -o esys-demo
```
## Todo
- switch the implementation to use the AutoString for text handling

Copyright &copy; 2016 [Przemysław Podwapiński][98].<br/>
Distributed under the [Simplified BSD License][99].

[11]:https://cmake.org/
[98]:mailto:p.podwapinski@gmail.com
[99]:https://www.freebsd.org/copyright/freebsd-license.html
