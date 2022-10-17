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
		yAxis
	};
	Spot();
	void paint(juce::Graphics& g) override;
	void setRange(Dimension dimen, float min, float max);

	void setValue(Dimension dimen, float value);
	float getValue(Dimension dimen) const;

	void setNormValue(Dimension dimen, float value);
	float getNormValue(Dimension dimen);

	void setVisible(bool shouldBeVisible) override;
private:
	juce::Slider sliderX;
	juce::Slider sliderY;
	juce::TextButton buttonVisibility;
};

class SpotAttachment
{
public:
	SpotAttachment(juce::AudioProcessorValueTreeState& stateToUse,const juce::String paramIdx, const juce::String paramIdy, const juce::String paramIdVisibility, Spot& spotToUse);
	~SpotAttachment() = default;
private:
	std::unique_ptr<juce::SliderParameterAttachment> attachmentX;
	std::unique_ptr<juce::SliderParameterAttachment> attachmentY;
	std::unique_ptr<juce::ButtonParameterAttachment> attachmentVisibility;
};