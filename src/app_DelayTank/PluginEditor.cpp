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
    static auto id = 0;
    auto result = processorRef.addDelay(id);
    if (result) {
        createSpot(id, event.getMouseDownPosition());
        id++;
    }
    
}

void AudioPluginAudioProcessorEditor::createSpot(int id, juce::Point<int> location)
{
    mSpots.emplace_back(id);
    auto& spot = mSpots.back();
    spot.setCenter(location);
    spot.onClick = [this, &spot]() {
        processorRef.removeDelay(spot.getId());
        removeChildComponent(&spot);
        auto it = std::find(mSpots.begin(), mSpots.end(), spot);
        mSpots.erase(it);
    };
    spot.onDrag = [this, &spot, &location]() {
        auto xNorm = spot.getCenter().x / getWidth();
        auto yNorm = spot.getCenter().y / getHeight();
        processorRef.setParam(spot.getId(), DelayTankEngine::Parameters::DelayTime, yNorm);
        processorRef.setParam(spot.getId(), DelayTankEngine::Parameters::Pan, xNorm);
        processorRef.setParam(spot.getId(), DelayTankEngine::Parameters::Gain, 1.0f);
    };
    addAndMakeVisible(spot);
}
