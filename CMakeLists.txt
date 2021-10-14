cmake_minimum_required(VERSION 3.10)
project(luagrpc)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_library(luagrpc SHARED lib.cpp) 


set(hw_proto_srcs "${CMAKE_CURRENT_BINARY_DIR}/helloworld.pb.cc")
set(hw_proto_hdrs "${CMAKE_CURRENT_BINARY_DIR}/helloworld.pb.h")
set(hw_grpc_srcs "${CMAKE_CURRENT_BINARY_DIR}/helloworld.grpc.pb.cc")
set(hw_grpc_hdrs "${CMAKE_CURRENT_BINARY_DIR}/helloworld.grpc.pb.h")

add_library(hw_grpc_proto ${hw_grpc_srcs} ${hw_grpc_hdrs} ${hw_proto_srcs} ${hw_proto_hdrs})
target_link_libraries(hw_grpc_proto libprotobuf grpc++_reflection grpc++)


include(FetchContent)
FetchContent_Declare(
  gRPC
  GIT_REPOSITORY https://github.com/grpc/grpc
  GIT_TAG        v1.41.0
)
set(FETCHCONTENT_QUIET OFF)
FetchContent_MakeAvailable(gRPC)
target_link_libraries(luagrpc grpc++ libprotobuf grpc++_reflection)
find_package(Lua 5.3 REQUIRED)


