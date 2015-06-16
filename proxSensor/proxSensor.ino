
// these constants won't change:

#include <MIDI.h>
const int channel = 1;

#define GREEN 3
#define BLUE 4
#define RED 5

const int proxPin = A0; 
const int threshold = 20;  // threshold value to decide when the piezo was hit strongly enough

int proxMidiold = 0;
int proxMidi = 0;
int delayMidi = 0;



void setup() {
digitalWrite(proxPin, INPUT);//enable pullup resistor 
 
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);
  pinMode(RED, OUTPUT);
 
 Serial.begin(9600);       // use the serial port
}

void loop() {
  

  int proxSensor = analogRead(proxPin);
  int proxCm = 4192.936 * pow(proxSensor,-0.935);
  int proxMidi = map (proxSensor, 0, 1023, 0, 127);
  
  int redVal = map (proxSensor, 300, 650, 100, 255);
  int greenVal = map (proxSensor, 330, 650, 255, 0);

  /*if (proxmidiold != proxmidi) {
      usbMIDI.sendNoteOff(proxmidiold, 123, channel);
      usbMIDI.sendNoteOn(proxmidi, 123, channel);
      Serial.print(" proxSensor: ");
      Serial.print(proxReading);
      Serial.print(" proxmidi: ");
      Serial.println(proxmidi); 
  }
      proxmidiold = proxmidi;
*/

   usbMIDI.sendNoteOn(proxMidi, 123, channel);
   analogWrite(GREEN, greenVal);
   analogWrite(RED, redVal);     
   delay (100);
   usbMIDI.sendNoteOff(proxMidi ,123, channel);
    while (usbMIDI.read()) ; // read and discard any incoming MIDI messages
 
    
  
    Serial.print(" proxSensor: ");
    Serial.print(proxSensor);
    Serial.print(" Distance in cm: ");
    Serial.print(proxCm);
    Serial.print(" proxmidi: ");
    Serial.print(proxMidi); 
    Serial.print(" Red: ");
    Serial.print(redVal);
    Serial.print(" Green: ");
    Serial.println(greenVal);
  
    delay(50); 
  //delaymidi = map (proxmidi, 38, 127, 127, 0);
  //delay(delaymidi);   //changes tempo according to distance: lower notes are played slower and vice versa
}
