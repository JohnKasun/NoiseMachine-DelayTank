#pragma once

#include <juce_gui_extra/juce_gui_extra.h>

// Make this a map?
class InfoPanel : public juce::Component
{
public:
	enum parameters{
		Delaytime,
		Pan,
		Gain,
		numParameters
	};
	InfoPanel();
	~InfoPanel() = default;

	void paint(juce::Graphics& g) override;

	void setParameterValue(parameters param, float value);
private:
	float parameterValues[numParameters]{};
};