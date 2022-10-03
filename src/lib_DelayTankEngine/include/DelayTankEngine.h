#pragma once

#include <vector>
#include <memory>
#include <unordered_set>
#include <queue>
#include <functional>

#include "Exception.h"
#include "Exception.h"
#include "Delay.h"

class DelayTankEngine {
public:
	DelayTankEngine(float maxDelayInSeconds, int maxNumDelays, float sampleRate);
	~DelayTankEngine();

	int addDelay();
	bool removeDelay(int id);

	void setDelay(int id, float delayinSeconds);
	void setGain(int id, float gain);
	void setPan(int id, int pan);
	std::pair<float, float> process(float input);

	float getDelay(int id) const;
	float getGain(int id) const;
	int getPan(int id) const;
private:
	std::vector<std::unique_ptr<Delay>> mDelays;
	std::unordered_set<int> mActiveDelays;
	std::priority_queue<int, std::vector<int>, std::greater<int>> mIdBackLog;
};