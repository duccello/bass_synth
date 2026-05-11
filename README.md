In this GIT you can find the Code, electronic layout and 3D design for a Monophonic, foot-controlled synth, designed to play bass while playing piano.
I created this instrument, because all the options I found on the market were either not portable for gigging, or too expensive for what they were.

The code it´s quite simple given the use of the Teensy Audio Library, which already provides 
digital oscilators, envelopes, mixers and all functions one might need to easily make a working digital instrument:
https://www.pjrc.com/teensy/gui/index.html?info=AudioEffectEnvelope

The synth has a simple UI:

4 controls:
PEAK (resonance)
RELEASE
CUTOFF
BLEND (a mix of the SUB and SAW oscilators)

13 buttons to play an octave (C2 to C3).

A HOLD button makes the notes to be sustained, otherwise the Release will control it´s duration. 

You might notice in the code that the notes layout it´s a bit mixed... that´s just because it was my first electronic project and I made some silly mistakes along the way. 

Here is the IDEAL layout:

Pins  0 - 6   → C to F#
Pin   7       → Audioshield
Pins  8 - 13  → G to C
Pin   14 / A0 → BLEND   
Pin   15 / A1 → CUTOFF  
Pin   16 / A2 → RELEASE
Pin   17 / A3 → PEAK  
Pins  18 - 21 → Audioshield
Pin   22      → Hold Button
Pin   23      → Audioshield

All the pins assigned to the Audioshield should match the pin with the same number of the interface. 
For that one can also mount them one of top of each other, in my case I did it with short wires instead.
Detailed info at:
https://www.pjrc.com/store/teensy3_audio.html

IMPORTANT:
Differntly to what you might see in wiring.svg, the 7th pin of the Teensy has to be connected to the 7th pin of the audioshield. therefore I had to sacrifice the volume control and do it externally after the output. 

This also open the possibilty of adding a simple VCA as seen here: https://www.youtube.com/shorts/kmSH9OMylew?si=BwbtT3qPElASROzM and a capacitor to work as a LOW PASS:

So we get something like:

Teensy output
    ↓
volume pot (passive VCA)
    ↓
1kΩ resistor (current limiting + forms RC filter with capacitor)
    ↓─────────────────── output jack
    │
    ├── LED + LED (anti-parallel clipping — soft saturation)
    │
    └── 10nF capacitor to GND (low pass filter, ~16kHz cutoff with 1kΩ)

This is mainly a protection in case there is problem between the Teensy and the Audioshield, which can cause a spike of high-frequency or even ultrasonic noise. That happening in a loud live situation might destroy somebody´s (most likely everybody´s) ears.

Also.. by adding this small circuit we get a bit of an analog touch to the sound.

Please contact me at uccellodante@gmail.com if you need some guidance, I´ll be happy to help.
