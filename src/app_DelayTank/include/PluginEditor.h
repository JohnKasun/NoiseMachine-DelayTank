#pragma once

#include "PluginProcessor.h"
#include "DelayTankLookAndFeel.h"

#include <list>

//==============================================================================
class AudioPluginAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    explicit AudioPluginAudioProcessorEditor (AudioPluginAudioProcessor&, juce::AudioProcessorValueTreeState&);
    ~AudioPluginAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

    void mouseDown(const juce::MouseEvent& event) override;
    void mouseDrag(const juce::MouseEvent& event) override;
    void mouseUp(const juce::MouseEvent& event) override;
    void mouseDoubleClick(const juce::MouseEvent& event) override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    AudioPluginAudioProcessor& processorRef;
    juce::AudioProcessorValueTreeState& paramRef;

    Spot spot;
    std::unique_ptr<SpotAttachment> spotAttachment;
    Spot* dragging = nullptr;
    Spot* selected = nullptr;

    juce::Slider gainSlider;

    void setSpotPosition(Spot& spot, juce::Point<float> point);
    void selectSpot(Spot& spot);
    void clearSelectedSpot();

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AudioPluginAudioProcessorEditor)
};
