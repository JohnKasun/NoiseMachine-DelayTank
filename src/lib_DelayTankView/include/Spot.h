#pragma once

#include <cassert>
#include <juce_gui_extra/juce_gui_extra.h>
#include <juce_audio_processors/juce_audio_processors.h>

class Spot : public juce::Component
{
	friend class SpotAttachment;
public:
	enum Dimension {
		xAxis,
		yAxis,
		zAxis
	};
	Spot();
	void paint(juce::Graphics& g) override;
	void setRange(Dimension dimen, float min, float max);

	void setValue(Dimension dimen, float value);
	float getValue(Dimension dimen) const;

	void setNormValue(Dimension dimen, float value);
	float getNormValue(Dimension dimen);

	void setVisible(bool shouldBeVisible) override;
	void setColor(juce::Colour newColor);
private:
	juce::Colour color = juce::Colours::red;
	juce::Slider sliderX;
	juce::Slider sliderY;
	juce::Slider sliderZ;
	juce::TextButton buttonVisibility;
};