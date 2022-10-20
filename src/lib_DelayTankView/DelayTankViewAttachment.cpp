#include "DelayTankViewAttachment.h"

DelayTankViewAttachment::DelayTankViewAttachment(juce::AudioProcessorValueTreeState& stateToUse, const juce::String paramIdx, const juce::String paramIdy, const juce::String paramIdz, const juce::String paramIdVisibility, DelayTankView& delayTank)
{
	for (int i = 0; i < delayTank.spots.size(); i++) {
		auto id = juce::String(i);
		attachments.emplace_back(new SpotAttachment(stateToUse, paramIdx + id, paramIdy + id, paramIdz + id, paramIdVisibility + id, delayTank.spots.at(i)));
	}
}
