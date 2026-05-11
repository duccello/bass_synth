#include "data.h"

// Shield declaration
AudioControlSGTL5000  codec;

// Oscillators
AudioSynthWaveform    osc;
AudioSynthWaveform    sub;

// Mixer
AudioMixer4           mixer; 

// Filter section
AudioSynthWaveformDc  filterCV;  
AudioEffectEnvelope   filterEnv; 
AudioFilterLadder     ladder;    

// Amplitude section
AudioEffectEnvelope   ampEnv;    

// Output
AudioOutputI2S           i2s1;
AudioOutputUSB           usb1;

// Signal path
AudioConnection p1(osc,      0, mixer,     0);
AudioConnection p2(sub,      0, mixer,     1);
AudioConnection p3(mixer,    0, ampEnv,    0);  
AudioConnection p4(ampEnv,   0, ladder,    0);  

AudioConnection p5(filterCV, 0, filterEnv, 0);  
AudioConnection p6(filterEnv,0, ladder,    1);

AudioConnection p7(ladder,   0, i2s1,      0);
AudioConnection p8(ladder,   0, i2s1,      1);

AudioConnection p9(ladder,   0, usb1,      0);
AudioConnection p10(ladder,   0, usb1,      1);