/*
 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 2
 of the License, or (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 
 02110-1301, USA.
*/

/**
 * TripleTremolo.cpp
 * TripleTremolo
 *
 * Martin Dittus 2013-06-23
 * @dekstop
 */

#include "TripleTremolo.h"

/**
 * Processing.
 */

void TripleTremolo::prepareToPlay(double sampleRate, int samplesPerBlock){
  this->sampleRate = sampleRate;
}

void TripleTremolo::processBlock(AudioSampleBuffer& buffer, int numInputChannels,
                               int numOutputChannels, MidiBuffer& midiMessages){
  // Atm we're assuming matching input/output channel counts
  jassert(numInputChannels==numOutputChannels);
  
  float freq1 = getFrequency(getParameterValue(PARAMETER_FREQ1));
  float freq2 = getFrequency(getParameterValue(PARAMETER_FREQ2));
  float freq3 = getFrequency(getParameterValue(PARAMETER_FREQ3));

  float step1 = freq1 / sampleRate;
  float step2 = freq2 / sampleRate;
  float step3 = freq3 / sampleRate;

  float amt1 = getParameterValue(PARAMETER_AMT1);
  float amt2 = getParameterValue(PARAMETER_AMT2);
  float amt3 = getParameterValue(PARAMETER_AMT3);
  
  float dryWet = getParameterValue(PARAMETER_DRYWET);

  for (int i=0; i<buffer.getNumSamples(); i++) {
    
    float mod1 = sinf(2 * M_PI * phase1) / 2.0f + .5; // 0..1
    float mod2 = sinf(2 * M_PI * phase2) / 2.0f + .5; // 0..1
    float mod3 = sinf(2 * M_PI * phase3) / 2.0f + .5; // 0..1
    
    float gain1 = (amt1 * mod1) + (1 - amt1);
    float gain2 = (amt2 * mod2) + (1 - amt2);
    float gain3 = (amt3 * mod3) + (1 - amt3);
    float gain = (gain1 * gain2 * gain3) * dryWet + (1 - dryWet);
    
    for (int channel=0; channel<numInputChannels; channel++)
    {
      float *buf = buffer.getSampleData(channel);
      buf[i] = gain * buf[i];
    }
    
    phase1 = fmodf(phase1 + step1, 1.0f);
    phase2 = fmodf(phase2 + step2, 1.0f);
    phase3 = fmodf(phase3 + step3, 1.0f);
  }
}

float TripleTremolo::getFrequency(float p1) {
  return p1*p1 * (MAX_FREQ-MIN_FREQ) + MIN_FREQ;
}


/**
 * Parameters.
 */

const String TripleTremolo::getParameterName(int index){
  if (index >= 0 && index < getNumParameters())
    return parameterNames[index];
  return String::empty;
}

float TripleTremolo::getParameterValue(int index){
  if (index >= 0 && index < getNumParameters())
    return parameterValues[index];
  return 0.0f;
}

void TripleTremolo::setParameterValue(int index, float value){
  if (index >= 0 && index < getNumParameters())
    parameterValues[index] = value;
}


/**
 * State
 */

XmlElement TripleTremolo::getStateInformation(){
  XmlElement state("TripleTremoloState");
  for (int i=0; i<getNumParameters(); i++)
    state.setAttribute(String::formatted("parameter%d", i), getParameterValue(i));
//    state.setAttribute(getParameterName(i), getParameterValue(i));
  return state;
}

void TripleTremolo::setStateInformation(ScopedPointer<XmlElement> state){
  if (state->hasTagName("TripleTremoloState"))
  {
    for (int i=0; i<getNumParameters(); i++)
      setParameterValue(i, (float)state->getDoubleAttribute(String::formatted("parameter%d", i), getParameterValue(i)));
//      setParameterValue(i, (float)state->getDoubleAttribute(getParameterName(i), getParameterValue(i)));
  }
}
