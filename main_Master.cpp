#include <Arduino.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_GC9A01A.h>

Adafruit_GC9A01A Dsg(7, 9); // CS, DC, RESET

int TenVal = 0; 

byte LedPinSel(){ //Led Pin Selection
    if(TenVal <= 5*0,3)
        return 0x00;
    else if(TenVal> 5*0,3 && TenVal <= 5*0,8)
        return 0x01;
    else if(TenVal > 5*0,8)
        return 0x02;
}

void setup(){
    Serial.begin(9600);
    SPI.begin();
    SPI.setClockDivider(SPI_CLOCK_DIV8);
    digitalWrite(SS, HIGH); 
    Dsg.begin();
    Dsg.width();
}

void loop(){
    byte Ms_Tx, Ms_Rx;
    
    digitalWrite(SS, LOW);
    TenVal = Ms_Tx / 51; // convert 0-255 to 0-5
    Ms_Tx = LedPinSel();
    Ms_Rx = SPI.transfer(Ms_Tx); // start the transfer

    Dsg.fillScreen(GC9A01A_MAGENTA);
    
}