#pragma once

#include <juce_gui_extra/juce_gui_extra.h>
#include <juce_audio_processors/juce_audio_processors.h>

class Spot
{

};

class SpotParameterAttachment : private juce::MouseListener 
{
public:
    /** Creates a connection between a plug-in parameter and a Slider.

        @param parameter     The parameter to use
        @param slider        The Slider to use
        @param undoManager   An optional UndoManager
    */
    SpotParameterAttachment(juce::RangedAudioParameter& parameter, Spot& spot);

    /** Destructor. */
    ~SpotParameterAttachment() override;

    /** Call this after setting up your slider in the case where you need to do
        extra setup after constructing this attachment.
    */
    void sendInitialUpdate();

private:
    void setValue(float newValue);
    void mouseDrag(const juce::MouseEvent& event) override;

    Spot& spot;
    juce::ParameterAttachment attachment;
    bool ignoreCallbacks = false;
};

class SpotAttachment
{
	SpotAttachment(juce::AudioProcessorValueTreeState& stateToUse, 
					const juce::String& xParamId,
					const juce::String& yParamId,
					Spot& spot);
	
private:
	std::unique_ptr<SpotParameterAttachment> attachment;
	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(SpotAttachment)
};
