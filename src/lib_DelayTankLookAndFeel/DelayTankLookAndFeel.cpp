#include "DelayTankLookAndFeel.h"

Spot::Spot(int id, juce::Point<float> center)
	: mId(id), mCenter(center)
{
}

void Spot::setCenter(juce::Point<float> newCenter)
{
	mCenter = newCenter;
}

juce::Point<float> Spot::getCenter() const
{
	return mCenter;
}

void Spot::paint(juce::Graphics& g)
{
	juce::Rectangle<float> r(0, 0, 100, 100);
	r.setCentre(mCenter);
	g.setColour(juce::Colours::red);
	g.fillEllipse(r);
}

void Spot::resized()
{
}
