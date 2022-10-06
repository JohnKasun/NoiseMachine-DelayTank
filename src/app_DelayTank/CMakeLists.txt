set(APP app_DelayTank)
juce_add_plugin(${APP}
    PLUGIN_MANUFACTURER_CODE John
    PLUGIN_CODE Dtnk
    FORMATS AU AUv3 VST3 Standalone
    PRODUCT_NAME "DelayTank"
    COMPANY_NAME NoiseMachine)

target_sources(${APP}
    PRIVATE
        PluginEditor.cpp
        PluginProcessor.cpp)

target_include_directories(${APP} PRIVATE include)

target_compile_definitions(${APP}
    PUBLIC
        # JUCE_WEB_BROWSER and JUCE_USE_CURL would be on by default, but you might not need them.
        JUCE_WEB_BROWSER=0  # If you remove this, add `NEEDS_WEB_BROWSER TRUE` to the `juce_add_plugin` call
        JUCE_USE_CURL=0     # If you remove this, add `NEEDS_CURL TRUE` to the `juce_add_plugin` call
        JUCE_VST3_CAN_REPLACE_VST2=0)

target_link_libraries(${APP}
    PRIVATE
        lib_DelayTankEngine
        juce::juce_audio_utils
        juce::juce_gui_extra
    PUBLIC
        juce::juce_recommended_config_flags
        juce::juce_recommended_lto_flags
        juce::juce_recommended_warning_flags)