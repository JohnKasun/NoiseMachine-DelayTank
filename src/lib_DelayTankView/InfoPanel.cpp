#include "InfoPanel.h"

void InfoPanel::paint(juce::Graphics& g) {
	g.fillAll(juce::Colours::white);
	g.setColour(juce::Colours::red);
	g.drawText(text, getLocalBounds(), juce::Justification::left);
}

void InfoPanel::setText(juce::String text) {
	this->text = text;
}