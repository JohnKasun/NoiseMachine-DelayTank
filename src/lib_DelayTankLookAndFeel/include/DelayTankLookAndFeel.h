#pragma once

#include <juce_gui_extra/juce_gui_extra.h>
#include <functional>

class Spot : public juce::Component
{
public:
	Spot(int id = 0, juce::Rectangle<int> bounds = {0,0,10,10});
	void setCenter(juce::Point<int> newCenter);
	juce::Point<int> getCenter() const;
	int getId() const;
	void paint(juce::Graphics& g) override;
	void resized() override;
	std::function<void()> onClick = {};
	std::function<void()> onDrag = {};
	bool operator==(const Spot& lhs);
private:
	void mouseDoubleClick(const juce::MouseEvent& event) override;
	void mouseDrag(const juce::MouseEvent& event) override;
	int mId;
	juce::Rectangle<int> mBounds;
};