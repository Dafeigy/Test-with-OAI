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
