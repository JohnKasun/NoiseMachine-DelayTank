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

class SpotParameterAttachment
{
public:
    SpotParameterAttachment(juce::RangedAudioParameter& parameter, Spot& spot, juce::UndoManager* undoManager = nullptr);
    ~SpotParameterAttachment();

	void callback(float value);
private:
    Spot& spot;
    juce::ParameterAttachment attachment;
    bool ignoreCallbacks = false;
};


class SpotAttachment
{
public:
	SpotAttachment(juce::AudioProcessorValueTreeState& stateToUse,const juce::String paramIdx, const juce::String paramIdy, const juce::String paramIdSize, Spot& spotToUse);
	~SpotAttachment() = default;
private:
	std::unique_ptr<SpotParameterAttachment> attachX;
	std::unique_ptr<SpotParameterAttachment> attachY;
	std::unique_ptr<SpotParameterAttachment> attachSize;
};