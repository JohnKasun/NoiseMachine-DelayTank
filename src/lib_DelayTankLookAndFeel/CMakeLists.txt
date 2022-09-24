set(LIB lib_DelayTankLookAndFeel)
add_library(${LIB} STATIC include/DelayTankLookAndFeel.h DelayTankLookAndFeel.cpp)
target_include_directories(${LIB} PUBLIC include)
target_link_libraries(${LIB} 
PRIVATE 
    juce::juce_gui_extra
PUBLIC
    juce::juce_recommended_config_flags
    juce::juce_recommended_lto_flags
    juce::juce_recommended_warning_flags)