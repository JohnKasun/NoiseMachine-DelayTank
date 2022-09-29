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

void DelayTankEngine::setDelay(int index, float delayInSeconds)
{
	mDelays.at(index)->setDelay(delayInSeconds);
}

void DelayTankEngine::setGain(int index, float gain)
{
	mDelays.at(index)->setGain(gain);
}

void DelayTankEngine::setPan(int index, int pan)
{
	mDelays.at(index)->setPan(pan);
}

std::pair<float, float> DelayTankEngine::process(float input)
{
	auto outputSumL = 0.0f;
	auto outputSumR = 0.0f;
	for (int i = 0; i < mNumActiveDelays; i++) {
		auto output = mDelays.at(i)->process(input);
		outputSumL += output.first;
		outputSumR += output.second;
	}
	return std::make_pair(outputSumL, outputSumR);
}

float DelayTankEngine::getDelay(int index) const
{
	return mDelays.at(index)->getDelay();
}

float DelayTankEngine::getGain(int index) const
{
	return mDelays.at(index)->getGain();
}

int DelayTankEngine::getPan(int index) const
{
	return mDelays.at(index)->getPan();
}
