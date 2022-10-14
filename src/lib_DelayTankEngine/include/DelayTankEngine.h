#pragma once

#include <vector>
#include <memory>
#include <set>


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

	void enableDelay(int id);
	void disableDelay(int id);

	std::set<int> getActiveDelayIds() const;
	std::set<int> getInactiveDelayIds() const;
	void setParameter(int id, Parameters param, float value);
	float getParameter(int id, Parameters param) const;
	std::pair<float, float> process(float input);

private:
	std::vector<std::unique_ptr<Delay>> mDelays;
	std::set<int> mActiveDelayIds;
	std::set<int> mInactiveDelayIds;

	void checkValidId(int id) const;
};