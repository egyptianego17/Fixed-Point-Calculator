# Fixed-Point-Calculator

The Enhanced AVR Calculator is a project that enables accurate calculation and display of floating-point numbers on an LCD using AVR microcontrollers. It addresses the limitations and inconsistencies associated with floating-point arithmetic on AVR microcontrollers, providing a reliable solution for applications requiring precise floating-point calculations and reliable display of the results.

# Problem

AVR microcontrollers have limited support for floating-point arithmetic, which can lead to inaccurate calculations and inconsistent results when working with floating-point numbers. Additionally, displaying floating-point numbers on an LCD screen can pose challenges in terms of accuracy and precision.

# Solution

The Enhanced AVR Calculator project solves the aforementioned problem by implementing the following key features:

1-Fixed-Point Arithmetic: The calculator utilizes fixed-point arithmetic instead of floating-point arithmetic for calculations. Fixed-point arithmetic represents decimal numbers as integers, avoiding the limitations and inconsistencies associated with floating-point calculations on AVR microcontrollers.

2-String Conversion: The project includes functions to convert fixed-point numbers to strings for display on the LCD. These conversion functions handle scaling and formatting, ensuring accurate representation and appropriate decimal precision. The numbers are displayed in a user-friendly format on the LCD.

3-Error Handling: Robust error handling mechanisms are incorporated to handle exceptional cases, such as division by zero. When errors occur during calculation, informative error messages are displayed on the LCD, preventing incorrect or misleading results from being shown.

4-LCD Display: The project interfaces with an LCD display to provide a clear and readable output of the calculated results. The LCD accurately represents the calculated fixed-point numbers with the desired decimal precision, enabling users to obtain precise results.

# Usage

To use the Enhanced AVR Calculator, follow these steps:

1-Set up your AVR microcontroller environment and ensure that the necessary libraries are included (avr/io.h, util/delay.h, stdlib.h, string.h, stdio.h, lcd_driver.h, keypad.h).

2-Connect the LCD display to the AVR microcontroller according to the specified pin connections.

3-Compile and upload the project code to your AVR microcontroller.

4-Power on the system and interact with the calculator using the keypad.

5-Enter the operands and the desired operator (+, -, *, /).

6-Press '=' to calculate the result. The calculated result will be displayed on the LCD.

7-Press 'C' to clear the calculator and start a new calculation.

# Contributions

Contributions to the Enhanced AVR Calculator project are welcome! If you encounter any issues, have ideas for improvements, or want to add new features, please submit a pull request. Ensure that your code adheres to the project's coding style and guidelines.
