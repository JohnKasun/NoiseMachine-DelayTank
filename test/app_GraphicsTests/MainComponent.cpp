#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
{
    // Initalize spot
    addAndMakeVisible(spot);
    spot.setRange(Spot::xAxis, 0, 10);
    spot.setRange(Spot::yAxis, 0, 30);
    spot.setRange(Spot::zAxis, 5, 20);
    spot.setValue(Spot::xAxis, 5);
    spot.setValue(Spot::yAxis, 5);
    spot.setValue(Spot::zAxis, 10);
    
    addAndMakeVisible(gainSlider);
    gainSlider.setRange(5, 20);
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
    spot.setSize(spot.getValue(Spot::zAxis), spot.getValue(Spot::zAxis));
}

void MainComponent::resized()
{
    gainSlider.setBounds(getLocalBounds().removeFromBottom(100).removeFromRight(100));
}

void MainComponent::mouseDown(const juce::MouseEvent& event)
{
    if (spot.getBoundsInParent().contains(event.mouseDownPosition.toInt()) && spot.isVisible()) {
        dragging = &spot;
        selectSpot(spot);
    }
    else {
        clearSelectedSpot();
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

void MainComponent::selectSpot(Spot& spot)
{
    clearSelectedSpot();
    selected = &spot;
    selected->setColor(juce::Colours::yellow);
    gainSlider.setEnabled(true);
    gainSlider.setValue(selected->getValue(Spot::Dimension::zAxis));
    repaint();
}

void MainComponent::clearSelectedSpot()
{
    if (selected) {
        selected->setColor(juce::Colours::red);
        selected = nullptr;
        gainSlider.setValue(gainSlider.getMinimum(), juce::dontSendNotification);
        gainSlider.setEnabled(false);
        repaint();
    }
}
