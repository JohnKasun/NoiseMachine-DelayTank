#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
AudioPluginAudioProcessorEditor::AudioPluginAudioProcessorEditor (AudioPluginAudioProcessor& p, juce::AudioProcessorValueTreeState& vts)
    : AudioProcessorEditor (&p), processorRef (p), paramRef(vts)
{
    juce::ignoreUnused (processorRef);

    addAndMakeVisible(spot);
    spotAttachment.reset(new SpotAttachment(paramRef, "0p", "0d", "0e", spot));

    setSize(400, 300);
}

AudioPluginAudioProcessorEditor::~AudioPluginAudioProcessorEditor()
{
}

void AudioPluginAudioProcessorEditor::paint(juce::Graphics& g)
{
    // Uses current spot values to set center position
    auto spotX = spot.getNormValue(Spot::xAxis) * getWidth();
    auto spotY = spot.getNormValue(Spot::yAxis) * getHeight();
    spot.setCentrePosition(spotX, spotY);
}

void AudioPluginAudioProcessorEditor::resized()
{
    spot.setSize(10, 10);
}

void AudioPluginAudioProcessorEditor::mouseDown(const juce::MouseEvent& event)
{
    if (spot.getBoundsInParent().contains(event.mouseDownPosition.toInt()) && spot.isVisible()) {
        juce::Logger::outputDebugString("Hit");
        dragging = &spot;
    }
}

void AudioPluginAudioProcessorEditor::mouseDrag(const juce::MouseEvent& event)
{
    // Update value of spots 
    if (dragging) {
        setSpotPosition(spot, event.position);
    }
}

void AudioPluginAudioProcessorEditor::mouseUp(const juce::MouseEvent& event)
{
    dragging = nullptr;
}

void AudioPluginAudioProcessorEditor::mouseDoubleClick(const juce::MouseEvent& event)
{
    if (spot.isVisible())
        spot.setVisible(false);
    else {
        spot.setVisible(true);
        setSpotPosition(spot, event.mouseDownPosition);
    }
}

void AudioPluginAudioProcessorEditor::setSpotPosition(Spot& spot, juce::Point<float> point)
{
    spot.setNormValue(Spot::xAxis, point.x / getWidth());
    spot.setNormValue(Spot::yAxis, point.y / getHeight());
    juce::Logger::outputDebugString("X : " + juce::String(spot.getValue(Spot::xAxis)));
    juce::Logger::outputDebugString("Y : " + juce::String(spot.getValue(Spot::yAxis)));
    repaint();
}


