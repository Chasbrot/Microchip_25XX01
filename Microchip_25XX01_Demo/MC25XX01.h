/*
   This file is part of the MC25XX01 Arduino Library.
   Copyright (c) 2019 Michael Selinger.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, version 3.

   This program is distributed in the hope that it will be useful, but
   WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
   General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program. If not, see <http://www.gnu.org/licenses/>.
*/

/* PINOUT
    CS   -|*  |- VCC
    MISO -|   |- HOLD
    WP   -|   |- SCK
    VSS  -|   |- SI

*/


#include<SPI.h>

// Instructions
#define READ  0x03
#define WRITE 0x02
#define WRDI  0x04
#define WREN  0x06
#define RDSR  0x05
#define WRSR  0x01

// Pins
#define WP    8
#define HOLD  7
#define CS    10

class MC25XX01 {
  public:
    uint8_t readByte(uint8_t address);
    uint8_t readSR();
    uint8_t * readNBytes(uint8_t start_address, uint8_t bytes);
    void writeSR(uint8_t data);
    void writeByte(uint8_t address, uint8_t data);
    void writePage(uint8_t start_address, uint8_t* data, uint8_t anz);
  private:
    void wipeChip();
    void sendInstruction(uint8_t inst);
};
