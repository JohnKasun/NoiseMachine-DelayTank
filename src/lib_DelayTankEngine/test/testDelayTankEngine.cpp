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

TEST_F(DelayTankEngineTestSuite, ReachingMaxDelay) {
	for (int i = 0; i < 20; i++) {
		if (i < 10)
			EXPECT_NO_THROW(mDelayTank->addDelay());
		else
			EXPECT_ANY_THROW(mDelayTank->addDelay());
	}
}

TEST_F(DelayTankEngineTestSuite, IDsAssignCorrectly) {
	EXPECT_EQ(0, mDelayTank->addDelay());
	EXPECT_EQ(1, mDelayTank->addDelay());
	EXPECT_EQ(2, mDelayTank->addDelay());
	mDelayTank->removeDelay(0);
	mDelayTank->removeDelay(1);
	EXPECT_EQ(0, mDelayTank->addDelay());
	EXPECT_EQ(1, mDelayTank->addDelay());
	EXPECT_EQ(3, mDelayTank->addDelay());
}

TEST_F(DelayTankEngineTestSuite, RemovingExistingDelay) {
	auto id = mDelayTank->addDelay();
	EXPECT_NO_THROW(mDelayTank->removeDelay(id));
}

TEST_F(DelayTankEngineTestSuite, RemovingNonExistentDelay) {
	EXPECT_ANY_THROW(mDelayTank->removeDelay(0));
}

TEST_F(DelayTankEngineTestSuite, ParametersSetCorrectly) {
	auto id = mDelayTank->addDelay();
	mDelayTank->setParameter(id, DelayTankEngine::Parameters::DelayTime, 0.01);
	mDelayTank->setParameter(id, DelayTankEngine::Parameters::Gain, 0.5);
	mDelayTank->setParameter(id, DelayTankEngine::Parameters::Pan, 50);
	EXPECT_EQ(0.01f, mDelayTank->getParameter(id, DelayTankEngine::DelayTime));
	EXPECT_EQ(0.5f, mDelayTank->getParameter(id, DelayTankEngine::Gain));
	EXPECT_EQ(50, mDelayTank->getParameter(id, DelayTankEngine::Pan));
}

TEST_F(DelayTankEngineTestSuite, ParameterBoundsHandling) {
	mDelayTank->addDelay();
	EXPECT_ANY_THROW(mDelayTank->setParameter(0, DelayTankEngine::Parameters::DelayTime, -1));
	EXPECT_ANY_THROW(mDelayTank->setParameter(0, DelayTankEngine::Parameters::DelayTime, 11));
	EXPECT_ANY_THROW(mDelayTank->setParameter(0, DelayTankEngine::Parameters::Gain, -384));
	EXPECT_ANY_THROW(mDelayTank->setParameter(0, DelayTankEngine::Parameters::Gain, 2.4));
	EXPECT_ANY_THROW(mDelayTank->setParameter(0, DelayTankEngine::Parameters::Pan, -2084));
	EXPECT_ANY_THROW(mDelayTank->setParameter(0, DelayTankEngine::Parameters::Pan, 2293));
}

TEST_F(DelayTankEngineTestSuite, settingParametersOnNonExistentDelay) {
	EXPECT_ANY_THROW(mDelayTank->setParameter(0, DelayTankEngine::Parameters::DelayTime, 0.3));
}

TEST_F(DelayTankEngineTestSuite, ParametersResetUponRemoval) {
	auto id = mDelayTank->addDelay();
	mDelayTank->setParameter(id, DelayTankEngine::Parameters::DelayTime, 5);
	mDelayTank->setParameter(id, DelayTankEngine::Parameters::Gain, 0.23);
	mDelayTank->setParameter(id, DelayTankEngine::Parameters::Pan, 76);
	mDelayTank->removeDelay(id);
	id = mDelayTank->addDelay();
	EXPECT_EQ(0.0f, mDelayTank->getParameter(id, DelayTankEngine::Parameters::DelayTime));
	EXPECT_EQ(1.0f, mDelayTank->getParameter(id, DelayTankEngine::Parameters::Gain));
	EXPECT_EQ(0.0f, mDelayTank->getParameter(id, DelayTankEngine::Parameters::Pan));
}