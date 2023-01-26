#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
AudioPluginAudioProcessorEditor::AudioPluginAudioProcessorEditor (AudioPluginAudioProcessor& p, juce::AudioProcessorValueTreeState& vts)
    : AudioProcessorEditor (&p), processorRef (p), paramRef(vts), delayTank(processorRef.getMaxNumberOfDelays())
{
    juce::ignoreUnused (processorRef);
    addAndMakeVisible(delayTank);
    delayTank.onSpotUpdate = [this](const Spot* spot) { updateInfoPanel(spot); };
    delayTankAttachment.reset(new DelayTankViewAttachment(paramRef, "pan", "delay", "gain", "enabled", delayTank));

    addAndMakeVisible(infoPanel);

    setSize(DelayTankWidth + InfoPanelWidth, DelayTankHeight);
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
    auto area = getBounds();
    delayTank.setBounds(area.removeFromLeft(DelayTankWidth));
    infoPanel.setBounds(area);
}

void AudioPluginAudioProcessorEditor::updateInfoPanel(const Spot* spot) 
{
    juce::String info;
    if (spot) {
        auto delayTime = "DelayTime : " + juce::String(spot->getValue(Spot::yAxis)) + "s\n";
        auto pan = "Pan : " + juce::String(spot->getValue(Spot::xAxis)) + "s\n";
        auto gain = "Gain : " + juce::String(spot->getValue(Spot::zAxis)) + "s\n";
        info = delayTime + pan + gain;
    }
    infoPanel.setText(info);
    repaint();
}


