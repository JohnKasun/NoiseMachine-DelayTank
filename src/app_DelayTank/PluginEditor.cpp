#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
AudioPluginAudioProcessorEditor::AudioPluginAudioProcessorEditor (AudioPluginAudioProcessor& p, juce::AudioProcessorValueTreeState& vts)
    : AudioProcessorEditor (&p), processorRef (p), paramRef(vts)
{
    juce::ignoreUnused (processorRef);

    addAndMakeVisible(spot);
    spotAttachment.reset(new SpotAttachment(paramRef, "0p", "0d", "0g", "0e", spot));

    addAndMakeVisible(gainSlider);
    gainSlider.setRange(paramRef.getParameterRange("0g").start, paramRef.getParameterRange("0g").end);
    gainSlider.onValueChange = [this]() {
        if (selected) {
            selected->setValue(Spot::zAxis, gainSlider.getValue());
            juce::Logger::outputDebugString("Z : " + juce::String(spot.getValue(Spot::zAxis)));
        }
    };
    gainSlider.setSliderStyle(juce::Slider::Rotary);
    gainSlider.setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);
    gainSlider.setEnabled(false);

    setSize(400, 400);
}

AudioPluginAudioProcessorEditor::~AudioPluginAudioProcessorEditor()
{
}

//==============================================================================
void AudioPluginAudioProcessorEditor::paint(juce::Graphics& g)
{
    // Uses current spot values to set center position
    auto spotX = spot.getNormValue(Spot::xAxis) * getWidth();
    auto spotY = spot.getNormValue(Spot::yAxis) * getHeight();
    spot.setCentrePosition(spotX, spotY);
    spot.setSize(10 * spot.getValue(Spot::zAxis) + 10, 10 * spot.getValue(Spot::zAxis) + 10);
}

void AudioPluginAudioProcessorEditor::resized()
{
    gainSlider.setBounds(getLocalBounds().removeFromBottom(100).removeFromRight(100));
}

void AudioPluginAudioProcessorEditor::mouseDown(const juce::MouseEvent& event)
{
    if (spot.getBoundsInParent().contains(event.mouseDownPosition.toInt()) && spot.isVisible()) {
        dragging = &spot;
        selectSpot(spot);
    }
    else {
        clearSelectedSpot();
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

void AudioPluginAudioProcessorEditor::selectSpot(Spot& spot)
{
    clearSelectedSpot();
    selected = &spot;
    selected->setColor(juce::Colours::yellow);
    gainSlider.setEnabled(true);
    gainSlider.setValue(selected->getValue(Spot::Dimension::zAxis));
    repaint();
}

void AudioPluginAudioProcessorEditor::clearSelectedSpot()
{
    if (selected) {
        selected->setColor(juce::Colours::red);
        selected = nullptr;
        gainSlider.setValue(gainSlider.getMinimum(), juce::dontSendNotification);
        gainSlider.setEnabled(false);
        repaint();
    }
}


