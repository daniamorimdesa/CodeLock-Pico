#  Hardware Specifications

##  Block Diagram
(media/block diagram.jpg)


##  Hardware Components
| Component        | Description |
|-----------------|-------------|
| Raspberry Pi Pico | Microcontroller |
| SSD1306 OLED Display | User feedback |
| 4x4 Keypad | User input for password |
| SG90 Servo Motor | Controls the safe lock |
| Buzzer | Sound alerts |
| LEDs (Green/Red) | Status indicators |

##  Pin Configuration
| Component | Pin(s) | Function |
|-----------|--------|----------|
| Keypad Rows | 28, 27, 26, 22 | Output |
| Keypad Columns | 21, 20, 19, 18 | Input |
| OLED Display | SDA (4), SCL (5) | I2C Communication |
| Servo Motor | GPIO 15 | Lock Control |
| Buzzer | GPIO 1 | Sound Alerts |
| Green LED | GPIO 17 | Safe Open Indicator |
| Red LED | GPIO 16 | Error/Lock Indicator |

##  Circuit Schematic
(Include an image or link to the schematic)

