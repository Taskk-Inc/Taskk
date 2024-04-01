# Taskk Multi-Language Software Profiler
wip.

## Building
In its current state this projects builds with Qt's mingw-w64 v11.2.0 
binaries, though with some slight tweaks it should be adaptable to 
any mainstream compiler.\
Here are the steps to adapt this project to your compiling environment.

### 1. Compiling & Linking Jansson
This project's only dependency except for the Qt Framework is
[Petri Lehtinen's JSON manipulation library](https://github.com/akheron/jansson).
Binaries might already be available for you environment, 
though we recommend always building open source projects yourself.
Read [Jansson's build instructions](https://jansson.readthedocs.io/en/latest/gettingstarted.html)
for further details on how to set it up.
Once compiled, all you have to do is replace our Jansson build in 
``lib/libs/jansson`` by you own, and make sure the 
``target_link_libraries`` command in ``lib/CMakeLists.txt``
points to the right static library file.

### 2. Compiling The Library
From here, everything should be set up correctly for compiling the library. \
Just generate a project with CMake and build for you desired target.

### 3. Linking The Library & Compiling The Tester
Once the library has been compiled, replace the files in 
``tester/libs/taskk`` with your own, then make sure your binary
files are linked correctly within ``tester/CMakeLists.txt`` 
(for further details see section 1.). The tester's language can be switched
between C and C++ in ``tester/src/switch.h``, just edit the 
``#define USE_CXX 0`` line to ``#define USE_CXX 1`` for C++.

### 4. Compiling the client
wip.

## Any Questions ? [Contact Us](mailto:berriot.cesar@gmail.com)

