juce_add_gui_app(app_GraphicsTest
    PRODUCT_NAME 
        "app_GraphicsTest")
target_sources(app_GraphicsTest 
    PRIVATE 
        Main.cpp 
        include/MainComponent.h
        MainComponent.cpp)
target_include_directories(app_GraphicsTest PUBLIC include)
target_link_libraries(app_GraphicsTest 
    PRIVATE 
        lib_DelayTankView
        juce::juce_gui_extra
        juce::juce_audio_utils
    PUBLIC
        juce::juce_recommended_config_flags
        juce::juce_recommended_lto_flags
        juce::juce_recommended_warning_flags)

target_compile_definitions(app_GraphicsTest
    PRIVATE
        # JUCE_WEB_BROWSER and JUCE_USE_CURL would be on by default, but you might not need them.
        JUCE_WEB_BROWSER=0  # If you remove this, add `NEEDS_WEB_BROWSER TRUE` to the `juce_add_gui_app` call
        JUCE_USE_CURL=1     # If you remove this, add `NEEDS_CURL TRUE` to the `juce_add_gui_app` call
        JUCE_USE_OGG=1
	    JUCE_APPLICATION_NAME_STRING="$<TARGET_PROPERTY:app_GraphicsTest,JUCE_PRODUCT_NAME>"
	    JUCE_APPLICATION_VERSION_STRING="$<TARGET_PROPERTY:app_GraphicsTest,JUCE_VERSION>")