set(LIB lib_DelayTankEngine)
add_library(${LIB} STATIC include/DelayTankEngine.h DelayTankEngine.cpp)
target_include_directories(${LIB} PUBLIC include)