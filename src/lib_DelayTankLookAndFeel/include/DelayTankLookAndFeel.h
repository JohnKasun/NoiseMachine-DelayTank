#pragma once

#include <juce_gui_extra/juce_gui_extra.h>

class Spot : public juce::Component
{
public:
	Spot(int id = 0, juce::Point<float> center = {0,0});
	void setCenter(juce::Point<float> newCenter);
	juce::Point<float> getCenter() const;
	void paint(juce::Graphics& g) override;
	void resized() override;
private:
	int mId;
	juce::Point<float> mCenter;
};