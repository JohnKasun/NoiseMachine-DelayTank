#include "DelayTankLookAndFeel.h"

Spot::Spot(int id, juce::Rectangle<int> bounds)
	: mId(id), mBounds(bounds)
{
	setBounds(mBounds);
}

void Spot::setCenter(juce::Point<int> newCenter)
{
	mBounds.setCentre(newCenter);
	setBounds(mBounds);
}

juce::Point<int> Spot::getCenter() const
{
	return mBounds.getCentre();
}

void Spot::paint(juce::Graphics& g)
{
	auto area = getLocalBounds();
	g.setColour(juce::Colours::red);
	g.fillEllipse(area.toFloat());
}

void Spot::resized()
{
	setBounds(mBounds);
}

SpotParameterAttachment::SpotParameterAttachment(juce::RangedAudioParameter& parameter, Spot& spot, juce::UndoManager* undoManager)
	: spot(spot), attachment(parameter, [this](float value) { parameterChangedCallback(value); })
{
	spot.addMouseListener(this, false);
}

SpotParameterAttachment::~SpotParameterAttachment()
{
	spot.removeMouseListener(this);
}

void SpotParameterAttachment::parameterChangedCallback(float value)
{
	
}

void SpotParameterAttachment::mouseDown(const juce::MouseEvent& event)
{
	juce::Logger::outputDebugString(spot.getName() + " mouse down");
	attachment.beginGesture();
}

void SpotParameterAttachment::mouseDrag(const juce::MouseEvent& event)
{
	juce::Logger::outputDebugString(spot.getName() + " mouse drag");

	// Convert event to spot position then value
	attachment.setValueAsPartOfGesture(0);
}

void SpotParameterAttachment::mouseUp(const juce::MouseEvent& event)
{
	juce::Logger::outputDebugString(spot.getName() + " mouse up");
	attachment.endGesture();
}


std::unique_ptr<SpotParameterAttachment> makeAttachment(const juce::AudioProcessorValueTreeState& stateToUse,
	const juce::String& parameterID,
	Spot& spot)
{
	if (auto* parameter = stateToUse.getParameter(parameterID))
		return std::make_unique<SpotParameterAttachment>(*parameter, spot, stateToUse.undoManager);

	jassertfalse;
	return nullptr;
}

SpotAttachment::SpotAttachment(juce::AudioProcessorValueTreeState& stateToUse, const juce::String paramIdx, const juce::String paramIdy, const juce::String paramIdSize, Spot& spotToUse)
	: attachX(makeAttachment(stateToUse, paramIdx, spotToUse)),
	  attachY(makeAttachment(stateToUse, paramIdy, spotToUse)),
	  attachSize(makeAttachment(stateToUse, paramIdSize, spotToUse))
{

}
