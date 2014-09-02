/*
 * First test for Laser Tone Generation
 *
 * We'll shoot lasters at 8 photocells and generate a tone when broken.
 * Connect Photoresistors to A0 ... A7
 * Connect Pyseo to Pin 3 for Tone Genration
 */
  
#include "pitches.h"

int melody[] = {NOTE_C1, NOTE_D2, NOTE_E3, NOTE_F4, NOTE_G5, NOTE_A6, NOTE_B7, NOTE_C8};
// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = {8, 8, 8, 8, 8, 8, 8, 8};

int tonePin = 3;

int lightReadDelay = 10; // Normal from original was 10

typedef struct {
  int curVal;
  int maxVal;
  int deltaVal;
  int note;
  int noteTime;
  int pauseTime;
  int canPlay;
} lightPin_type;

lightPin_type lightPin[8];

void setup()
{
  int i;
  
  Serial.begin(9600);  //Begin serial communcation
  
  // Setup the sensor structure.
  for (i=0; i < 8; i++) {
    lightPin[i].curVal = 0;
    lightPin[i].maxVal = analogRead(i);
    lightPin[i].deltaVal = 0;
    lightPin[i].note = melody[i];
    lightPin[i].noteTime = 1000 / noteDurations[i];
    lightPin[i].pauseTime = lightPin[i].noteTime * 1.30; // dead air til next tone
    lightPin[i].canPlay = 0; // is this tone a candidate tobe played
    
    tone(tonePin, lightPin[i].note, lightPin[i].noteTime);
    delay(lightPin[i].pauseTime);
    noTone(tonePin);
  }
}

void loop()
{
   int i;
   int toneToPlay;
   int maxToPlay;
   
   // We'll store the Max and adjust as we go.
   // A beam will be considered broken when the current value is below 50% the stored max.
   // We'll play the sensor tone with the greatest delta.
   for (i=0; i < 8; i++) {
     lightPin[i].curVal = analogRead(i);
     if (lightPin[i].curVal >> lightPin[i].maxVal) {
       lightPin[i].maxVal = (lightPin[i].maxVal + lightPin[i].curVal) / 2;
       lightPin[i].deltaVal = 0;
       lightPin[i].canPlay = 0;
     } else {
       lightPin[i].deltaVal = lightPin[i].maxVal - lightPin[i].curVal;
       if (lightPin[i].curVal < (lightPin[i].maxVal / 2))
         lightPin[i].canPlay = 1;
     }
     Serial.print(lightPin[i].curVal);
     Serial.print(" ");
   }
   Serial.println(" ");
   
   toneToPlay = 0;
   maxToPlay = 0;
   for (i=0; i < 8; i++) {
     if (lightPin[i].deltaVal > maxToPlay) {
       toneToPlay = i;
       maxToPlay = lightPin[i].deltaVal;
     }
   }
   
   if (lightPin[toneToPlay].canPlay == 1) {
     tone(tonePin, lightPin[toneToPlay].note, lightPin[toneToPlay].noteTime);
     delay(lightPin[toneToPlay].pauseTime);
     noTone(tonePin);
     lightPin[toneToPlay].canPlay = 0;
   }
   
   delay(lightReadDelay); //short delay for faster response to light.
}
