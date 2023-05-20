#ifndef LCD_DRIVER_H
#define LCD_DRIVER_H

#include <inttypes.h>
#include <avr/io.h>
#include <util/delay.h>

#define LCD_Dir  DDRB
#define LCD_Port PORTB
#define RS PB0
#define EN PB1

void LCD_Command(unsigned char cmnd);
void LCD_Char(unsigned char data);
void LCD_Init(void);
void LCD_String(char *str);
void LCD_String_xy(char row, char pos, char *str);
void LCD_Clear(void);

#endif // LCD_DRIVER_H