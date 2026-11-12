/*-----------------------------------------------------------------\
@ Embedded Controller by Young-Keun Kim - Handong Global University
Author           : Lee Jae Yong (22200570)
Created          : 09-10-2026
Modified         : 09-20-2026
Language/ver     : Arduino (STM32duino) in Arduino IDE

Description      : LAB_GPIO_DIO_LED - Problem 0 (STM-Arduino)
/-----------------------------------------------------------------*/

const int btnPin = 3;
const int ledPin = 13;

int btnState = HIGH;

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(btnPin, INPUT);
}

void loop() {
  btnState = digitalRead(btnPin);

  if (btnState == HIGH) 
    digitalWrite(ledPin, LOW);
  
  else 
    digitalWrite(ledPin, HIGH);
  
}
