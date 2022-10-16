#pragma once

#include <cassert>
#include <juce_gui_extra/juce_gui_extra.h>
#include <juce_audio_processors/juce_audio_processors.h>

class Spot : public juce::Component
{
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
private:
	juce::Slider sliderX;
	juce::Slider sliderY;
};

//class SpotParameterAttachment : public juce::MouseListener
//{
//public:
//    SpotParameterAttachment(juce::RangedAudioParameter& xParam, juce::RangedAudioParameter& yParam, juce::RangedAudioParameter& sizeParam, Spot& spot);
//    virtual ~SpotParameterAttachment();
//
//private:
//    Spot& spot;
//    juce::ParameterAttachment xAttach;
//    juce::ParameterAttachment yAttach;
//    juce::ParameterAttachment sizeAttach;
//
//	// Update Parameter Here
//	void mouseDown(const juce::MouseEvent& event) override;
//	void mouseDrag(const juce::MouseEvent& event) override;
//	void mouseUp(const juce::MouseEvent& event) override;
//
//
//};
//
//
//class SpotAttachment
//{
//public:
//	SpotAttachment(juce::AudioProcessorValueTreeState& stateToUse,const juce::String paramIdx, const juce::String paramIdy, const juce::String paramIdSize, Spot& spotToUse);
//	~SpotAttachment() = default;
//private:
//	std::unique_ptr<SpotParameterAttachment> attachment;
//};