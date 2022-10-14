#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
AudioPluginAudioProcessorEditor::AudioPluginAudioProcessorEditor (AudioPluginAudioProcessor& p, juce::AudioProcessorValueTreeState& vts)
    : AudioProcessorEditor (&p), processorRef (p), paramRef(vts)
{
    juce::ignoreUnused (processorRef);

    for (int i = 0; i < AudioPluginAudioProcessor::getMaxNumberOfDelays(); i++) {
        auto id = juce::String(i);
        mSpots.emplace_back(i);
        auto& spot = mSpots.back();
        spot.setName("Spot " + id);
        mSpotAttachments.emplace_back(new SpotAttachment(paramRef, id + "p", id + "d", id + "g", spot));
        addAndMakeVisible(spot);
    }

    setSize(400, 300);
}

AudioPluginAudioProcessorEditor::~AudioPluginAudioProcessorEditor()
{
}

//==============================================================================
void AudioPluginAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
}

void AudioPluginAudioProcessorEditor::resized()
{
    auto area = getLocalBounds();

}

void AudioPluginAudioProcessorEditor::mouseDown(const juce::MouseEvent& event)
{
}

void AudioPluginAudioProcessorEditor::mouseDrag(const juce::MouseEvent& event)
{
}

void AudioPluginAudioProcessorEditor::mouseUp(const juce::MouseEvent& event)
{
}

