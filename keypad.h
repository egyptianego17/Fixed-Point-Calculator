#ifndef KEYPAD_H
#define KEYPAD_H

#include <inttypes.h>
#include <avr/io.h>
#include <util/delay.h>

#define ROWS    4
#define COLS    4

void keypad_init(void);
uint8_t keypad_scan(void);

#endif // KEYPAD_H