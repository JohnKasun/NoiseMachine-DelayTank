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

void Spot::setValueRangeX(juce::NormalisableRange<float> xRange)
{
	mValueRangeX = xRange;
}

void Spot::setValueRangeY(juce::NormalisableRange<float> yRange)
{
	mValueRangeY = yRange;
}

juce::NormalisableRange<float> Spot::getValueRangeX() const
{
	return mValueRangeX;
}

juce::NormalisableRange<float> Spot::getValueRangeY() const
{
	return mValueRangeY;
}

void Spot::setValueX(float value)
{
	auto valueNorm = mValueRangeX.convertTo0to1(value);
	auto xPos = valueNorm * getParentWidth();
	setCenter(juce::Point<int>(xPos, getCenter().y));
}

void Spot::setValueY(float value)
{
	auto valueNorm = mValueRangeY.convertTo0to1(value);
	auto yPos = valueNorm * getParentHeight();
	setCenter(juce::Point<int>(getCenter().x, yPos));
}

float Spot::getValueX() const
{
	auto xPosNorm = static_cast<float>(getCenter().x) / getParentWidth();
	return mValueRangeX.convertFrom0to1(juce::jlimit<float>(0, 1, xPosNorm));
}

float Spot::getValueY() const
{
	auto yPosNorm = static_cast<float>(getCenter().y) / getParentHeight();
	return mValueRangeY.convertFrom0to1(juce::jlimit<float>(0, 1, yPosNorm));
}

SpotParameterAttachment::SpotParameterAttachment(juce::RangedAudioParameter& xParam, juce::RangedAudioParameter& yParam, juce::RangedAudioParameter& sizeParam, Spot& spot)
	: spot(spot), 
	xAttach(xParam, [&spot](float rawValue) { spot.setValueX(rawValue); }),
	yAttach(yParam, [&spot](float rawValue) { spot.setValueY(rawValue); }),
	sizeAttach(sizeParam, [&spot](float rawValue) { ; })
{
	spot.setValueRangeX(xParam.getNormalisableRange());
	spot.setValueRangeY(yParam.getNormalisableRange());

	spot.addMouseListener(this, false);
}

SpotParameterAttachment::~SpotParameterAttachment()
{
	spot.removeMouseListener(this);
}

void SpotParameterAttachment::mouseDown(const juce::MouseEvent& event)
{
	juce::Logger::outputDebugString(spot.getName() + " mouse down");
	xAttach.beginGesture();
	yAttach.beginGesture();
	sizeAttach.beginGesture();
}

void SpotParameterAttachment::mouseDrag(const juce::MouseEvent& event)
{
	juce::Logger::outputDebugString(spot.getName() + " mouse drag");

	// Convert event to spot position then value
	//xAttach.setValueAsPartOfGesture(xParamValue);
	//yAttach.setValueAsPartOfGesture(yParamValue);

}

void SpotParameterAttachment::mouseUp(const juce::MouseEvent& event)
{
	juce::Logger::outputDebugString(spot.getName() + " mouse up");
	xAttach.endGesture();
	yAttach.endGesture();
	sizeAttach.endGesture();
}


std::unique_ptr<SpotParameterAttachment> makeAttachment(const juce::AudioProcessorValueTreeState& stateToUse,
	const juce::String& paramIdX,
	const juce::String& paramIdY,
	const juce::String& paramIdSize,
	Spot& spot)
{
	auto* paramX = stateToUse.getParameter(paramIdX);
	auto* paramY = stateToUse.getParameter(paramIdY);
	auto* paramSize = stateToUse.getParameter(paramIdSize);
	if (paramX && paramY && paramSize)
		return std::make_unique<SpotParameterAttachment>(*paramX, *paramY, *paramSize, spot);

	jassertfalse;
	return nullptr;
}

SpotAttachment::SpotAttachment(juce::AudioProcessorValueTreeState& stateToUse, const juce::String paramIdx, const juce::String paramIdy, const juce::String paramIdSize, Spot& spotToUse)
	: attachment(makeAttachment(stateToUse, paramIdx, paramIdy, paramIdSize, spotToUse))
{

}
