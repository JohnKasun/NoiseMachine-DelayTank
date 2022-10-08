#include "SpotAttachment.h"

SpotParameterAttachment::SpotParameterAttachment(juce::RangedAudioParameter& xParam,
													juce::RangedAudioParameter& yParam,
													Spot& s)
	: spot(s),
	  xAttachment(xParam, [this](float f) {setValue(f); }),
	  yAttachment(yParam, [this](float f) {setValue(f); })
{
	sendInitialUpdate();
	spot.addMouseListener(this, false);
}

SpotParameterAttachment::~SpotParameterAttachment()
{
	spot.removeMouseListener(this);
}

void SpotParameterAttachment::sendInitialUpdate()
{
}

void SpotParameterAttachment::setValue(float newValue)
{
}

void SpotParameterAttachment::mouseDrag(const juce::MouseEvent& event)
{
}

SpotAttachment::SpotAttachment(juce::AudioProcessorValueTreeState& stateToUse,
								const juce::String& xParamId,
								const juce::String& yParamId,
								Spot& spot)
	: attachment(std::make_unique<SpotParameterAttachment>(*stateToUse.getParameter(xParamId),
															*stateToUse.getParameter(yParamId),
															spot)) {

}
