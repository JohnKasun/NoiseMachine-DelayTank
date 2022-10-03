#include <gtest/gtest.h>
#include <array>
#include <vector>

#include "Delay.h"
#include "GTestUtil.h"
#include "Vector.h"

class DelayTestSuite: public ::testing::Test
{
protected:
	void SetUp() override {
		mDelay.reset(new Delay(10, mSampleRate));
		mInput.reset(new float[mNumSamples] {});
		for (auto i = 0; i < mOutput.size(); i++) {
			mOutput.at(i).reset(new float[mNumSamples] {});
			mGround.at(i).reset(new float[mNumSamples] {});
		}
	}
	void ClearBuffers() {
		mInput.reset();
		for (auto i = 0; i < mOutput.size(); i++) {
			mOutput.at(i).reset();
			mGround.at(i).reset();
		}
	}
	void TearDown() override {
		ClearBuffers();
		mDelay.reset();
	}
	std::unique_ptr<Delay> mDelay;
	std::unique_ptr<float[]> mInput;
	std::array<std::unique_ptr<float[]>, 2> mOutput;
	std::array<std::unique_ptr<float[]>, 2> mGround;
	float mSampleRate = 44100.0f;
	int mNumSamples = 10000;
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
	const float delays[]{ 0, 0.025, 0.05, 0.075, 0.1, 0.125 };
	for (const auto delay : delays) {
		SetUp();
		mInput[0] = 1;
		mDelay->setDelay(delay);
		auto sampleDelay = CUtil::float2int<int>(delay * mSampleRate);
		assert(sampleDelay < mNumSamples);
		mGround.at(0)[sampleDelay] = 0.5;
		mGround.at(1)[sampleDelay] = 0.5;
		for (int i = 0; i < mNumSamples; i++) {
			auto out = mDelay->process(mInput[i]);
			mOutput.at(0)[i] = out.first;
			mOutput.at(1)[i] = out.second;
		}
		GTestUtil::compare(mOutput.at(0).get(), mGround.at(0).get(), mNumSamples);
		GTestUtil::compare(mOutput.at(1).get(), mGround.at(1).get(), mNumSamples);
		TearDown();
	}
}

TEST_F(DelayTestSuite, Gain) {
	const float gains[]{ 0, 0.25, 0.5, 0.75, 1};
	for (const auto gain : gains) {
		SetUp();
		mDelay->setGain(gain);
		mDelay->setDelay(0);
		mInput[0] = 1;
		auto out = mDelay->process(1);
		EXPECT_EQ(0.5f * gain, out.first);
		EXPECT_EQ(0.5f * gain, out.first);
		TearDown();
	}
}

TEST_F(DelayTestSuite, Pan) {
	const std::pair<float, std::pair<float, float>> pans[]{
		{-100, {1.0f, 0.0f}},
		{0, {0.5f, 0.5f}},
		{100, {0.0f, 1.0f}}
	};
	for (const auto pan : pans) {
		SetUp();
		mDelay->setPan(pan.first);
		mDelay->setDelay(0);
		mInput[0] = 1;
		auto out = mDelay->process(1);
		EXPECT_EQ(pan.second, out);
		TearDown();
	}
}