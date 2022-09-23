
#include "Arduino.h"
#include <MIDI.h>

#define TUNE_MIN_TIME 2


// 2 
uint8_t pinButton[] = {2, 3, 4, 5, 6, 7, 8, 9, 10,11,12,A0,A1,A2,A4};
uint8_t note[] =      {30,31,32,33,34,35,36,37,38,39,40,41,42,43,44};

// 1
// uint8_t pinButton[] = {A2,A1,A0,A3,A4,11,10,9 ,8 ,7 ,6 ,5 ,4 ,3 , 2};
// uint8_t note[] =      {45,46,47,48,49,50,51,52,53,55,56,57,58,59,60};
uint8_t oldState[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

MIDI_CREATE_DEFAULT_INSTANCE();


void setup()
{
  // Configuration de la broche 12 en tant qu'entree numerique.
  MIDI.begin(1);
  Serial.begin(115200);
  for(int i=0; i<20; i++){
    pinMode(i, INPUT);
    digitalWrite(i, HIGH);
  }
}

void scanNote(uint8_t index){
  //velocity of MIDI notes, must be between 0 and 127
  uint8_t velocity = 127;
  uint8_t boutonPressed = digitalRead(pinButton[index]);

  if (boutonPressed == 0)
  {
   if (oldState[index] == 0)
      {
        MIDI.sendNoteOn(note[index], velocity, 1);
        oldState[index] = 1;
      }
  }
  else
  {
    MIDI.sendNoteOff(note[index],0,1);
    oldState[index] = 0;
  }

}

void loop()
{
  for (uint8_t i=0; i < 15; i++){
    scanNote(i);
  }
}
