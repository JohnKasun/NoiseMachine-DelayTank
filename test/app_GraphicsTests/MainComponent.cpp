#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
{
    // Initalize spot
    addAndMakeVisible(spot);
    spot.setRange(Spot::xAxis, 0, 10);
    spot.setRange(Spot::yAxis, 0, 30);
    spot.setValue(Spot::xAxis, 5);
    spot.setValue(Spot::yAxis, 5);

    setInterceptsMouseClicks(true, false);

    setSize(400, 400);
}

MainComponent::~MainComponent()
{
}

//==============================================================================
void MainComponent::paint(juce::Graphics& g)
{
    // Uses current spot values to set center position
    auto spotX = spot.getNormValue(Spot::xAxis) * getWidth();
    auto spotY = spot.getNormValue(Spot::yAxis) * getHeight();
    spot.setCentrePosition(spotX, spotY);
}

void MainComponent::resized()
{
    // Set initialize size of spots
    spot.setBounds(0, 0, 10, 10);
}

void MainComponent::mouseDown(const juce::MouseEvent& event)
{

}

void MainComponent::mouseDrag(const juce::MouseEvent& event)
{
    // Update value of spots 
    spot.setNormValue(Spot::xAxis, event.position.x / getWidth());
    spot.setNormValue(Spot::yAxis, event.position.y / getHeight());
    juce::Logger::outputDebugString("X : " + juce::String(spot.getValue(Spot::xAxis)));
    juce::Logger::outputDebugString("Y : " + juce::String(spot.getValue(Spot::yAxis)));
    repaint();
}
