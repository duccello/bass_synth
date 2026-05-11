#include "data.h"
#include <Arduino.h>

#define POT_BLEND     A0   // 14
#define POT_CUTOFF    A1   // 15
#define POT_RELEASE   A2   // 16
#define POT_RESONANCE A3   // 17

#define HOLD_PIN 22

static bool holdActive = false;
static bool holdWasPressed = false;
static unsigned long holdLastPress = 0;

static float smoothCutoff    = 800.0f;
static float smoothResonance = 0.3f;
static float smoothBlend     = 0.0f;
static float smoothRelease   = 400.0f;

const int BUTTON_PINS[13] = {0,1,4,3,2,10,6,12,9,8,11,5,13};
static bool wasPressed[13] = {false};
static unsigned long lastPressTime[13] = {0};
const unsigned long DEBOUNCE_MS = 120;

static int lastButton = -1;
static int currentOctave = 2;
//static int lastNote = -1;

void initHardware() 
{
  for (int i = 0; i < 13; i++) {
    pinMode(BUTTON_PINS[i], INPUT_PULLUP);
    wasPressed[i] = (digitalRead(BUTTON_PINS[i]) == LOW);
  }
  pinMode(HOLD_PIN, INPUT_PULLUP); 
}

void readPots() {
  float cutoff    = constrain(analogRead(POT_CUTOFF)    / 1023.0f * 3900.0f + 100.0f, 100.0f, 4000.0f);
  float resonance = constrain(analogRead(POT_RESONANCE) / 1023.0f * 0.65f, 0.0f, 0.65f);
  float blend     = constrain(analogRead(POT_BLEND)     / 1023.0f, 0.0f, 1.0f);
  float release   = constrain(analogRead(POT_RELEASE)   / 1023.0f * 2000.0f, 50.0f, 2000.0f);

  smoothCutoff    += (cutoff    - smoothCutoff)    * 0.05f;
  smoothResonance += (resonance - smoothResonance) * 0.05f;
  smoothBlend     += (blend     - smoothBlend)     * 0.05f;
  smoothRelease   += (release   - smoothRelease)   * 0.05f;

  ladder.frequency(constrain(smoothCutoff,    100.0f, 4000.0f));
  ladder.resonance(constrain(smoothResonance, 0.0f,   0.65f));
  ampEnv.release(constrain(smoothRelease,     50.0f,  2000.0f));

  mixer.gain(0, constrain(1.0f - smoothBlend, 0.0f, 1.0f));
  mixer.gain(1, constrain(smoothBlend,        0.0f, 1.0f));
}

void readButtons() {
  unsigned long now = millis();
  
  for (int i = 0; i < 13; i++) {
    bool pressed = (digitalRead(BUTTON_PINS[i]) == LOW);

    if (pressed != wasPressed[i] && (now - lastPressTime[i]) > DEBOUNCE_MS) {
      lastPressTime[i] = now;
      wasPressed[i] = pressed;

      if (pressed) {
        noteOn(buttonToMidi(i), 0.8f);
        Serial.print("noteOn: ");
        Serial.println(buttonToMidi(i));
      } else {
        noteOff();
      }
    }
  }
}

int getLastButtonPressed() 
{
  return lastButton;
}

int buttonToMidi(int button) 
{
  return (currentOctave + 1) * 12 + button;
}

void readHold() {
  unsigned long now = millis();
  bool pressed = (digitalRead(HOLD_PIN) == LOW);

  if (pressed != holdWasPressed && (now - holdLastPress) > DEBOUNCE_MS) {
    holdLastPress = now;
    holdWasPressed = pressed;

    if (pressed) {
      holdActive = !holdActive;
      if (!holdActive) noteOff();
      Serial.print("hold: ");
      Serial.println(holdActive ? "ON" : "OFF");
    }
  }
}

bool isHoldActive() {
  return holdActive;
}

/*
void handleButtons() 
{
  readButtons();
  int button = getLastButtonPressed();

  if (button != -1 && button != lastNote) 
  {
    if (lastNote != -1)
      noteOff();
    lastNote = button;
    noteOn(buttonToMidi(button), 0.8f);

  } 
  else if (button == -1 && lastNote != -1) 
  {
    noteOff();
    lastNote = -1;
  }
}*/
