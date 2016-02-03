# ESys
System framework suited for resource constrained embedded applications

## Features
- simple application framework with OS signal support
- OOD multithreading abstraction layer
- minimalistic UDP socket implementation
- reduce the heap usage to minimum, use the automatic/stack variables whenever possible
- template based Automatic Arrays and String analogues
- requires C++11

## Todo
- implement the AutoString class (std::string analogue that does not use heap)
- switch the implementation to use the AutoString for text handling

Copyright &copy; 2016 [Przemysław Podwapiński][98]<br/>
Distributed under the [Simplified BSD License][99].

[98]:mailto:p.podwapinski@gmail.com
[99]:https://www.freebsd.org/copyright/freebsd-license.html
