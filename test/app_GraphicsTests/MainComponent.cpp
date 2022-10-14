#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
{
    addAndMakeVisible(spot);
    spot.setValueRangeX(juce::NormalisableRange<float>(0, 100));
    spot.setValueRangeY(juce::NormalisableRange<float>(0, 50));

    setInterceptsMouseClicks(true, false);
    setSize(400, 400);

    spot.setValueX(100);
    spot.setValueY(25);
}

MainComponent::~MainComponent()
{
}

//==============================================================================
void MainComponent::paint(juce::Graphics& g)
{

}

void MainComponent::resized()
{
    spot.resized();
}

void MainComponent::mouseDrag(const juce::MouseEvent& event)
{
    spot.setCenter(event.getPosition());
    juce::Logger::outputDebugString("x: " + juce::String(spot.getValueX()));
    juce::Logger::outputDebugString("y: " + juce::String(spot.getValueY()));
}
