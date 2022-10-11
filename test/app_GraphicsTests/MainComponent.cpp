#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
{
    addAndMakeVisible(spot);

    setSize(400, 400);

    juce::Point<float> center(getX() + getWidth() / 2, getY() + getHeight() / 2);
    spot.setCenter(center);
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
    spot.setBounds(getLocalBounds());
}
