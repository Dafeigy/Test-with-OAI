# OAI beginner's start: Write a dev/test function within OAI workflow

As you know, OAI is a tremendous C project, which uses `CMake` to compile and manage different executables. In this part, I try to share you with me experience in writing a single unit test with OAI original code logic, and an example for modification in `CMakeLists.txt` would be helpful for your personal dev reference.

## What I try to do

I want to do RPC things, to be more specific, I manage to send some data in `openair1/PHY/xx/xx.c`, and the data is serialized by protobuf, and be sent in UDP package.
I extract the key logic of the data generation, and make it a random one for test, and at the receiver, I use `python` to get these UDP packages.

To serilize the data, I use protobuf-c to pack the data and send them. A protobuf-c is required, you can download it by this following command:
```bash
git clone https://github.com/protobuf-c/protobuf-c.git
```

The very first thing you should do is to write a `CMakeLists.txt` in your project root dir:

```cmake
cmake_minimum_required(VERSION 3.10)
project(prototest)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)


include_directories(protobuf-c)

add_executable(prototest 
  test.c
  protobuf-c/protobuf-c/protobuf-c.c
  protobuf-c/protobuf-c/protobuf-c.h
  MESSAGES/channel_matrx.pb-c.h
  MESSAGES/channel_matrx.pb-c.c
)

```

and after that, make a new folder named `build`, where compiled results are stored. You can do it by using `mkdir build` in terminal.  Of course this name can be any valid linux filename, but usually I just named it `build`. 
The next step is to write `test.c` for testing. You can check `test.c` to view it. In summary, this repo shows like this (README.md is not listed here ^_^):

```bash
cybersh1t@DESKTOP-BLEL2PT:~/prog/Protobuf-test$ tree -I protobuf-c -L 2
.
├── CMakeLists.txt
├── MESSAGES
│   ├── __pycache__
│   ├── channel_matrx.pb-c.c
│   ├── channel_matrx.pb-c.h
│   ├── channel_matrx.proto
│   └── channel_matrx_pb2.py
├── build
│   ├── CMakeCache.txt
│   ├── CMakeFiles
│   ├── Makefile
│   ├── cmake_install.cmake
│   └── prototest
├── receiver.py
└── test.c

4 directories, 11 files
```
## Compile and run
So the next step is to compile and run the code. To do these, you need to run the following command:

```bash
cd build
cmake ../
cmake --build .
```

After compilation is done, the following commands can be used to run the test:

```bash
// C test
sudo ./prototest 

// Python Receiver
python3 receiver.py
```
And the results should be like this:
![image-20240705112255636](https://s2.loli.net/2024/07/05/1pRaHuJoc9KrwWm.png)


Thanks for your watching :)