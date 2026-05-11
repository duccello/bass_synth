#pragma once

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>

// Oscillators
extern AudioSynthWaveform    osc;      
extern AudioSynthWaveform    sub;        

// Mixer
extern AudioMixer4           mixer; 

// Filter section
extern AudioSynthWaveformDc  filterCV;  
extern AudioEffectEnvelope   filterEnv; 
extern AudioFilterLadder     ladder;    

// Amplitude section
extern AudioEffectEnvelope   ampEnv;    

// Output
extern AudioOutputI2S        i2s1;
extern AudioOutputUSB        usb1;
extern AudioControlSGTL5000  codec;

// MIDI
void midiHandler();
int  keyToMidi(int key);
void shiftOctave(int direction);

const int MIDI_NOTES = 128;
const int NUM_KEYS   = 12;
const int DEFAULT_OCTAVE = 3;

// HARDWARE
void initHardware();
void readPots();
void readButtons();
int  getLastButtonPressed();
void handleButtons();
int buttonToMidi(int button);

//NOTES
void buildFreqTable();
void noteOn(int midiNote, float velocity);
void noteOff();

//HOLD
void readHold();
bool isHoldActive();
