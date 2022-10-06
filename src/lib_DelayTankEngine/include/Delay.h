#pragma once

#include <memory>

#include "Util.h"
#include "RingBuffer.h"
#include "Exception.h"

class Delay {
public:
	Delay(float maxDelayInSeconds, float sampleRate);
	~Delay();

	void setDelay(float delayInSeconds);
	void setGain(float gain);
	void setPan(float pan);
	std::pair<float, float> process(float input);
	void resetParameters();

	float getDelay() const;
	float getGain() const;
	float getPan() const;
private:
	std::unique_ptr<CRingBuffer<float>> mDelayLine;

	float mPan = 0.5f;
	float mGain = 1.0f;
	float mSampleRate = 44100.0f;

	float readDelay();
	void writeDelay(float input);
};