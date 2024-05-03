#ifndef DISPLAY_H
#define DISPLAY_H

#include <TFT_eSPI.h> // Hardware-specific library
#include <SPI.h>


void initialize_screen(void);
//static uint8_t conv2d(const char* p);
void update_screen(int hh, int mm, int ss);

#endif
