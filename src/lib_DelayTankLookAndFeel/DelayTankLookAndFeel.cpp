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
