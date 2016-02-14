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

## ChangeLog
### 0.1.1
2016-02-14
- switch the net, app and sys components to use AutoString

### 0.1.0
2016-02-14
- implemented AutoString

### 0.0.1
- initial commit

## Todo
- switch the implementation to use the AutoString for text handling

Copyright &copy; 2016 [Przemysław Podwapiński][98]<br/>
Distributed under the [Simplified BSD License][99].

[98]:mailto:p.podwapinski@gmail.com
[99]:https://www.freebsd.org/copyright/freebsd-license.html
