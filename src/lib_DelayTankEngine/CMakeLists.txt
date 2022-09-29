set(LIB lib_DelayTankEngine)
add_library(${LIB} STATIC include/DelayTankEngine.h include/Delay.h Delay.cpp DelayTankEngine.cpp)
target_include_directories(${LIB} PUBLIC include)
target_link_libraries(${LIB} PUBLIC lib_RingBuffer)