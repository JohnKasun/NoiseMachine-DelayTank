#pragma once

#include <memory>

#include <juce_gui_extra/juce_gui_extra.h>
#include <juce_audio_processors/juce_audio_processors.h>

class Spot : public juce::Component
{

};

class SpotParameterAttachment : private juce::MouseListener 
{
public:
    SpotParameterAttachment(juce::RangedAudioParameter& xParam, juce::RangedAudioParameter& yParam, Spot& spot);
    ~SpotParameterAttachment() override;

    void sendInitialUpdate();

private:
    void setValue(float newValue);
    void mouseDrag(const juce::MouseEvent& event) override;

    Spot& spot;
    juce::ParameterAttachment xAttachment;
    juce::ParameterAttachment yAttachment;
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
