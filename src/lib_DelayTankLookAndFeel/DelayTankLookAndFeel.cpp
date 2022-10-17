#include "DelayTankLookAndFeel.h"

Spot::Spot()
{
	setInterceptsMouseClicks(false, false);
}

void Spot::paint(juce::Graphics& g)
{
	g.setColour(color);
	g.fillAll();
}

void Spot::setRange(Dimension dimen, float min, float max)
{
	switch (dimen) {
	case Dimension::xAxis:
		sliderX.setRange(min, max);
		break;
	case Dimension::yAxis:
		sliderY.setRange(min, max);
		break;
	default:
		sliderZ.setRange(min, max);
	}
}

void Spot::setValue(Dimension dimen, float value)
{
	switch (dimen) {
	case Dimension::xAxis:
		sliderX.setValue(value, juce::sendNotification);
		break;
	case Dimension::yAxis:
		sliderY.setValue(value, juce::sendNotification);
		break;
	default:
		sliderZ.setValue(value, juce::sendNotification);
	}
}

float Spot::getValue(Dimension dimen) const
{
	switch (dimen) {
	case Dimension::xAxis:
		return sliderX.getValue();
	case Dimension::yAxis:
		return sliderY.getValue();
	default:
		return sliderZ.getValue();
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
	case Dimension::yAxis:
		denormValue = value * (sliderY.getMaximum() - sliderY.getMinimum()) + sliderY.getMinimum();
		sliderY.setValue(denormValue);
		break;
	default:
		denormValue = value * (sliderZ.getMaximum() - sliderZ.getMinimum()) + sliderZ.getMinimum();
		sliderZ.setValue(denormValue);
	}
}

float Spot::getNormValue(Dimension dimen)
{
	switch (dimen) {
	case Dimension::xAxis:
		return (sliderX.getValue() - sliderX.getMinimum()) / (sliderX.getMaximum() - sliderX.getMinimum());
	case Dimension::yAxis:
		return (sliderY.getValue() - sliderY.getMinimum()) / (sliderY.getMaximum() - sliderY.getMinimum());
	default:
		return (sliderZ.getValue() - sliderZ.getMinimum()) / (sliderZ.getMaximum() - sliderZ.getMinimum());
	}
}

void Spot::setVisible(bool shouldBeVisible)
{
	juce::Component::setVisible(shouldBeVisible);
	buttonVisibility.setToggleState(shouldBeVisible, juce::sendNotification);
	auto result = buttonVisibility.getToggleState();
	if (result)
		juce::Logger::outputDebugString("Button is on");
	else
		juce::Logger::outputDebugString("Button is off");
}

void Spot::setColor(juce::Colour newColor)
{
	color = newColor;
}

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
