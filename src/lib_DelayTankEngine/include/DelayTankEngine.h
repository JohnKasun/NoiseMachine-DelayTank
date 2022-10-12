#pragma once

#include <vector>
#include <memory>
#include <unordered_set>
#include <queue>
#include <functional>
#include <map>

#include "Exception.h"
#include "Delay.h"

class DelayTankEngine {
public:
	enum class Parameters {
		DelayTime,
		Gain,
		Pan
	};
	DelayTankEngine(float maxDelayInSeconds, int maxNumDelays, float sampleRate);
	~DelayTankEngine();

	bool addDelay(int id);
	bool removeDelay(int id);

	void setParameter(int id, Parameters param, float value);
	float getParameter(int id, Parameters param) const;
	std::pair<float, float> process(float input);

private:
	std::queue<std::shared_ptr<Delay>> mDelayQueue;
	std::map<int, std::shared_ptr<Delay>> mDelayMap;

	bool isValidId(int id) const;
};