#include "data.h"

static int currentOctave = DEFAULT_OCTAVE;

int keyToMidi(int key) 
{
  return (currentOctave + 1) * 12 + key;
}

void shiftOctave(int direction) 
{
  int next = currentOctave + direction;
  if (next >= 0 && next <= 9)
    currentOctave = next;
}

void midiHandler() 
{
  while (usbMIDI.read()) {
    byte type     = usbMIDI.getType();
    byte note     = usbMIDI.getData1();
    byte velocity = usbMIDI.getData2();

    if (type == usbMIDI.NoteOn && velocity > 0)
      noteOn(note, velocity / 127.0f);
    else if (type == usbMIDI.NoteOff || (type == usbMIDI.NoteOn && velocity == 0))
      noteOff();
  }
}