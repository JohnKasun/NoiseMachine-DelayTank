#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
{
    addAndMakeVisible(delayTank);
    setSize(400, 400);
}

MainComponent::~MainComponent()
{
}

//==============================================================================
void MainComponent::paint(juce::Graphics& g)
{
    // Uses current spot values to set center position
}

void MainComponent::resized()
{
    delayTank.setBounds(getBounds().reduced(50));
}

