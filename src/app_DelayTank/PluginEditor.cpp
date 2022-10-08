#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
AudioPluginAudioProcessorEditor::AudioPluginAudioProcessorEditor (AudioPluginAudioProcessor& p, juce::AudioProcessorValueTreeState& vts)
    : AudioProcessorEditor (&p), processorRef (p), paramRef(vts)
{
    juce::ignoreUnused (processorRef);
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 300);

    startTimer(5);

    //On move, send processor id and values
    addAndMakeVisible(slider);
    auto paramRange = paramRef.getParameterRange("0d");
    slider.setRange(paramRange.start, paramRange.end);
    slider.onValueChange = [this]() {processorRef.requestParameterChange(0, slider.getValue(), 1.0f, 1.0f); };
}

AudioPluginAudioProcessorEditor::~AudioPluginAudioProcessorEditor()
{
    stopTimer();
}

//==============================================================================
void AudioPluginAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
    g.drawFittedText ("Hello World", getLocalBounds(), juce::Justification::centred, 1);
}

void AudioPluginAudioProcessorEditor::resized()
{
    slider.setBounds(getLocalBounds());
}

void AudioPluginAudioProcessorEditor::timerCallback()
{
    updateGraphics();
}

void AudioPluginAudioProcessorEditor::updateGraphics()
{
    slider.setValue(*paramRef.getRawParameterValue("0d"), juce::dontSendNotification);
}
