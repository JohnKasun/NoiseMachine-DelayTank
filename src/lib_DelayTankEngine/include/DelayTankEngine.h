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
	enum Parameters {
		DelayTime,
		Gain,
		Pan
	};
	DelayTankEngine(float maxDelayInSeconds, int maxNumDelays, float sampleRate);
	~DelayTankEngine();

	int addDelay();
	void removeDelay(int id);

	void setParameter(int id, Parameters param, float value);
	float getParameter(int id, Parameters param) const;
	std::pair<float, float> process(float input);

private:
	std::vector<std::unique_ptr<Delay>> mDelays;
	std::unordered_set<int> mActiveDelays;
	std::priority_queue<int, std::vector<int>, std::greater<int>> mIdBackLog;

	bool isValidId(int id) const;
};