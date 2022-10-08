#pragma once

#include <juce_audio_processors/juce_audio_processors.h>

#include "DelayTankEngine.h"

juce::AudioProcessorValueTreeState::ParameterLayout createParameterLayout();

//==============================================================================
class AudioPluginAudioProcessor  : public juce::AudioProcessor
{
public:
    //==============================================================================
    AudioPluginAudioProcessor();
    ~AudioPluginAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;
    using AudioProcessor::processBlock;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    void requestParameterChange(int delayId, float delayTime, float gain, float pan);
    static int getMaxNumberOfDelays() { return MaxNumberOfDelays; };

private:
    constexpr static int MaxNumberOfDelays = 10;

    juce::AudioProcessorValueTreeState mParameters;
    std::array<std::array<std::atomic<float>*, 3>, MaxNumberOfDelays> mParamPtrs;

    std::unique_ptr<DelayTankEngine> mDelayTank;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AudioPluginAudioProcessor)
};
