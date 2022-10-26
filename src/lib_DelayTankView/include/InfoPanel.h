#pragma once

#include <juce_gui_extra/juce_gui_extra.h>

class InfoPanel : public juce::Component
{
public:
	InfoPanel() = default;
	~InfoPanel() = default;

	void paint(juce::Graphics& g) override;

	void setText(juce::String);
private:
	juce::String text;
};