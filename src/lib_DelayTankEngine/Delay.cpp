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
	writeDelay(input);
	auto output = mGain * readDelay();
	auto outputL = (1.0f - mPan) * output;
	auto outputR = mPan * output;
	return std::pair<float, float>(outputL, outputR);
}

void Delay::resetParameters()
{
	while (mDelayLine->getNumValuesInBuffer() != 0) {
		mDelayLine->getPostInc();
	}
	setDelay(0.0f);
	setPan(0.0f);
	setGain(1.0f);
}

float Delay::getDelay() const
{
	return mDelayLine->getNumValuesInBuffer() / mSampleRate;
}

float Delay::getGain() const
{
	return mGain;
}

float Delay::getPan() const
{
	return (mPan * 200.0f) - 100.0f;
}

float Delay::readDelay()
{
	auto currWriteIdx = mDelayLine->getWriteIdx();
	mDelayLine->setWriteIdx(mDelayLine->getReadIdx());
	auto output = mDelayLine->getPostInc();
	mDelayLine->put(0.0f);
	mDelayLine->setWriteIdx(currWriteIdx);
	return output;
}

void Delay::writeDelay(float input)
{
	auto currReadIdx = mDelayLine->getReadIdx();
	mDelayLine->setReadIdx(mDelayLine->getWriteIdx());
	mDelayLine->putPostInc(mDelayLine->get() + input);
	mDelayLine->setReadIdx(currReadIdx);
}
