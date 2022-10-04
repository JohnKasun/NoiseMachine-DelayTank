#include "DelayTankEngine.h"

DelayTankEngine::DelayTankEngine(float maxDelayInSeconds, int maxNumDelays, float sampleRate)
{
	for (auto i = 0; i < maxNumDelays; i++) {
		mDelays.emplace_back(new Delay(maxDelayInSeconds, sampleRate));
		mIdBackLog.push(i);
	}
}

DelayTankEngine::~DelayTankEngine()
{
	mDelays.clear();
}

int DelayTankEngine::addDelay()
{
	if (mIdBackLog.empty()) throw Exception("Max Delays Reached");
	auto id = mIdBackLog.top();
	mIdBackLog.pop();
	mActiveDelays.insert(id);
	return id;
}

void DelayTankEngine::removeDelay(int id)
{
	if (!isValidId(id)) throw Exception("Invalid Id");
	mActiveDelays.erase(id);
	mIdBackLog.push(id);
	mDelays.at(id)->resetParameters();
}

void DelayTankEngine::setParameter(int id, Parameters param, float value)
{
	if (!isValidId(id)) throw Exception("Invalid Id");
	switch (param) {
	case DelayTime:
		mDelays.at(id)->setDelay(value);
		break;
	case Gain:
		mDelays.at(id)->setGain(value);
		break;
	default:
		mDelays.at(id)->setPan(value);
	}
}

float DelayTankEngine::getParameter(int id, Parameters param) const
{
	if (!isValidId(id)) throw Exception("Invalid Id");
	switch (param) {
	case DelayTime:
		return mDelays.at(id)->getDelay();
	case Gain:
		return mDelays.at(id)->getGain();
	default:
		return mDelays.at(id)->getPan();
	}
}

std::pair<float, float> DelayTankEngine::process(float input)
{
	auto outputSumL = 0.0f;
	auto outputSumR = 0.0f;
	for (auto& i : mActiveDelays) {
		auto output = mDelays.at(i)->process(input);
		outputSumL += output.first;
		outputSumR += output.second;
	}
	return std::make_pair(outputSumL, outputSumR);
}

bool DelayTankEngine::isValidId(int id) const
{
	auto found = mActiveDelays.find(id);
	if (found != mActiveDelays.end())
		return true;
	return false;
}
