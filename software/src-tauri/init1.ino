#include <Mouse.h>
#include <Keyboard.h>
#include <U8g2lib.h>
#include <SPI.h>
#include <Wire.h>

bool trig = false;

int PIEZO = 6;

int layer = 1;
int maxLayer = 4;

String active = "";

char table[4][4] = {
  {'A', 'B', 'C', 'D'},
  {'E', 'F', 'G', 'H'},
  {'I', 'J', 'K', 'L'},
  {'M', 'N', 'O', 'P'}
};

U8G2_SSD1306_128X64_NONAME_F_4W_SW_SPI u8g2(U8G2_R0, 15, 14, 9, 10, 16); //[full framebuffer, size = 1024 bytes]

// SECTION - PROGRAM EDITABLE - DO NOT EDIT THIS COMMENT
