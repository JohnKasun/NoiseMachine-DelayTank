#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
{
    addAndMakeVisible(spot);

    setSize(400, 400);
}

MainComponent::~MainComponent()
{
}

//==============================================================================
void MainComponent::paint(juce::Graphics& g)
{

}

void MainComponent::resized()
{
    juce::Point<float> center(getX() + getWidth() / 2, getY() + getHeight() / 2);
    spot.setCenter(center);
    spot.setBounds(getLocalBounds());
}
