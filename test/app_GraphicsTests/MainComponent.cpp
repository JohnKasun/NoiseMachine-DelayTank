#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
{
    setSize(400, 400);
    addMouseListener(this, true);
}

MainComponent::~MainComponent()
{
    removeMouseListener(this);
}

//==============================================================================
void MainComponent::paint(juce::Graphics& g)
{

}

void MainComponent::resized()
{
    for (auto& spot : mSpots)
        spot.setBounds(getLocalBounds());
}

void MainComponent::mouseDown(const juce::MouseEvent& event)
{
    mSpots.emplace_back(0, event.mouseDownPosition);
    addAndMakeVisible(mSpots.back());
    mSpots.back().setBounds(getLocalBounds());
}
