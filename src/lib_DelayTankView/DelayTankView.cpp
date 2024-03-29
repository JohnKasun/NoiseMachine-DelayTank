#include "DelayTankView.h"

//==============================================================================
DelayTankView::DelayTankView(int numSpots)
    : spots(numSpots)
{
    // Initalize spot
    for (auto& spot : spots) {
        addChildComponent(spot);
    }
    setSize(400, 400);
}

DelayTankView::~DelayTankView()
{
}

//==============================================================================
void DelayTankView::paint(juce::Graphics& g)
{
    g.setColour(juce::Colours::black);
    g.fillAll();
    for (auto& spot : spots) {
        auto spotX = spot.getNormValue(Spot::xAxis) * getWidth();
        auto spotY = (1.0f - spot.getNormValue(Spot::yAxis)) * getHeight();
        auto spotZ = spot.getNormValue(Spot::zAxis) * getHeight() / 10.0f + getHeight() / 40.0f;
        spot.setCentrePosition(spotX, spotY);
        spot.setSize(spotZ, spotZ);
    }
}

void DelayTankView::resized()
{

}

void DelayTankView::mouseDown(const juce::MouseEvent& event)
{
    if (auto spot = getSpotAt(event.mouseDownPosition)) {
        auto diffClicks = event.eventTime - lastMouseClick;
        if (diffClicks.inMilliseconds() < juce::MouseEvent::getDoubleClickTimeout()) {
            resizing = spot;
            resizeStart = spot->getNormValue(Spot::zAxis);
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
    onSpotUpdate(selected);
}

void DelayTankView::mouseDrag(const juce::MouseEvent& event)
{
    if (dragging) {
        setSpotPosition(*dragging, event.position);
    }
    else if (resizing) {
        setSpotSize(*resizing, event);
    }
    onSpotUpdate(selected);
}

void DelayTankView::mouseUp(const juce::MouseEvent& event)
{
    dragging = nullptr;
    resizing = nullptr;
    resizeStart = 0.0f;
    onSpotUpdate(selected);
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
    spot.setNormValue(Spot::yAxis, 1.0f - (point.y / getHeight()));
    repaint();
}

void DelayTankView::setSpotSize(Spot& spot, const juce::MouseEvent& event)
{
    auto yDiffNorm = static_cast<float>(event.getDistanceFromDragStartY()) / getHeight();
    auto newSizeNorm = resizeStart - yDiffNorm;
    spot.setNormValue(Spot::zAxis, newSizeNorm);
    repaint();
}

void DelayTankView::selectSpot(Spot& spot)
{
    clearSelectedSpot();
    selected = &spot;
    selected->setColor(juce::Colours::yellow);
    repaint();
}

void DelayTankView::clearSelectedSpot()
{
    if (selected) {
        selected->setColor(juce::Colours::red);
        selected = nullptr;
        repaint();
    }
}
