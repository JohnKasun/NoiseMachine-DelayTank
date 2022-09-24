CMAKE_MINIMUM_REQUIRED(VERSION 3.20)
Project(NoiseMachine-DelayTank VERSION 1.0.0)
set(CMAKE_CXX_STANDARD 20)

include_directories(include)

add_subdirectory(extern)
add_subdirectory(src bin)
add_subdirectory(test)