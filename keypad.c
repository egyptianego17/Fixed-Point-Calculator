#include "keypad.h"

// Configure the row pins as output and column pins as input
void keypad_init(void) {
    DDRA |= (1 << PA0) | (1 << PA1) | (1 << PA2) | (1 << PA3); // Set row pins as outputs
    DDRA &= ~((1 << PA4) | (1 << PA5) | (1 << PA6) | (1 << PA7)); // Set column pins as inputs
    PORTA |= (1 << PA4) | (1 << PA5) | (1 << PA6) | (1 << PA7); // Enable pull-up resistors on column pins
}

// Scan the keypad and return the pressed key (0xFF if no key pressed)
uint8_t keypad_scan(void) {
    const char keys[ROWS][COLS] = {{'7', '8', '9', '/'},
                                   {'4', '5', '6', '*'},
                                   {'1', '2', '3', '-'},
                                   {'C', '0', '=', '+'}};
    uint8_t row, col;

    for (row = 0; row < ROWS; row++) {
        // Activate the current row
        PORTA = (PORTA & 0xF0) | (~(1 << row) & 0x0F);

        // Check each column for a key press
        for (col = 0; col < COLS; col++) {
            if (!(PINA & (1 << (col + 4)))) {
                // Debounce the key press
                _delay_ms(200);
                if (!(PINA & (1 << (col + 4)))) {
                    return keys[row][col];
                }
            }
        }
    }

    return 0xFF; // No key pressed
}