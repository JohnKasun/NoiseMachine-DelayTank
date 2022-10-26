#pragma once

#include "PluginProcessor.h"
#include "DelayTankView.h"
#include "DelayTankViewAttachment.h"
#include "InfoPanel.h"

#include <list>

//==============================================================================
class AudioPluginAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    enum {
        DelayTankWidth = 700,
        DelayTankHeight = 500,
        InfoPanelHeight = 200
    };
    explicit AudioPluginAudioProcessorEditor (AudioPluginAudioProcessor&, juce::AudioProcessorValueTreeState&);
    ~AudioPluginAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    AudioPluginAudioProcessor& processorRef;
    juce::AudioProcessorValueTreeState& paramRef;

    DelayTankView delayTank;
    std::unique_ptr<DelayTankViewAttachment> delayTankAttachment;

    InfoPanel infoPanel;

    void updateInfoPanel(const Spot* spot);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AudioPluginAudioProcessorEditor)
};
