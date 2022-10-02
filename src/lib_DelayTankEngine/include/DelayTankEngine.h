#pragma once

#include <vector>
#include <memory>

#include "Exception.h"
#include "Exception.h"
#include "Delay.h"

class DelayTankEngine {
public:
	DelayTankEngine(float maxDelayInSeconds, int maxNumDelays, float sampleRate);
	~DelayTankEngine();

	void setDelay(int index, float delayinSeconds);
	void setGain(int index, float gain);
	void setPan(int index, int pan);
	std::pair<float, float> process(float input);

	float getDelay(int index) const;
	float getGain(int index) const;
	int getPan(int index) const;
private:
	std::vector<std::unique_ptr<Delay>> mDelays;
	int mNumActiveDelays = 0;
};