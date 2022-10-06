#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
AudioPluginAudioProcessor::AudioPluginAudioProcessor()
     : AudioProcessor (BusesProperties()
                       .withInput  ("Input",  juce::AudioChannelSet::mono(), true)
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                       )
{
    juce::ValueTree delayRanges("Delay");
    delayRanges.setProperty(juce::Identifier("Max"), 3.0f, nullptr);
    delayRanges.setProperty(juce::Identifier("Default"), 0.1f, nullptr);
    delayRanges.setProperty(juce::Identifier("Min"), 0.0f, nullptr);
    juce::ValueTree panRanges("Pan");
    panRanges.setProperty(juce::Identifier("Max"), 100, nullptr);
    panRanges.setProperty(juce::Identifier("Default"), 0.0f, nullptr);
    panRanges.setProperty(juce::Identifier("Min"), -100.0f, nullptr);
    juce::ValueTree gainRanges("Gain");
    gainRanges.setProperty(juce::Identifier("Max"), 1.0f, nullptr);
    gainRanges.setProperty(juce::Identifier("Default"), 1.0f, nullptr);
    gainRanges.setProperty(juce::Identifier("Min"), 0.0f, nullptr);
    mParameterRanges.addChild(delayRanges, 0, nullptr);
    mParameterRanges.addChild(panRanges, 1, nullptr);
    mParameterRanges.addChild(gainRanges, 2, nullptr);

    for (int i = 0; i < MaxNumberOfDelays; i++) {
        juce::ValueTree params(juce::Identifier("Delay" + juce::String(i)));
        params.setProperty(juce::Identifier("DelayTime"), mParameterRanges.getChild(0).getProperty(juce::Identifier("Default")), nullptr);
        params.setProperty(juce::Identifier("Pan"), mParameterRanges.getChild(1).getProperty(juce::Identifier("Default")), nullptr);
        params.setProperty(juce::Identifier("Gain"), mParameterRanges.getChild(2).getProperty(juce::Identifier("Default")), nullptr);
        mDelayTime.emplace_back(params.getPropertyPointer("DelayTime"));
        mPan.emplace_back(params.getPropertyPointer("Pan"));
        mGain.emplace_back(params.getPropertyPointer("Gain"));
        mParameterValues.addChild(params, i, nullptr);
    }
}

AudioPluginAudioProcessor::~AudioPluginAudioProcessor()
{
}

//==============================================================================
const juce::String AudioPluginAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool AudioPluginAudioProcessor::acceptsMidi() const
{
    return false;
}

bool AudioPluginAudioProcessor::producesMidi() const
{
    return false;
}

bool AudioPluginAudioProcessor::isMidiEffect() const
{
    return false;
}

double AudioPluginAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int AudioPluginAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int AudioPluginAudioProcessor::getCurrentProgram()
{
    return 0;
}

void AudioPluginAudioProcessor::setCurrentProgram (int index)
{
    juce::ignoreUnused (index);
}

const juce::String AudioPluginAudioProcessor::getProgramName (int index)
{
    juce::ignoreUnused (index);
    return {};
}

void AudioPluginAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
    juce::ignoreUnused (index, newName);
}

//==============================================================================
void AudioPluginAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    mDelayTank.reset(new DelayTankEngine(3, 10, sampleRate));
    for (int i = 0; i < MaxNumberOfDelays; i++) {
        mDelayTank->addDelay();
    }
}

void AudioPluginAudioProcessor::releaseResources()
{
    mDelayTank.reset();
}

bool AudioPluginAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
        || layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo()) {
        return false;
    }

    if (layouts.getMainOutputChannels() < layouts.getMainInputChannels())
        return false;

    return true;
}

void AudioPluginAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer,
                                              juce::MidiBuffer& midiMessages)
{
    juce::ignoreUnused (midiMessages);

    juce::ScopedNoDenormals noDenormals;

    for (int i = 0; i < MaxNumberOfDelays; i++) {
        auto delay = mParameterValues.getChild(i);
        try {
            mDelayTank->setParameter(i, DelayTankEngine::Parameters::DelayTime, delay.getProperty(juce::Identifier("DelayTime")));
            mDelayTank->setParameter(i, DelayTankEngine::Parameters::Pan, delay.getProperty(juce::Identifier("Pan")));
            mDelayTank->setParameter(i, DelayTankEngine::Parameters::Gain, delay.getProperty(juce::Identifier("Gain")));
        }
        catch (Exception& ex) {

        }
    }
}

//==============================================================================
bool AudioPluginAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* AudioPluginAudioProcessor::createEditor()
{
    return new AudioPluginAudioProcessorEditor (*this, mParameterValues);
}

//==============================================================================
void AudioPluginAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
    juce::ignoreUnused (destData);
}

void AudioPluginAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
    juce::ignoreUnused (data, sizeInBytes);
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new AudioPluginAudioProcessor();
}
