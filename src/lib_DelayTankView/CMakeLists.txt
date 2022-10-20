set(LIB lib_DelayTankView)
add_library(${LIB} 
    STATIC 
        include/DelayTankView.h 
        include/Spot.h
        include/SpotAttachment.h
        DelayTankView.cpp
        Spot.cpp
        SpotAttachment.cpp)
target_include_directories(${LIB} PUBLIC include)
target_link_libraries(${LIB} 
PRIVATE 
    juce::juce_gui_extra
    juce::juce_audio_utils
PUBLIC
    juce::juce_recommended_config_flags
    juce::juce_recommended_lto_flags
    juce::juce_recommended_warning_flags)