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

bool DelayTankEngine::addDelay(int id)
{
	return false;
}

bool DelayTankEngine::removeDelay(int id)
{
	return false;
}

void DelayTankEngine::setDelay(int id, float delayInSeconds)
{
	mDelays.at(id)->setDelay(delayInSeconds);
}

void DelayTankEngine::setGain(int id, float gain)
{
	mDelays.at(id)->setGain(gain);
}

void DelayTankEngine::setPan(int id, int pan)
{
	mDelays.at(id)->setPan(pan);
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

float DelayTankEngine::getDelay(int id) const
{
	return mDelays.at(id)->getDelay();
}

float DelayTankEngine::getGain(int id) const
{
	return mDelays.at(id)->getGain();
}

int DelayTankEngine::getPan(int id) const
{
	return mDelays.at(id)->getPan();
}
