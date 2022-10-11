#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
{
    setSize(400, 400);
    addMouseListener(this, false);
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
    for (auto& spot : mSpots) {
        spot.resized();
    }
}

void MainComponent::mouseDown(const juce::MouseEvent& event)
{
    mSpots.emplace_back(0, juce::Rectangle<int>(event.x - 5, event.y - 5, 10, 10));
    addAndMakeVisible(mSpots.back());
}
