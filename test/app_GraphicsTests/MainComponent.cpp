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
    spot.setSize(10, 10);
}

void MainComponent::mouseDown(const juce::MouseEvent& event)
{
    if (spot.getBoundsInParent().contains(event.mouseDownPosition.toInt()) && spot.isVisible()) {
        juce::Logger::outputDebugString("Hit");
        dragging = &spot;
    }
}

void MainComponent::mouseDrag(const juce::MouseEvent& event)
{
    // Update value of spots 
    if (dragging) {
        setSpotPosition(spot, event.position);
    }
}

void MainComponent::mouseUp(const juce::MouseEvent& event)
{
    dragging = nullptr;
}

void MainComponent::mouseDoubleClick(const juce::MouseEvent& event)
{
    if (spot.isVisible())
        spot.setVisible(false);
    else {
        spot.setVisible(true);
        setSpotPosition(spot, event.mouseDownPosition);
    }
}

void MainComponent::setSpotPosition(Spot& spot, juce::Point<float> point)
{
    spot.setNormValue(Spot::xAxis, point.x / getWidth());
    spot.setNormValue(Spot::yAxis, point.y / getHeight());
    juce::Logger::outputDebugString("X : " + juce::String(spot.getValue(Spot::xAxis)));
    juce::Logger::outputDebugString("Y : " + juce::String(spot.getValue(Spot::yAxis)));
    repaint();
}
