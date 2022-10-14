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
private:
	int mId;
	juce::Rectangle<int> mBounds;
};

//class SpotAttachment : public juce::MouseListener, juce::AudioProcessorParameter::Listener
//{
//public:
//	SpotAttachment(juce::AudioProcessorValueTreeState& stateToUse,const juce::String paramId, Spot& spotToUse);
//	~SpotAttachment() = default;
//private:
//	Spot& spot;
//	juce::RangedAudioParameter* param;
//};