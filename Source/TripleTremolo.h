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

#ifndef TripleTremolo_TripleTremolo_h
#define TripleTremolo_TripleTremolo_h

#include "../JuceLibraryCode/JuceHeader.h"

enum ParameterId {
  PARAMETER_FREQ1 = 0,
  PARAMETER_FREQ2,
  PARAMETER_FREQ3,
  PARAMETER_AMT1,
  PARAMETER_AMT2,
  PARAMETER_AMT3,
  PARAMETER_DRYWET
};

const float MIN_FREQ = 0.2;
const float MAX_FREQ = 35;

class TripleTremolo {
public:

  TripleTremolo() {
    parameterNames.add("Frequency 1");
    parameterNames.add("Frequency 2");
    parameterNames.add("Frequency 3");
    parameterNames.add("Amount 1");
    parameterNames.add("Amount 2");
    parameterNames.add("Amount 3");
    parameterNames.add("Dry/Wet");
    
    parameterValues.resize(parameterNames.size());
//    for (int i=0; i<parameterNames.size(); i++) {
//      parameterValues.push_back(0.5f);
//    }
  }
  
  // Processing
  void prepareToPlay(double sampleRate, int samplesPerBlock);
  void processBlock(AudioSampleBuffer& buffer, int numInputChannels,
                    int numOutputChannels, MidiBuffer& midiMessages);
  
  float getFrequency(float p1);

  // Parameters
  const float getNumParameters(){return parameterNames.size();};
  const String getParameterName(int index);
  float getParameterValue(int index);
  void setParameterValue(int index, float value);

  // State
  XmlElement getStateInformation();
  void setStateInformation(ScopedPointer<XmlElement> state);

private:
  void processChannelBlock(int size, float* buf, float* delayBuf, int delayBufIdx);
  
private:
  StringArray parameterNames;
  std::vector<float> parameterValues;
  
  float sampleRate;

  float phase1, phase2, phase3 = 0;
};

#endif
