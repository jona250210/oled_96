//
// oled test program
//
// Written by Larry Bank
// Copyright 2017 BitBank Software, Inc. All Rights Reserved.
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//    http://www.apache.org/licenses/LICENSE-2.0
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//===========================================================================

#include <stdint.h>
/* #include <string.h> */
/* #include <stdio.h> */
#include "../printf/printf.h"
/* #include <stdlib.h> */
#include "oled96.h"
#include <unistd.h>
#include "../mmio.h"

const uint32_t CLK_FREQ = 12e6;

int main(int argc, char *argv[]) {
  int i, iChannel;
  int iOLEDAddr = 0x3c;        // typical address; it can also be 0x3d
  int iOLEDType = OLED_128x64; // Change this for your specific display
  int bFlip = 0, bInvert = 0;
  scl_ratio_set(scl_compute_ratio(CLK_FREQ, 100e3));

  /* const uint8_t oled64_initbuf[] = { */
  /*     0x00, 0xae, 0xa8, 0x3f, 0xd3, 0x00, 0x40, 0xa1, 0xc8, 0xda, 0x12, */
  /*     0x81, 0xff, 0xa4, 0xa6, 0xd5, 0x80, 0x8d, 0x14, 0xaf, 0x20, 0x02}; */

  /* const uint8_t* arr = oled64_initbuf; */
  /* uint8_t hmm = 0xAE; */
  /* printf("Hmm: %02X\r\n", hmm); */
  /* printf("Hmm2: %02X\r\n", arr[1] & 0x00FF); */

  /* while(1){} */
  i = -1;
  iChannel = -1;
  i = oledInit(iChannel, iOLEDAddr, iOLEDType, bFlip, bInvert);

  printf("Successfully opened I2C bus %d\r\n", iChannel);
  oledFill(0); // fill with black

  /* printf("Trying to write string 1\r\n"); */
  /* oledWriteString(0, 0, "OLED 123 Library!", FONT_NORMAL); */
  /* printf("Trying to write string 2\r\n"); */
  /* oledWriteString(3, 1, "BIG!", FONT_BIG); */
  /* printf("Trying to write string 3\r\n"); */
  /* oledWriteString(0, 1, "Small", FONT_SMALL); */
  for (i = 0; i < 64; i++) {
    oledSetPixel(i, 16 + i, 1);
    oledSetPixel(127 - i, 16 + i, 1);
  }
  printf("Press ENTER to quit\n");
  oledWriteString(0, 0, "               ", FONT_NORMAL);
  oledWriteString(0, 0, "1500.5 Hz", FONT_NORMAL);
  oledWriteString(0, 0, "1500.8 Hz", FONT_NORMAL);
  oledWriteString(0, 0, "1501.0 Hz", FONT_NORMAL);
  oledWriteString(0, 0, "1502.4 Hz", FONT_NORMAL);
  oledWriteString(0, 0, "1621.9 Hz", FONT_NORMAL);
  oledWriteString(0, 0, "END!     ", FONT_NORMAL);

  for(int i=0; i < 100; i++){
    char buf[20];
    sprintf_(buf, "i: %d", i);
    oledWriteString(0, 0, buf, FONT_NORMAL);
  }
  while (1) {
  };
  oledShutdown();
  return 0;
} /* main() */
