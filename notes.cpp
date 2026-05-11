#include "data.h"
#include <math.h>
#include <Audio.h>
#include <Wire.h>
#include <SPI.h>

static float midiFreqTable[128];
static int currentNote = -1;

void buildFreqTable() 
{
  for (int note = 0; note < 128; note++)
    midiFreqTable[note] = 440.0f * powf(2.0f, (note - 69) / 12.0f);
}

void noteOn(int midiNote, float velocity) {
  if (midiNote == currentNote)
    return;
  currentNote = midiNote;
  float freq = midiFreqTable[midiNote];

  osc.frequency(freq);
  sub.frequency(freq * 0.5f);
  float noteTracking = freq * 0.3f;
  ladder.frequency(200.0f + noteTracking);

  ampEnv.noteOn();
  filterEnv.noteOn();
  Serial.print("noteOn: ");
  Serial.println(midiNote);
}

void noteOff() {
  if (isHoldActive()) 
      return;
  currentNote = -1;
  ampEnv.noteOff();
  filterEnv.noteOff();
}