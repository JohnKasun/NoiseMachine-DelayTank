#include "DelayTankEngine.h"

DelayTankEngine::DelayTankEngine(float maxDelayInSeconds, int maxNumDelays, float sampleRate)
{
	for (auto i = 0; i < maxNumDelays; i++) {
		mDelayQueue.emplace(new Delay(maxDelayInSeconds, sampleRate));
	}
}

DelayTankEngine::~DelayTankEngine()
{
	while (!mDelayQueue.empty())
		mDelayQueue.pop();
}

bool DelayTankEngine::addDelay(int id)
{
	// Max of 10 delays
	if (mDelayQueue.empty()) {
		return false;
	}
	
	// Return if already exists
	auto it = mDelayMap.find(id);
	if (it != mDelayMap.end())
		return false;

	auto delay = mDelayQueue.front();
	delay->resetParameters();
	mDelayMap[id] = delay;
	mDelayQueue.pop();
	return true;
}

bool DelayTankEngine::removeDelay(int id)
{
	auto it = mDelayMap.find(id);
	if (it != mDelayMap.end()) {
		mDelayQueue.push(it->second);
		mDelayMap.erase(it);
		return true;
	}
	return false;
}

void DelayTankEngine::setParameter(int id, Parameters param, float value)
{
	if (!isValidId(id)) throw Exception("Invalid Id");
	switch (param) {
	case Parameters::DelayTime:
		mDelayMap.at(id)->setDelay(value);
		break;
	case Parameters::Gain:
		mDelayMap.at(id)->setGain(value);
		break;
	default:
		mDelayMap.at(id)->setPan(value);
	}
}

float DelayTankEngine::getParameter(int id, Parameters param) const
{
	if (!isValidId(id)) throw Exception("Invalid Id");
	switch (param) {
	case Parameters::DelayTime:
		return mDelayMap.at(id)->getDelay();
	case Parameters::Gain:
		return mDelayMap.at(id)->getGain();
	default:
		return mDelayMap.at(id)->getPan();
	}
}

std::pair<float, float> DelayTankEngine::process(float input)
{
	auto outputSumL = 0.0f;
	auto outputSumR = 0.0f;
	for (auto& [id, delay] : mDelayMap) {
		auto output = delay->process(input);
		outputSumL += output.first;
		outputSumR += output.second;
	}
	return std::make_pair(outputSumL, outputSumR);
}

bool DelayTankEngine::isValidId(int id) const
{
	auto found = mDelayMap.find(id);
	if (found != mDelayMap.end())
		return true;
	return false;
}
