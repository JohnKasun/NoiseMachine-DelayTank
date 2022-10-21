#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
AudioPluginAudioProcessorEditor::AudioPluginAudioProcessorEditor (AudioPluginAudioProcessor& p, juce::AudioProcessorValueTreeState& vts)
    : AudioProcessorEditor (&p), processorRef (p), paramRef(vts), delayTank(processorRef.getMaxNumberOfDelays())
{
    juce::ignoreUnused (processorRef);
    addAndMakeVisible(delayTank);
    delayTankAttachment.reset(new DelayTankViewAttachment(paramRef, "delay", "gain", "pan", "enabled", delayTank));

    setSize(400, 400);
}

AudioPluginAudioProcessorEditor::~AudioPluginAudioProcessorEditor()
{
}

//==============================================================================
void AudioPluginAudioProcessorEditor::paint(juce::Graphics& g)
{

}

void AudioPluginAudioProcessorEditor::resized()
{
    delayTank.setBounds(getBounds());
}



