#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "lcd_driver.h"
#include "keypad.h"

// Enumeration for calculator states
typedef enum { INPUT_1, INPUT_2, RESULT } State;

// Define maximum input length and LCD line width
#define MAX_INPUT_LENGTH 10
#define LCD_LINE_WIDTH 16

// Function to check if a character is a valid input
int is_valid_input_char(char c) {
    return (c >= '0' && c <= '9') || c == '.' || c == '-';
}

// Function to convert string to fixed-point number
int64_t str_to_fixed_point(const char *str) {
    int64_t result = 0;
    int8_t sign = 1;
    uint8_t decimal = 0;
    const char *c = str;

    // Check if the number is negative
    if (*c == '-') {
        sign = -1;
        c++;
    }

    // Iterate through the string
    while (*c) {
        // Handle the decimal point
        if (*c == '.') {
            decimal = 1;
            c++;
            continue;
        }

        // Update the result
        result *= 10;
        result += (*c - '0');

        // Update the decimal point position
        if (decimal) {
            decimal++;
        }
        c++;
    }

    // Adjust the result based on the position of the decimal point
    if (decimal == 2) {
        result *= 10;
    } else if (decimal == 0) {
        result *= 100;
    }

    return sign * result;
}

// Function to convert fixed-point number to string
void fixed_point_to_str(int32_t num, char *str) {
    int32_t whole = num / 100;
    int32_t remainder = abs(num % 100);
    if (remainder < 10) {
        snprintf(str, LCD_LINE_WIDTH, "%ld.0%ld", whole, remainder);
    } else {
        snprintf(str, LCD_LINE_WIDTH, "%ld.%02ld", whole, remainder);
    }
}

int main(void) {
    LCD_Init(); /* Initialization of LCD */
    keypad_init();
    State state = INPUT_1;
    char operand1[MAX_INPUT_LENGTH + 1] = {0};
    char operand2[MAX_INPUT_LENGTH + 1] = {0};
    char operator = '\0';
    uint8_t operand1_index = 0;
    uint8_t operand2_index = 0;
    uint8_t key;

    // Main loop
    while (1) {
        key = keypad_scan();
        if (key != 0xFF) {
            switch (state) {
                case INPUT_1:
                    // Handle valid input characters
                    if (is_valid_input_char(key) && (key != '-' || operand1_index == 0) && operand1_index < MAX_INPUT_LENGTH) {
                        operand1[operand1_index++] = key;
                    }
                    // Handle the "C" button
                    else if (key == 'C') {
                        LCD_Clear();
                        state = INPUT_1;
                        operand1_index = 0;
                        operand2_index = 0;
                        memset(operand1, 0, sizeof(operand1));
                        memset(operand2, 0, sizeof(operand2));
                        operator = '\0';
                        continue;
                    }
                    // Handle operators
                    else if (key == '+' || key == '-' || key == '*' || key == '/') {
                        if (operand1_index == 0) { // No valid input yet
                            break;
                        }
                        operator = key;
                        state = INPUT_2;
                    }
                    break;

                case INPUT_2:
                    // Handle valid input characters
                    if (is_valid_input_char(key) && (key != '-' || operand2_index == 0) && operand2_index < MAX_INPUT_LENGTH) {
                        operand2[operand2_index++] = key;
                    }
                    // Handle the "=" button
                    else if (key == '=') {
                        if (operand2_index == 0) { // No valid input yet
                            break;
                        }
                        int32_t result = 0;
                        int32_t num1 = str_to_fixed_point(operand1);
                        int32_t num2 = str_to_fixed_point(operand2);

                        // Perform the calculation
                        switch (operator) {
                            case '+':
                                result = num1 + num2;
                                break;
                            case '-':
                                result = num1 - num2;
                                break;
                            case '*':
                                result = (num1 * num2) / 100;
                                break;
                            case '/':
                                if (num2 != 0) {
                                    result = (num1 * 100) / num2;
                                } else {
                                    LCD_Clear();
                                    LCD_String("Cannot divide by 0");
                                    _delay_ms(2000);
                                    break;
                                }
                                break;
                            default:
                                break;
                        }
                        // Display the result
                        LCD_Clear();
                        LCD_String(operand1);
                        LCD_Char(operator);
                        LCD_String(operand2);
                        LCD_Char('=');
                        char result_str[LCD_LINE_WIDTH] = {0};
                        fixed_point_to_str(result, result_str);

                        // Check the remaining space on the first line
                        uint8_t remaining_space = LCD_LINE_WIDTH - (strlen(operand1) + 1 + strlen(operand2) + 1);
                        if (strlen(result_str) > remaining_space) {
                            // Move to the second line if the result is too long
                            LCD_Command(0xC0); // Move the cursor to the second line
                        }
                        LCD_String(result_str);
                        state = RESULT;
                    }
                    break;

                case RESULT:
                    // Reset the calculator state and clear the LCD
                    operand1_index = 0;
                    operand2_index = 0;
                    memset(operand1, 0, sizeof(operand1));
                    memset(operand2, 0, sizeof(operand2));
                    operator = '\0';
                    state = INPUT_1;
                    LCD_Clear();
                    continue;
            }
            // Display the key press if not in RESULT state
            if (state != RESULT) {
                LCD_Char(key);
            }
        }
    }

    return 0;
}
