#include "SpotAttachment.h"

template<typename Attachment, typename Control>
std::unique_ptr<Attachment> makeAttachment(const juce::AudioProcessorValueTreeState& stateToUse,
	const juce::String& paramId,
	Control& control)
{
	auto* param = stateToUse.getParameter(paramId);
	if (param)
		return std::make_unique<Attachment>(*param, control);

	jassertfalse;
	return nullptr;
}

SpotAttachment::SpotAttachment(juce::AudioProcessorValueTreeState& stateToUse, const juce::String paramIdx, const juce::String paramIdy, const juce::String paramIdz, const juce::String paramIdVisibility, Spot& spotToUse)
	: attachmentX(makeAttachment<juce::SliderParameterAttachment>(stateToUse, paramIdx, spotToUse.sliderX)),
	attachmentY(makeAttachment<juce::SliderParameterAttachment>(stateToUse, paramIdy, spotToUse.sliderY)),
	attachmentZ(makeAttachment<juce::SliderParameterAttachment>(stateToUse, paramIdz, spotToUse.sliderZ)),
	attachmentVisibility(makeAttachment<juce::ButtonParameterAttachment>(stateToUse, paramIdVisibility, spotToUse.buttonVisibility))
{

}
