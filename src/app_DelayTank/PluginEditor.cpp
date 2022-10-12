#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
AudioPluginAudioProcessorEditor::AudioPluginAudioProcessorEditor (AudioPluginAudioProcessor& p, juce::AudioProcessorValueTreeState& vts)
    : AudioProcessorEditor (&p), processorRef (p), paramRef(vts)
{
    juce::ignoreUnused (processorRef);

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
    try {
        auto id = processorRef.addDelay();
        mSpots.emplace_back(id);
        mSpots.back().setCenter(event.getMouseDownPosition());
        addAndMakeVisible(mSpots.back());
    }
    catch (Exception& ex) {
        juce::Logger::outputDebugString("Max Delays Reached");
    }
}

void AudioPluginAudioProcessorEditor::mouseDrag(const juce::MouseEvent& event)
{

}

void AudioPluginAudioProcessorEditor::mouseUp(const juce::MouseEvent& event)
{
}

