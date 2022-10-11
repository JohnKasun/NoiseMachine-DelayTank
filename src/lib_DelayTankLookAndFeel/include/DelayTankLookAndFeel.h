#pragma once

#include <juce_gui_extra/juce_gui_extra.h>

class Spot : public juce::Component
{
public:
	Spot(int id = 0, juce::Rectangle<int> bounds = {0,0,10,10});
	void setCenter(juce::Point<int> newCenter);
	juce::Point<int> getCenter() const;
	void paint(juce::Graphics& g) override;
	void resized() override;
private:
	int mId;
	juce::Rectangle<int> mBounds;
};