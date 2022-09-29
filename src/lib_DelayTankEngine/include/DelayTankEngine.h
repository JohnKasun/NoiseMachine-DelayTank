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
private:
	std::vector<std::unique_ptr<Delay>> mDelays;
};