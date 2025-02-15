cmake_minimum_required(VERSION 3.10)
project(BulbStateMachine)

set(CMAKE_BUILD_TYPE Debug)  # Ensure Debug build type
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")  # -g flag for debug symbols

set(SOURCE_DIR src)

include_directories(${SOURCE_DIR})

# List of source files
set(SOURCES
    ${SOURCE_DIR}/Bulb.cpp
    ${SOURCE_DIR}/FSM.cpp
    ${SOURCE_DIR}/State.cpp
    ${SOURCE_DIR}/Transition.cpp
    main.cpp
)

add_executable(main ${SOURCES})
