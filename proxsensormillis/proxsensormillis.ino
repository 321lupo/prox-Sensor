  #include <MIDI.h>
  const int channel = 1;

  const int proxPin = A14;                        //proxSensor on A14

  unsigned long time;                            // mili timer
  unsigned long timeProxMidiOn = 0;              // timer midi notes on 
  unsigned long timeProxMidiOff = 0;             // timer midi notes on 
  unsigned long proxMidiDelay = 250;             // time between midi note off-on 
  unsigned long proxMidiSustain = 50;           // length between midi note on-off  SUSTAIN CANNOT BE LONGER THAT DELAY!!!
  
  unsigned long timeSerialPrint = 0;
  unsigned long serialPrintDelay = 200;
  
  #define GREEN 3                                //LEDS
  #define BLUE 4
  #define RED 5

void setup() {
  
  digitalWrite(proxPin, INPUT);                  //enable pullup resistor 
 
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);
  pinMode(RED, OUTPUT);

  Serial.begin(9600);                            // use the serial port

}

void loop() {
  
  time = millis();
  
  int proxSensor = analogRead(proxPin);                                                           //read proximity sensor
  int proxMidi = map (proxSensor, 0, 1023, 0, 127);                                               //map midinotes according to sensor value 
  
  if (time - timeProxMidiOn >= proxMidiDelay) {                                                   //after the amount of proxMidiDelay time, send midi note
    usbMIDI.sendNoteOn(proxMidi,123,channel);  
    timeProxMidiOn = time;                                                                        //set times equal
    timeProxMidiOff = time;
    }  
    
  if (time - timeProxMidiOff >= proxMidiSustain) {                                                //after amount of time proxMidiSustain, send midi off
    usbMIDI.sendNoteOff(proxMidi,123,channel);                                                    
    }
    
  int redVal = map (proxSensor, 300, 650, 100, 255);                                              //make sensor react to ableton send midis? or keep at straight sign?
  int greenVal = map (proxSensor, 330, 650, 255, 0);                                              //calculate rgb led values according to sensordata
  analogWrite(GREEN, greenVal);                                                                   //write rgb led values
  analogWrite(RED, redVal);   

  if(time-timeSerialPrint>=serialPrintDelay) {                                                    //after amount of time serialPrintDelay send Serial Print data
    timeSerialPrint = time;
    Serial.print(" proxSensor: ");
    Serial.print(proxSensor);
    Serial.print(" proxMidion: ");
    Serial.print(proxMidi);      
    Serial.print(" proxMidion: ");
    Serial.print(proxMidi);          
    Serial.println(" "); 
  }
  while (usbMIDI.read()) ;                                                                        // read and discard any incoming MIDI messages
}
