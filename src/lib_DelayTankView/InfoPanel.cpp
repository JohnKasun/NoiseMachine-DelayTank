#include "InfoPanel.h"

InfoPanel::InfoPanel() {
	for (auto& value : parameterValues)
		value = 0.0f;
}

void InfoPanel::setParameterValue(parameters param, float value) {
	parameterValues[param] = value;
}

void InfoPanel::paint(juce::Graphics& g) {
	g.fillAll(juce::Colours::white);
	g.setColour(juce::Colours::red);
	g.drawText(text, getLocalBounds(), juce::Justification::left);
}

void InfoPanel::setText(juce::String text) {
	this->text = text;
}