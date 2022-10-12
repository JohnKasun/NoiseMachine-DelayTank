#include "PluginProcessor.h"
#include "PluginEditor.h"

juce::AudioProcessorValueTreeState::ParameterLayout createParameterLayout()
{
    juce::AudioProcessorValueTreeState::ParameterLayout layout;
    for (int i = 0; i < AudioPluginAudioProcessor::getMaxNumberOfDelays(); i++) {
        layout.add(std::make_unique<juce::AudioParameterFloat>(juce::String(i) + "d", "DelayTime" + juce::String(i), 0, 5, 1));
        layout.add(std::make_unique<juce::AudioParameterFloat>(juce::String(i) + "g", "Gain" + juce::String(i), 0, 1, 1));
        layout.add(std::make_unique<juce::AudioParameterFloat>(juce::String(i) + "p", "Pan" + juce::String(i), 0, 1, 1));
      
    }
    return layout;
}

//==============================================================================
AudioPluginAudioProcessor::AudioPluginAudioProcessor()
     : AudioProcessor (BusesProperties()
                       .withInput  ("Input",  juce::AudioChannelSet::mono(), true)
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                       ),
    mParameters(*this, nullptr, "Parameters", createParameterLayout())
{
    for (int i = 0; i < MaxNumberOfDelays; i++) {
        mParamPtrs[i][0] = mParameters.getRawParameterValue(juce::String(i) + "d");
        mParamPtrs[i][1] = mParameters.getRawParameterValue(juce::String(i) + "g");
        mParamPtrs[i][2] = mParameters.getRawParameterValue(juce::String(i) + "p");
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
}

//==============================================================================
bool AudioPluginAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* AudioPluginAudioProcessor::createEditor()
{
    return new AudioPluginAudioProcessorEditor (*this, mParameters);
   // return new juce::GenericAudioProcessorEditor(*this);
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

int AudioPluginAudioProcessor::addDelay()
{
    return mDelayTank->addDelay();
}

void AudioPluginAudioProcessor::requestParameterChange(int delayId, float delayTime, float gain, float pan)
{
    auto paramIdDelay = juce::String(delayId) + "d";
    auto paramIdGain = juce::String(delayId) + "g";
    auto paramIdPan = juce::String(delayId) + "p";
    mParameters.getParameter(paramIdDelay)->setValueNotifyingHost(mParameters.getParameterRange(paramIdDelay).convertTo0to1(delayTime));
    mParameters.getParameter(paramIdGain)->setValueNotifyingHost(mParameters.getParameterRange(paramIdGain).convertTo0to1(gain));
    mParameters.getParameter(paramIdPan)->setValueNotifyingHost(mParameters.getParameterRange(paramIdPan).convertTo0to1(pan));
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new AudioPluginAudioProcessor();
}
