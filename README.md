# ESys
System framework suited for resource constrained embedded applications

## Features
- simple application framework with OS signal support
- multithreading abstraction
- minimalistic UDP socket implementation
- reduce the heap usage to minimum, use the automatic variables whenever possible
- template based Automatic Arrays
- requires C++11

## Todo
- implement the AutoString class (std::string analogue that does not use heap)
- switch the implementation to use the AutoString for text handling
