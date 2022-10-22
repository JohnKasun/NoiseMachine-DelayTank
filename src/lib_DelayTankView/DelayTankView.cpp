#include "DelayTankView.h"

//==============================================================================
DelayTankView::DelayTankView(int numSpots)
    : spots(numSpots)
{
    // Initalize spot
    for (auto& spot : spots) {
        addChildComponent(spot);
    }

    addAndMakeVisible(gainSlider);
    gainSlider.setRange(0, 1);
    gainSlider.onValueChange = [this]() {
        if (selected) {
            selected->setNormValue(Spot::zAxis, gainSlider.getValue());
            juce::Logger::outputDebugString("Z : " + juce::String(selected->getValue(Spot::zAxis)));
        }
    };
    gainSlider.setSliderStyle(juce::Slider::LinearVertical);
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
    //g.setColour(juce::Colours::white);
    //g.fillAll();
    // Uses current spot values to set center position
    for (auto& spot : spots) {
        auto spotX = spot.getNormValue(Spot::xAxis) * getWidth();
        auto spotY = spot.getNormValue(Spot::yAxis) * getHeight();
        auto spotZ = spot.getNormValue(Spot::zAxis) * getHeight() / 10.0f + getHeight() / 40.0f;
        spot.setCentrePosition(spotX, spotY);
        spot.setSize(spotZ, spotZ);
    }
}

void DelayTankView::resized()
{
    gainSlider.setBounds(getLocalBounds().removeFromBottom(100).removeFromRight(100));
}

void DelayTankView::mouseDown(const juce::MouseEvent& event)
{
    if (auto spot = getSpotAt(event.mouseDownPosition)) {
        auto diffClicks = event.eventTime - lastMouseClick;
        if (diffClicks.inMilliseconds() < juce::MouseEvent::getDoubleClickTimeout()) {
            resizing = spot;
        }
        else {
            dragging = spot;
        }
        selectSpot(*spot);
        lastMouseClick = event.eventTime;
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
    else if (resizing) {
        setSpotSize(*resizing, event);
    }
}

void DelayTankView::mouseUp(const juce::MouseEvent& event)
{
    dragging = nullptr;
    resizing = nullptr;
}

void DelayTankView::mouseDoubleClick(const juce::MouseEvent& event)
{
    if (!event.mouseWasDraggedSinceMouseDown()) {
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

void DelayTankView::setSpotSize(Spot& spot, const juce::MouseEvent& event)
{
    auto sensitivity = 20;
    auto yDiff = spot.getBounds().getCentreY() - event.position.y;
    auto yDiffNorm = yDiff / getHeight();
    auto newSize = spot.getNormValue(Spot::zAxis) + yDiffNorm / 20;
    spot.setNormValue(Spot::zAxis, yDiffNorm);
    juce::Logger::outputDebugString("Z : " + juce::String(spot.getValue(Spot::zAxis)));
    repaint();
}

void DelayTankView::selectSpot(Spot& spot)
{
    clearSelectedSpot();
    selected = &spot;
    selected->setColor(juce::Colours::yellow);
    gainSlider.setEnabled(true);
    gainSlider.setValue(selected->getNormValue(Spot::Dimension::zAxis));
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
