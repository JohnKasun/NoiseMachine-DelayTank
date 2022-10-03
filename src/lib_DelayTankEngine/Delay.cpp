#include "Delay.h"

Delay::Delay(float maxDelayInSeconds, float sampleRate)
{
	mSampleRate = sampleRate;
	mDelayLine.reset(new CRingBuffer<float>(1 + CUtil::float2int<int>(maxDelayInSeconds * mSampleRate)));
}

Delay::~Delay()
{
	mDelayLine.reset();
}

void Delay::setDelay(float delayInSeconds)
{
	int delayInSamples = CUtil::float2int<int>(delayInSeconds * mSampleRate);
	if (delayInSamples < 0.0f || delayInSamples > mDelayLine->getLength() - 1) 
		throw Exception("Invalid Delay Parameter");
	mDelayLine->setWriteIdx(mDelayLine->getReadIdx() + delayInSamples);
}

void Delay::setGain(float gain)
{
	if (gain < 0.0f || gain > 1.0f) throw Exception("Invalid Gain Parameter");
	mGain = gain;
}

void Delay::setPan(float pan)
{
	if (pan < -100.0f || pan > 100.0f) throw Exception("Invalid Pan Parameter");
	mPan = (pan + 100.0f) / 200.0f;
}

std::pair<float, float> Delay::process(float input)
{
	auto currReadIdx = mDelayLine->getReadIdx();
	mDelayLine->setReadIdx(mDelayLine->getWriteIdx());
	mDelayLine->putPostInc(mDelayLine->get() + input);
	mDelayLine->setReadIdx(currReadIdx);

	auto output = mGain * mDelayLine->getPostInc();
	auto outputL = (1.0f - mPan) * output;
	auto outputR = mPan * output;
	return std::pair<float, float>(outputL, outputR);
}

float Delay::getDelay() const
{
	return mDelayLine->getNumValuesInBuffer() / mSampleRate;
}

float Delay::getGain() const
{
	return mGain;
}

int Delay::getPan() const
{
	return (mPan * 200.0f) - 100.0f;
}