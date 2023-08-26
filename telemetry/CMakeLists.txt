cmake_minimum_required(VERSION 3.14 FATAL_ERROR)
set( PROJECT_NAME msp_telemetry )
project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} \
    -fsanitize=address \
    -fsanitize=bool \
    -fsanitize=bounds \
    -fsanitize=enum \
    -fsanitize=float-cast-overflow \
    -fsanitize=float-divide-by-zero \
    -fsanitize=nonnull-attribute \
    -fsanitize=returns-nonnull-attribute \
    -fsanitize=signed-integer-overflow \
    -fsanitize=undefined \
    -fsanitize=vla-bound \
    -fno-sanitize=alignment \
    -fsanitize=leak \
    -fsanitize=object-size \
")

OPTION(BUILD_EXAMPLES "Build examples" ON)

set(BUILD_SHARED_LIBS "ON")
set(MSP_SOURCE_DIR msp)
set(MSP_INCLUDE_DIR msp)
include_directories(${MSP_INCLUDE_DIR})

add_library(mspclient ${MSP_SOURCE_DIR}/Client.cpp ${MSP_SOURCE_DIR}/PeriodicTimer.cpp)


if( BUILD_EXAMPLES )
    # client test for blocking read
    add_executable(client_read_test examples/client_read_test.cpp)
    target_link_libraries(client_read_test mspclient)

    add_executable( client_async_read_test examples/client_async_read_test.cpp )
    target_link_libraries(client_async_read_test mspclient)
endif()