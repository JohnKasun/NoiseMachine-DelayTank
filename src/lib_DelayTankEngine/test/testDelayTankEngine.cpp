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
			EXPECT_TRUE(mDelayTank->addDelay(i));
		else
			EXPECT_FALSE(mDelayTank->addDelay(i));
	}
}

TEST_F(DelayTankEngineTestSuite, IDsAssignCorrectly) {
	EXPECT_TRUE(mDelayTank->addDelay(0));
	EXPECT_TRUE(mDelayTank->removeDelay(0));
}

TEST_F(DelayTankEngineTestSuite, RemovingNonExistentDelay) {
	EXPECT_FALSE(mDelayTank->removeDelay(0));
}

TEST_F(DelayTankEngineTestSuite, ParametersSetCorrectly) {
	mDelayTank->addDelay(0);
	mDelayTank->setParameter(0, DelayTankEngine::Parameters::DelayTime, 0.01);
	mDelayTank->setParameter(0, DelayTankEngine::Parameters::Gain, 0.5);
	mDelayTank->setParameter(0, DelayTankEngine::Parameters::Pan, 50);
	EXPECT_EQ(0.01f, mDelayTank->getParameter(0, DelayTankEngine::Parameters::DelayTime));
	EXPECT_EQ(0.5f, mDelayTank->getParameter(0, DelayTankEngine::Parameters::Gain));
	EXPECT_EQ(50, mDelayTank->getParameter(0, DelayTankEngine::Parameters::Pan));
}

TEST_F(DelayTankEngineTestSuite, ParameterBoundsHandling) {
	mDelayTank->addDelay(0);
	EXPECT_ANY_THROW(mDelayTank->setParameter(0, DelayTankEngine::Parameters::DelayTime, -1));
	EXPECT_ANY_THROW(mDelayTank->setParameter(0, DelayTankEngine::Parameters::DelayTime, 11));
	EXPECT_ANY_THROW(mDelayTank->setParameter(0, DelayTankEngine::Parameters::Gain, -384));
	EXPECT_ANY_THROW(mDelayTank->setParameter(0, DelayTankEngine::Parameters::Gain, 2.4));
	EXPECT_ANY_THROW(mDelayTank->setParameter(0, DelayTankEngine::Parameters::Pan, -2084));
	EXPECT_ANY_THROW(mDelayTank->setParameter(0, DelayTankEngine::Parameters::Pan, 2293));
}

TEST_F(DelayTankEngineTestSuite, SettingParametersOnNonExistentDelay) {
	EXPECT_ANY_THROW(mDelayTank->setParameter(0, DelayTankEngine::Parameters::DelayTime, 0.3));
}

TEST_F(DelayTankEngineTestSuite, ParametersResetUponRemoval) {
	auto id = 0;
	mDelayTank->addDelay(id);
	mDelayTank->setParameter(id, DelayTankEngine::Parameters::DelayTime, 5);
	mDelayTank->setParameter(id, DelayTankEngine::Parameters::Gain, 0.23);
	mDelayTank->setParameter(id, DelayTankEngine::Parameters::Pan, 76);
	mDelayTank->removeDelay(id);
	mDelayTank->addDelay(id);
	EXPECT_EQ(0.0f, mDelayTank->getParameter(id, DelayTankEngine::Parameters::DelayTime));
	EXPECT_EQ(1.0f, mDelayTank->getParameter(id, DelayTankEngine::Parameters::Gain));
	EXPECT_EQ(0.0f, mDelayTank->getParameter(id, DelayTankEngine::Parameters::Pan));
}

TEST_F(DelayTankEngineTestSuite, MultipleDelayDelaytime) {
	auto delay1Id = 1;
	mDelayTank->addDelay(delay1Id);
	auto delay2Id = 2;
	mDelayTank->addDelay(delay2Id);
	auto delay3Id = 3;
	mDelayTank->addDelay(delay3Id);
	mDelayTank->setParameter(delay1Id, DelayTankEngine::Parameters::DelayTime, 0.05);
	mDelayTank->setParameter(delay2Id, DelayTankEngine::Parameters::DelayTime, 0.05);
	mDelayTank->setParameter(delay3Id, DelayTankEngine::Parameters::DelayTime, 0.05);
	auto sampleDelay = CUtil::float2int<int>(0.05 * mSampleRate);
	mGround.at(0)[sampleDelay] = 1.5;
	mGround.at(1)[sampleDelay] = 1.5;
	mDelayTank->process(1.0f);
	for (int i = 1; i < mNumSamples; i++) {
		auto out = mDelayTank->process(0.0f);
		mOutput.at(0)[i] = out.first;
		mOutput.at(1)[i] = out.second;
	}
	GTestUtil::compare(mGround.at(0).get(), mOutput.at(0).get(), mNumSamples);
	GTestUtil::compare(mGround.at(1).get(), mOutput.at(1).get(), mNumSamples);
}

TEST_F(DelayTankEngineTestSuite, MultipleDelayPan) {
	auto delay1Id = 1;
	mDelayTank->addDelay(delay1Id);
	auto delay2Id = 2;
	mDelayTank->addDelay(delay2Id);
	auto delay3Id = 3;
	mDelayTank->addDelay(delay3Id);
	mDelayTank->setParameter(delay1Id, DelayTankEngine::Parameters::Pan, -100);
	mDelayTank->setParameter(delay2Id, DelayTankEngine::Parameters::Pan, -100);
	mDelayTank->setParameter(delay3Id, DelayTankEngine::Parameters::Pan, 100);
	auto out = mDelayTank->process(1.0f);
	EXPECT_EQ(2.0f, out.first);
	EXPECT_EQ(1.0f, out.second);
}

TEST_F(DelayTankEngineTestSuite, MultipleDelayGain) {
	auto delay1Id = 1;
	mDelayTank->addDelay(delay1Id);
	auto delay2Id = 2;
	mDelayTank->addDelay(delay2Id);
	auto delay3Id = 3;
	mDelayTank->addDelay(delay3Id);
	mDelayTank->setParameter(delay1Id, DelayTankEngine::Parameters::Gain, 0.5);
	mDelayTank->setParameter(delay2Id, DelayTankEngine::Parameters::Gain, 0.1);
	mDelayTank->setParameter(delay3Id, DelayTankEngine::Parameters::Gain, 0.2);
	auto out = mDelayTank->process(1.0f);
	EXPECT_EQ(0.4f, out.first);
	EXPECT_EQ(0.4f, out.second);
}