/** Arduino Doorbell
 *  Harry A.
 *  Will only play once when the button is held.
 */

#include "pitches.h"

#define pinButton 7
#define pinLED 3
#define pinLED2 4
#define pinLED3 6
#define pinSpeaker 5

void setup() {
  pinMode(pinLED, OUTPUT);
  pinMode(pinButton, INPUT);
}

// Variable that prevents the tune from continuesly playing when the button is
// held down.
int hasPlayed = 0;

void loop() {
  switch (getButtonStatus(pinButton)) {
    case 1:
      digitalWrite(pinLED3, HIGH);
      break;

    default:
      digitalWrite(pinLED3, LOW);
      break;
  }
  if (getButtonStatus(pinButton) == 1) {
    digitalWrite(pinLED, HIGH);
    // If the tune hasn't played already, play it.
    if (hasPlayed == 0)
      playDoorbellTune();
    // Acknowledge that the tune has played.
    hasPlayed = 1;
  } else {
    digitalWrite(pinLED, LOW);
    // Button has been released; acknowledge that.
    hasPlayed = 0;
  }
}

/**
 * @param pin The pin number that the button is plugged into.
 * @returns 1 if button is pushed, 0 otherwise
 */
int getButtonStatus(int pin) {
  int pinStatus = digitalRead(pin);
  if (pinStatus == HIGH) {
    return 0;
  } else {
    return 1;
  }
}

/**
 * Plays a simple door bell tune that is the default Ring doorbell chime.
 * (E5, G5, C5)
 * @returns void
 */
void playDoorbellTune() {
  digitalWrite(pinLED2, HIGH);
  tone(pinSpeaker, NOTE_E5);
  delay(500);
  tone(pinSpeaker, NOTE_G5);
  delay(250);
  tone(pinSpeaker, NOTE_C5);
  delay(500);
  digitalWrite(pinLED2, LOW);
  noTone(pinSpeaker);
}