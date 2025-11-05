#include <Arduino.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_GC9A01A.h>

volatile boolean RxFlag = 0;
volatile byte Rx_SVR, Tx_SVR; // Reciver/Transmit Slave Value Read
#define SVR A0 // Slave Value Read
#define RL 3
#define GL 4

void setup() {
  Serial.begin(9600);
  pinMode(RL, OUTPUT);
  pinMode(GL, OUTPUT);

  SPCR |= 1<<SPE; //abilitazione modulo SPI

  SPI.attachInterrupt();

}

ISR (SPI_STC_vect){
  Rx_SVR = SPDR;
  RxFlag = true;
}

void loop() {
  if (RxFlag){
    if(Rx_SVR == 0x00){
      digitalWrite(RL, LOW);
      digitalWrite(GL, LOW);
    }
    if(Rx_SVR == 0x01){
      digitalWrite(RL, LOW);
      digitalWrite(GL, HIGH);
    }
    if(Rx_SVR == 0x02){
      digitalWrite(RL, HIGH);
      digitalWrite(GL, LOW);
    }
  }
  Tx_SVR = analogRead(SVR) / 4; // read the input on analog pin 0 (0-1023) and map it to 0-255
  SPDR = Tx_SVR; // send the value to the master
  
}

