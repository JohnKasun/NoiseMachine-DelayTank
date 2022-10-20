#include "DelayTankView.h"

//==============================================================================
DelayTankView::DelayTankView()
{
    // Initalize spot
    for (auto& spot : spots) {
        addChildComponent(spot);
        spot.setRange(Spot::xAxis, 0, 10);
        spot.setRange(Spot::yAxis, 0, 30);
        spot.setRange(Spot::zAxis, 5, 20);
        spot.setValue(Spot::xAxis, 5);
        spot.setValue(Spot::yAxis, 5);
        spot.setValue(Spot::zAxis, 10);
    }

    addAndMakeVisible(gainSlider);
    gainSlider.setRange(5, 20);
    gainSlider.onValueChange = [this]() {
        if (selected) {
            selected->setValue(Spot::zAxis, gainSlider.getValue());
            juce::Logger::outputDebugString("Z : " + juce::String(selected->getValue(Spot::zAxis)));
        }
    };
    gainSlider.setSliderStyle(juce::Slider::Rotary);
    gainSlider.setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);
    gainSlider.setEnabled(false);

    setSize(400, 400);
}

DelayTankView::~DelayTankView()
{
}

//==============================================================================
void DelayTankView::paint(juce::Graphics& g)
{
    g.setColour(juce::Colours::white);
    g.fillAll();
    // Uses current spot values to set center position
    for (auto& spot : spots) {
        auto spotX = spot.getNormValue(Spot::xAxis) * getWidth();
        auto spotY = spot.getNormValue(Spot::yAxis) * getHeight();
        spot.setCentrePosition(spotX, spotY);
        spot.setSize(spot.getValue(Spot::zAxis), spot.getValue(Spot::zAxis));
    }
}

void DelayTankView::resized()
{
    gainSlider.setBounds(getLocalBounds().removeFromBottom(100).removeFromRight(100));
}

void DelayTankView::mouseDown(const juce::MouseEvent& event)
{
    if (auto spot = getSpotAt(event.mouseDownPosition)) {
        dragging = spot;
        selectSpot(*spot);
    }
    else {
        clearSelectedSpot();
    }
}

void DelayTankView::mouseDrag(const juce::MouseEvent& event)
{
    // Update value of spots 
    if (dragging) {
        setSpotPosition(*dragging, event.position);
    }
}

void DelayTankView::mouseUp(const juce::MouseEvent& event)
{
    dragging = nullptr;
}

void DelayTankView::mouseDoubleClick(const juce::MouseEvent& event)
{
    if (auto spot = getSpotAt(event.mouseDownPosition)) {
        spot->setVisible(false);
    }
    else {
        for (auto& spot : spots) {
            if (!spot.isVisible()) {
                setSpotPosition(spot, event.mouseDownPosition);
                spot.setVisible(true);
                break;
            }
        }
    }
}

Spot* DelayTankView::getSpotAt(juce::Point<float> point)
{
    for (auto& spot : spots) {
        if (spot.getBoundsInParent().contains(point.toInt()) && spot.isVisible())
            return &spot;
    }
    return nullptr;
}

void DelayTankView::setSpotPosition(Spot& spot, juce::Point<float> point)
{
    spot.setNormValue(Spot::xAxis, point.x / getWidth());
    spot.setNormValue(Spot::yAxis, point.y / getHeight());
    juce::Logger::outputDebugString("X : " + juce::String(spot.getValue(Spot::xAxis)));
    juce::Logger::outputDebugString("Y : " + juce::String(spot.getValue(Spot::yAxis)));
    repaint();
}

void DelayTankView::selectSpot(Spot& spot)
{
    clearSelectedSpot();
    selected = &spot;
    selected->setColor(juce::Colours::yellow);
    gainSlider.setEnabled(true);
    gainSlider.setValue(selected->getValue(Spot::Dimension::zAxis));
    repaint();
}

void DelayTankView::clearSelectedSpot()
{
    if (selected) {
        selected->setColor(juce::Colours::red);
        selected = nullptr;
        gainSlider.setValue(gainSlider.getMinimum(), juce::dontSendNotification);
        gainSlider.setEnabled(false);
        repaint();
    }
}
