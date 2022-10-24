#pragma once

#include "Spot.h"

class DelayTankView : public juce::Component 
{
    friend class DelayTankViewAttachment;
public:
    //==============================================================================
    DelayTankView(int numSpots = 10);
    ~DelayTankView() override;

    //==============================================================================
    void paint(juce::Graphics&) override;
    void resized() override;

    void mouseDown(const juce::MouseEvent& event) override;
    void mouseDrag(const juce::MouseEvent& event) override;
    void mouseUp(const juce::MouseEvent& event) override;
    void mouseDoubleClick(const juce::MouseEvent& event) override;

private:

    std::vector<Spot> spots;
    Spot* dragging = nullptr;
    Spot* resizing = nullptr;
    Spot* selected = nullptr;

    juce::Slider gainSlider;

    Spot* getSpotAt(juce::Point<float> point);
    void setSpotPosition(Spot& spot, juce::Point<float> point);
    void setSpotSize(Spot& spot, const juce::MouseEvent& event);
    void selectSpot(Spot& spot);
    void clearSelectedSpot();

    juce::Time lastMouseClick;
    float resizeStart = 0.0f;
};