#pragma once

#include <cassert>
#include <juce_gui_extra/juce_gui_extra.h>
#include <juce_audio_processors/juce_audio_processors.h>

class Spot : public juce::Component
{
public:
	Spot(int id = 0, juce::Rectangle<int> bounds = {0,0,10,10});
	void setCenter(juce::Point<int> newCenter);
	juce::Point<int> getCenter() const;
	void paint(juce::Graphics& g) override;
	void resized() override;

	void setValueRangeX(juce::NormalisableRange<float> xRange);
	void setValueRangeY(juce::NormalisableRange<float> yRange);
	juce::NormalisableRange<float> getValueRangeX() const;
	juce::NormalisableRange<float> getValueRangeY() const;

	void setValueX(float value);
	void setValueY(float value);
	float getValueX() const;
	float getValueY() const;
private:
	int mId;
	juce::Rectangle<int> mBounds;
	juce::NormalisableRange<float> mValueRangeX = juce::NormalisableRange<float>(0, 1);
	juce::NormalisableRange<float> mValueRangeY = juce::NormalisableRange<float>(0, 1);
};

class SpotParameterAttachment : public juce::MouseListener
{
public:
    SpotParameterAttachment(juce::RangedAudioParameter& xParam, juce::RangedAudioParameter& yParam, juce::RangedAudioParameter& sizeParam, Spot& spot);
    virtual ~SpotParameterAttachment();

private:
    Spot& spot;
    juce::ParameterAttachment xAttach;
    juce::ParameterAttachment yAttach;
    juce::ParameterAttachment sizeAttach;

	// Update Parameter Here
	void mouseDown(const juce::MouseEvent& event) override;
	void mouseDrag(const juce::MouseEvent& event) override;
	void mouseUp(const juce::MouseEvent& event) override;


};


class SpotAttachment
{
public:
	SpotAttachment(juce::AudioProcessorValueTreeState& stateToUse,const juce::String paramIdx, const juce::String paramIdy, const juce::String paramIdSize, Spot& spotToUse);
	~SpotAttachment() = default;
private:
	std::unique_ptr<SpotParameterAttachment> attachment;
};