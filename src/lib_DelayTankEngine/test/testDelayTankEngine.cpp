#include <gtest/gtest.h>
#include <array>

#include "DelayTankEngine.h"
#include "GTestUtil.h"

class DelayTankEngineTestSuite : public ::testing::Test
{
protected:
	void SetUp() override {
		mDelayTank.reset(new DelayTankEngine(10, 10, mSampleRate));
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
		mDelayTank.reset();
	}
	std::unique_ptr<DelayTankEngine> mDelayTank;
	std::unique_ptr<float[]> mInput;
	std::array<std::unique_ptr<float[]>, 2> mOutput;
	std::array<std::unique_ptr<float[]>, 2> mGround;
	float mSampleRate = 44100.0f;
	int mNumSamples = 10000;
};

TEST_F(DelayTankEngineTestSuite, AddingDelays) {
	for (int i = 0; i < 10; i++) {
		EXPECT_NO_THROW(mDelayTank->addDelay());
	}
	EXPECT_ANY_THROW(mDelayTank->addDelay());
}

TEST_F(DelayTankEngineTestSuite, IdBackLog) {
	mDelayTank->addDelay();
	mDelayTank->addDelay();
	mDelayTank->addDelay();
	mDelayTank->removeDelay(0);
	mDelayTank->removeDelay(1);
	EXPECT_EQ(0, mDelayTank->addDelay());
	EXPECT_EQ(1, mDelayTank->addDelay());
	EXPECT_EQ(3, mDelayTank->addDelay());
}

TEST_F(DelayTankEngineTestSuite, RemovingDelays) {
	EXPECT_FALSE(mDelayTank->removeDelay(0));
	mDelayTank->addDelay();
	EXPECT_TRUE(mDelayTank->removeDelay(0));
}