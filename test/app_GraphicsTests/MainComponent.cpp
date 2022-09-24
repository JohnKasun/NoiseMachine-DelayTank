#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
{
    setSize(200, 200);
}

MainComponent::~MainComponent()
{
}

//==============================================================================
void MainComponent::paint(juce::Graphics& g)
{
    g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));
}

void MainComponent::resized()
{

}
