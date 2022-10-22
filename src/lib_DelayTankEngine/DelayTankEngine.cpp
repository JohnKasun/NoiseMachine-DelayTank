#include "DelayTankEngine.h"

DelayTankEngine::DelayTankEngine(float maxDelayInSeconds, int maxNumDelays, float sampleRate)
{
	for (auto i = 0; i < maxNumDelays; i++) {
		mDelays.emplace_back(new Delay(maxDelayInSeconds, sampleRate));
	}
}

DelayTankEngine::~DelayTankEngine()
{
	mDelays.clear();
}

void DelayTankEngine::enableDelay(int id)
{
	checkValidId(id);

	mInactiveDelayIds.erase(id);
	mActiveDelayIds.insert(id);
}

void DelayTankEngine::disableDelay(int id)
{
	checkValidId(id);

	mActiveDelayIds.erase(id);
	mInactiveDelayIds.insert(id);
	mDelays.at(id)->resetParameters();
}

std::set<int> DelayTankEngine::getActiveDelayIds() const
{
	return mActiveDelayIds;
}

std::set<int> DelayTankEngine::getInactiveDelayIds() const
{
	return mInactiveDelayIds;
}

void DelayTankEngine::setParameter(int id, Parameters param, float value)
{
	checkValidId(id);

	switch (param) {
	case Parameters::DelayTime:
		mDelays.at(id)->setDelay(value);
		break;
	case Parameters::Gain:
		mDelays.at(id)->setGain(value);
		break;
	default:
		mDelays.at(id)->setPan(value);
	}
}

float DelayTankEngine::getParameter(int id, Parameters param) const
{
	checkValidId(id);

	switch (param) {
	case Parameters::DelayTime:
		return mDelays.at(id)->getDelay();
	case Parameters::Gain:
		return mDelays.at(id)->getGain();
	default:
		return mDelays.at(id)->getPan();
	}
}

std::pair<float, float> DelayTankEngine::process(float input)
{
	auto outputSumL = 0.0f;
	auto outputSumR = 0.0f;
	for (const auto& id : mActiveDelayIds) {
		auto output = mDelays.at(id)->process(input);
		outputSumL += output.first;
		outputSumR += output.second;
	}
	return std::make_pair(outputSumL, outputSumR);
}

void DelayTankEngine::checkValidId(int id) const
{
	if (id < 0 || id >= mDelays.size())
		throw Exception("Invalid Id");
}
