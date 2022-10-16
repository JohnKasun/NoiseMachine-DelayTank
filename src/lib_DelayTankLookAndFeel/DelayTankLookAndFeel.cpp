#include "DelayTankLookAndFeel.h"

Spot::Spot()
{

}

void Spot::paint(juce::Graphics& g)
{
	g.setColour(juce::Colours::red);
	g.fillAll();
}

void Spot::setRange(Dimension dimen, float min, float max)
{
	switch (dimen) {
	case Dimension::xAxis:
		sliderX.setRange(min, max);
		break;
	default:
		sliderY.setRange(min, max);
	}
}

void Spot::setValue(Dimension dimen, float value)
{
	switch (dimen) {
	case Dimension::xAxis:
		sliderX.setValue(value, juce::sendNotification);
		break;
	default:
		sliderY.setValue(value, juce::sendNotification);
	}
}

float Spot::getValue(Dimension dimen) const
{
	switch (dimen) {
	case Dimension::xAxis:
		return sliderX.getValue();
	default:
		return sliderY.getValue();
	}
}

void Spot::setNormValue(Dimension dimen, float value)
{
	auto denormValue = value;
	switch (dimen) {
	case Dimension::xAxis:
		denormValue = value * (sliderX.getMaximum() - sliderX.getMinimum()) + sliderX.getMinimum();
		sliderX.setValue(denormValue);
		break;
	default:
		denormValue = value * (sliderY.getMaximum() - sliderY.getMinimum()) + sliderY.getMinimum();
		sliderY.setValue(denormValue);
		break;
	}
}

float Spot::getNormValue(Dimension dimen)
{
	switch (dimen) {
	case Dimension::xAxis:
		return (sliderX.getValue() - sliderX.getMinimum()) / (sliderX.getMaximum() - sliderX.getMinimum());
		break;
	default:
		return (sliderY.getValue() - sliderY.getMinimum()) / (sliderY.getMaximum() - sliderY.getMinimum());
		break;
	}
}

//
//SpotParameterAttachment::SpotParameterAttachment(juce::RangedAudioParameter& xParam, juce::RangedAudioParameter& yParam, juce::RangedAudioParameter& sizeParam, Spot& spot)
//	: spot(spot), 
//	xAttach(xParam, [&spot](float rawValue) { spot.setValueX(rawValue); }),
//	yAttach(yParam, [&spot](float rawValue) { spot.setValueY(rawValue); }),
//	sizeAttach(sizeParam, [&spot](float rawValue) { ; })
//{
//	spot.setValueRangeX(xParam.getNormalisableRange());
//	spot.setValueRangeY(yParam.getNormalisableRange());
//
//	spot.addMouseListener(this, false);
//}
//
//SpotParameterAttachment::~SpotParameterAttachment()
//{
//	spot.removeMouseListener(this);
//}
//
//void SpotParameterAttachment::mouseDown(const juce::MouseEvent& event)
//{
//	juce::Logger::outputDebugString(spot.getName() + " mouse down");
//	xAttach.beginGesture();
//	yAttach.beginGesture();
//	sizeAttach.beginGesture();
//}
//
//void SpotParameterAttachment::mouseDrag(const juce::MouseEvent& event)
//{
//	juce::Logger::outputDebugString(spot.getName() + " mouse drag");
//
//	// Convert event to spot position then value
//	//xAttach.setValueAsPartOfGesture(xParamValue);
//	//yAttach.setValueAsPartOfGesture(yParamValue);
//
//}
//
//void SpotParameterAttachment::mouseUp(const juce::MouseEvent& event)
//{
//	juce::Logger::outputDebugString(spot.getName() + " mouse up");
//	xAttach.endGesture();
//	yAttach.endGesture();
//	sizeAttach.endGesture();
//}
//
//
//std::unique_ptr<SpotParameterAttachment> makeAttachment(const juce::AudioProcessorValueTreeState& stateToUse,
//	const juce::String& paramIdX,
//	const juce::String& paramIdY,
//	const juce::String& paramIdSize,
//	Spot& spot)
//{
//	auto* paramX = stateToUse.getParameter(paramIdX);
//	auto* paramY = stateToUse.getParameter(paramIdY);
//	auto* paramSize = stateToUse.getParameter(paramIdSize);
//	if (paramX && paramY && paramSize)
//		return std::make_unique<SpotParameterAttachment>(*paramX, *paramY, *paramSize, spot);
//
//	jassertfalse;
//	return nullptr;
//}
//
//SpotAttachment::SpotAttachment(juce::AudioProcessorValueTreeState& stateToUse, const juce::String paramIdx, const juce::String paramIdy, const juce::String paramIdSize, Spot& spotToUse)
//	: attachment(makeAttachment(stateToUse, paramIdx, paramIdy, paramIdSize, spotToUse))
//{
//
//}
