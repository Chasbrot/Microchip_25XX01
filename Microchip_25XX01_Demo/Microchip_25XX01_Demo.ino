/* 
 * This file is part of the MC25XX01 Arduino Library.
 * Copyright (c) 2019 Michael Selinger.
 * 
 * This program is free software: you can redistribute it and/or modify  
 * it under the terms of the GNU General Public License as published by  
 * the Free Software Foundation, version 3.
 *
 * This program is distributed in the hope that it will be useful, but 
 * WITHOUT ANY WARRANTY; without even the implied warranty of 
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU 
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License 
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */
 
#include<SPI.h>
#include "MC25XX01.h"

void setup() {

  Serial.begin(9600);
  SPI.begin();
  MC25XX01 chip;
  
  Serial.println("------WRITE CHIP");

  for (uint8_t i = 0; i < 128; i++) {
    chip.writeByte(i, i);
  }

  Serial.println("\n------READ CHIP");

  for (uint8_t i = 0; i < 128; i++) {
    Serial.print(chip.readByte(i), DEC);
    Serial.print(" ");
    if (i % 4 == 0) {
      Serial.println();
    }
  }
  
  delay(1000);
    
  byte test[16];
  for(int i=0;i<16;i++){
    test[i]=128-i;
  }
  chip.writePage(0,test,16);
  for(int i=0;i<16;i++){
    test[i]=112-i;
  }
  chip.writePage(16,test,16);
  for(int i=0;i<16;i++){
    test[i]=96-i;
  }
  chip.writePage(32,test,16);
  for(int i=0;i<16;i++){
    test[i]=80-i;
  }
  chip.writePage(48,test,16);
  for(int i=0;i<16;i++){
    test[i]=64-i;
  }
  chip.writePage(64,test,16);
  for(int i=0;i<16;i++){
    test[i]=48-i;
  }
  chip.writePage(80,test,16);
  for(int i=0;i<16;i++){
    test[i]=32-i;
  }
  chip.writePage(96,test,16);
  for(int i=0;i<16;i++){
    test[i]=16-i;
  }
  chip.writePage(112,test,16);

  Serial.println("\n------READ CHIP");
  byte *data = chip.readNBytes(0, 128);

  for (uint8_t i = 0; i < 128; i++) {
    Serial.print(data[i], DEC);
    Serial.print(" ");
    if (i % 8 == 0) {
      Serial.println();
    }
  }
}

void loop() {

}
