# Greenhouse Monitoring and Control System

This project is an Arduino-based greenhouse monitoring and control system. It utilizes various sensors and actuators to monitor and regulate the greenhouse environment, ensuring optimal conditions for plant growth.

## Components Used

1. **Arduino Board** (e.g., Arduino Uno)
2. **Temperature Sensor** (e.g., LM35)
3. **RGB LED** (for visual temperature indication)
4. **LCD Display** (I2C LCD, 16x2)
5. **Servos** (for window control)
6. **Relays** (for controlling external devices)
7. **Push Buttons** (for manual control)
8. **Resistors** and **Wires**

## Pin Configuration

### RGB LED
- Red: Pin 11
- Green: Pin 10
- Blue: Pin 9

### Relay
- Relay Pin: Pin 12

### Temperature Sensor
- Sensor Pin: A0

### Servos
- Left Servo: Pin 5
- Right Servo: Pin 6

### Buttons
- Left Servo Button: Pin 7
- Mode Change Button: Pin 4
- Right Servo Button: Pin 2

### LCD Display
- SDA: A4
- SCL: A5

## Custom Characters for LCD

- `Wopen`: Open window icon
- `Wclose`: Closed window icon
- `hot`: Hot temperature icon
- `cold`: Cold temperature icon
- `O` and `K`: Custom characters for additional indicators

## Functionality

### Modes of Operation

1. **Automatic Mode**
   - The system automatically controls the greenhouse windows based on the temperature.
   - If the temperature exceeds 30°C, the windows open.
   - If the temperature is below 30°C, the windows close.

2. **Manual Mode**
   - The user can manually control the windows using push buttons.

### Temperature-Based Actions

- **Above 40°C**: RGB LED turns Cyan (Green + Blue), relay remains off.
- **Between 25°C and 40°C**: RGB LED turns Magenta (Red + Blue), relay remains off.
- **Below 25°C**: RGB LED turns Yellow (Red + Green), relay is toggled on for 3 seconds.

### LCD Display

- The LCD displays the current temperature, mode, and window status.
- Custom icons indicate temperature range and window state.

## Code Explanation

### Setup Function

- Initializes the serial communication, LCD, buttons, servos, and RGB LED pins.
- Sets initial positions for servos and default display on the LCD.

### Loop Function

- Reads the temperature sensor and calculates the temperature in Celsius.
- Updates the LCD with the current temperature and window status.
- Handles mode changes and window operations based on the mode.
- Adjusts RGB LED color based on temperature.
- Controls the relay based on temperature conditions.

### LCD Display Function

- `printToLCD(float temperatureC, int window_L_position, int window_R_position)`
  - Updates the LCD with the current temperature and window status using custom icons.

## Usage

1. **Power the Arduino** and ensure all components are connected as per the pin configuration.
2. **Monitor the LCD display** for real-time temperature and window status updates.
3. **Use the push buttons** to switch between automatic and manual modes or to manually control the windows in manual mode.
4. **Observe the RGB LED** for a quick visual indication of the current temperature range.

## Circuit Diagram

(Include a schematic diagram showing connections between the Arduino, LCD, RGB LED, temperature sensor, relays, servos, and buttons.)
