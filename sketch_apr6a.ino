#include "data.h"

void setup() 
{
  osc.frequency(55.0f);
  //ampEnv.noteOn();
  //filterEnv.noteOn();

  initHardware();
  AudioMemory(60);
  buildFreqTable();

  // oscillators
  osc.begin(WAVEFORM_SAWTOOTH);
  osc.amplitude(0.8f);
  sub.begin(WAVEFORM_SINE);
  sub.amplitude(0.4f);

  // mixer
  mixer.gain(0, 0.6f);
  mixer.gain(1, 0.4f);

  // filter
  ladder.frequency(800.0f);
  ladder.resonance(0.3f);
  //filterCV.amplitude(1.0f);

  // envelopes
  ampEnv.attack(10);
  ampEnv.decay(200);
  ampEnv.sustain(0.3f);
  ampEnv.release(400);
  ampEnv.releaseNoteOn(10);

  filterEnv.attack(15);
  filterEnv.decay(400);
  filterEnv.sustain(0.0f);
  filterEnv.release(300);


  // audio shield
  codec.enable();
  Serial.println(codec.enable());
  codec.volume(0.8f);
  codec.lineOutLevel(29);
  codec.enhanceBass(0.85f, 0.4f);
  
  // EQ
  codec.eqSelect(2);
  codec.eqBands(-0.1f, 0.2f, -0.1f, -0.2f, -0.3f);
}

void loop() 
{
  readButtons();
  readHold();
  readPots();
  //midiHandler();
}