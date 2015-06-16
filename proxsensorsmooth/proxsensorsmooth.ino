  const int proxPin = A0; 

void setup() {
  
  digitalWrite(proxPin, INPUT);  //input 
  Serial.begin(9600);            // use the serial port
  }

void loop() {
  
  int proxSensor = analogRead(proxPin);                                                           //read proximity sensor
  
  
  
  int proxSensorSmooth = 0;
  
 

  Serial.print(" proxSensor: ");
  Serial.print(proxSensor);
  Serial.print(" proxSensorsmooth: ");
  Serial.println(proxSensorSmooth);
  
 
  delay(25);
  
  
}
