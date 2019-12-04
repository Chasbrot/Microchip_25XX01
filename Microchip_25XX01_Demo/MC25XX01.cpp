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

/*
 * Reads one Byte from the specified Address (0-127)
 */
uint8_t MC25XX01::readByte(uint8_t address){
  digitalWrite(HOLD,HIGH);
  digitalWrite(CS,LOW);
  SPI.transfer(READ);
  SPI.transfer(address);
  uint8_t datarec = SPI.transfer(0);
  digitalWrite(CS,HIGH);
  digitalWrite(HOLD,LOW);
  return datarec;
}

/*
 * Reads the Status Register
 */
uint8_t MC25XX01::readSR(){
  digitalWrite(HOLD,HIGH);
  digitalWrite(CS,LOW);
  SPI.transfer(RDSR);
  uint8_t datarec = SPI.transfer(0);
  digitalWrite(CS,HIGH);
  return datarec;
}

/*
 * Reads N Bytes starting from the specified Location. 
 * Loops after position 127 back to 0
 */
uint8_t * MC25XX01::readNBytes(uint8_t start_address, uint8_t bytes){
  uint8_t data[bytes+80];
  digitalWrite(HOLD,HIGH);
  digitalWrite(CS,LOW);
  SPI.transfer(READ);
  SPI.transfer(start_address);
  for(uint8_t i =0; i<bytes; i++){
    data[i]=SPI.transfer(0);
  }
  digitalWrite(CS,HIGH);
  return data;
}

/*
 * Writes the Status Register with the specified Byte
 */
void MC25XX01::writeSR(uint8_t data){
  digitalWrite(HOLD,HIGH);
  digitalWrite(WP,HIGH);
  digitalWrite(CS,LOW);
  // Reset WREN Latch
  SPI.transfer(WREN);
  digitalWrite(CS,HIGH);
  digitalWrite(CS,LOW);
  SPI.transfer(WRSR);
  SPI.transfer(data);
  digitalWrite(CS,HIGH);
  delay(5);
}

/*
 * Writes a specified Byte to the supplied address (0-127)
 */
void MC25XX01::writeByte(uint8_t address, uint8_t data){
  digitalWrite(HOLD,HIGH);
  digitalWrite(WP,HIGH);
  digitalWrite(CS,LOW);
  // Reset WREN Latch
  SPI.transfer(WREN);
  digitalWrite(CS,HIGH);
  digitalWrite(CS,LOW);
  // Write Data
  SPI.transfer(WRITE);
  SPI.transfer(address);
  SPI.transfer(data);
  digitalWrite(CS,HIGH);
  delay(5);
}

/*
 * Writes up to 16 Bytes at a Time in a row, starting from the specified Address.
 */
void MC25XX01::writePage(uint8_t start_address, uint8_t* data, uint8_t anz){
  digitalWrite(HOLD,HIGH);
  digitalWrite(WP,HIGH);
  digitalWrite(CS,LOW);
  // Reset WREN Latch
  SPI.transfer(WREN);
  digitalWrite(CS,HIGH);
  digitalWrite(CS,LOW);
  // Write Data
  SPI.transfer(WRITE);
  SPI.transfer(start_address);
  for(uint8_t i =0; i<anz;i++){
    SPI.transfer(data[i]);
  }
  digitalWrite(CS,HIGH);
  delay(5);
}

/*
 * Wipes the complete Chip with zeros --Debug--
 */
void MC25XX01::wipeChip(){
  for(uint8_t i=0; i<128; i++){
   writeByte(0,i); 
  }
}

/*
 * Sends a single Instruction to the Chip
 */
void MC25XX01::sendInstruction(uint8_t inst){
  digitalWrite(CS,LOW);
  digitalWrite(HOLD,HIGH);
  SPI.transfer(inst);
  digitalWrite(CS,HIGH);
}
