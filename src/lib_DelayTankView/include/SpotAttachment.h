#pragma once

#include <cassert>
#include <juce_gui_extra/juce_gui_extra.h>
#include <juce_audio_processors/juce_audio_processors.h>

#include "Spot.h"

class SpotAttachment
{
public:
	SpotAttachment(juce::AudioProcessorValueTreeState& stateToUse, const juce::String paramIdx, const juce::String paramIdy, const juce::String paramIdz, const juce::String paramIdVisibility, Spot& spotToUse);
	~SpotAttachment() = default;
private:
	std::unique_ptr<juce::SliderParameterAttachment> attachmentX;
	std::unique_ptr<juce::SliderParameterAttachment> attachmentY;
	std::unique_ptr<juce::SliderParameterAttachment> attachmentZ;
	std::unique_ptr<juce::ButtonParameterAttachment> attachmentVisibility;
};