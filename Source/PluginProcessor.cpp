/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic startup code for a Juce application.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
TripleTremoloAudioProcessor::TripleTremoloAudioProcessor()
{
}

TripleTremoloAudioProcessor::~TripleTremoloAudioProcessor()
{
}

//==============================================================================
const String TripleTremoloAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

int TripleTremoloAudioProcessor::getNumParameters()
{
    return tripleTremolo.getNumParameters();
}

float TripleTremoloAudioProcessor::getParameter (int index)
{
    return tripleTremolo.getParameterValue(index);
}

void TripleTremoloAudioProcessor::setParameter (int index, float newValue)
{
    tripleTremolo.setParameterValue(index, newValue);
}

const String TripleTremoloAudioProcessor::getParameterName (int index)
{
    return tripleTremolo.getParameterName(index);
}

const String TripleTremoloAudioProcessor::getParameterText (int index)
{
    return tripleTremolo.getParameterName(index);
}

const String TripleTremoloAudioProcessor::getInputChannelName (int channelIndex) const
{
    return String (channelIndex + 1);
}

const String TripleTremoloAudioProcessor::getOutputChannelName (int channelIndex) const
{
    return String (channelIndex + 1);
}

bool TripleTremoloAudioProcessor::isInputChannelStereoPair (int index) const
{
    return true;
}

bool TripleTremoloAudioProcessor::isOutputChannelStereoPair (int index) const
{
    return true;
}

bool TripleTremoloAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool TripleTremoloAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool TripleTremoloAudioProcessor::silenceInProducesSilenceOut() const
{
    return true;
}

double TripleTremoloAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int TripleTremoloAudioProcessor::getNumPrograms()
{
    return 0;
}

int TripleTremoloAudioProcessor::getCurrentProgram()
{
    return 0;
}

void TripleTremoloAudioProcessor::setCurrentProgram (int index)
{
}

const String TripleTremoloAudioProcessor::getProgramName (int index)
{
    return String::empty;
}

void TripleTremoloAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void TripleTremoloAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    tripleTremolo.prepareToPlay(sampleRate, samplesPerBlock);
}

void TripleTremoloAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

void TripleTremoloAudioProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    tripleTremolo.processBlock(buffer, getNumInputChannels(), getNumOutputChannels(), midiMessages);

    // In case we have more outputs than inputs, we'll clear any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    for (int i = getNumInputChannels(); i < getNumOutputChannels(); ++i)
    {
        buffer.clear (i, 0, buffer.getNumSamples());
    }
}

void TripleTremoloAudioProcessor::reset()
{
  // Use this method as the place to clear any delay lines, buffers, etc, as it
  // means there's been a break in the audio's continuity.
  tripleTremolo.reset();
}

//==============================================================================
bool TripleTremoloAudioProcessor::hasEditor() const
{
    return false; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* TripleTremoloAudioProcessor::createEditor()
{
    return NULL;
}

//==============================================================================
void TripleTremoloAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
    copyXmlToBinary(tripleTremolo.getStateInformation(), destData);
}

void TripleTremoloAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
    ScopedPointer<XmlElement> xmlState (getXmlFromBinary(data, sizeInBytes));
    if (xmlState != nullptr)
    {
        tripleTremolo.setStateInformation(xmlState);
    }
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new TripleTremoloAudioProcessor();
}
