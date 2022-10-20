#pragma once

#include "DelayTankView.h"
#include "SpotAttachment.h"

class DelayTankViewAttachment
{
public:
	DelayTankViewAttachment(juce::AudioProcessorValueTreeState& stateToUse, const juce::String generalParamIdx, const juce::String generalParamIdy, const juce::String generalParamIdz, const juce::String generalParamIdVisibility, DelayTankView& delayTank);
	~DelayTankViewAttachment() = default;
private:
	std::vector<std::unique_ptr<SpotAttachment>> attachments;
};
