#include <gtest/gtest.h>
#include "Delay.h"
#include "GTestUtil.h"

class DelayTestSuite: public ::testing::Test
{
protected:
	void SetUp() override {
		mDelay.reset(new Delay(10, mSampleRate));
	}
	void TearDown() override {

	}
	std::unique_ptr<Delay> mDelay;
	float mSampleRate = 44100.0f;
};

TEST_F(DelayTestSuite, ParameterBounds) {
	EXPECT_ANY_THROW(mDelay->setDelay(11));
	EXPECT_ANY_THROW(mDelay->setDelay(-1));
	EXPECT_NO_THROW(mDelay->setDelay(10));
	EXPECT_NO_THROW(mDelay->setDelay(0));

	EXPECT_ANY_THROW(mDelay->setGain(-1));
	EXPECT_ANY_THROW(mDelay->setGain(2));
	EXPECT_NO_THROW(mDelay->setGain(0));
	EXPECT_NO_THROW(mDelay->setGain(1));

	EXPECT_ANY_THROW(mDelay->setPan(-101));
	EXPECT_ANY_THROW(mDelay->setPan(101));
	EXPECT_NO_THROW(mDelay->setPan(100));
	EXPECT_NO_THROW(mDelay->setPan(-100));
}

TEST_F(DelayTestSuite, ParameterSetting) {
	mDelay->setDelay(5);
	EXPECT_EQ(5, mDelay->getDelay());

	mDelay->setGain(0.5);
	EXPECT_EQ(0.5, mDelay->getGain());

	mDelay->setPan(34);
	EXPECT_EQ(34, mDelay->getPan());
}

TEST_F(DelayTestSuite, Delay) {
	mDelay->setDelay(0.1);
	auto sampleDelay = CUtil::float2int<int>(5 * mSampleRate);

	const int numSamples = 10000;
	float input[numSamples]{};
	float output[numSamples]{};
	float ground[numSamples]{};
	input[0] = 1;
	ground[sampleDelay] = 1;
	for (int i = 0; i < numSamples; i++) {
		auto out = mDelay->process(input[i]);
		output[i] = out.first + out.second;
	}
	GTestUtil::compare(output, ground, numSamples);
}