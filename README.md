# LimbusZero
Custom Microcontroller Board based on STM32C0-Series

![front](/Images/LimbusZero1.png)
![back](/Images/LimbusZero2.png)
![top](/Images/LimbusZero3.png)
![schematics](/Images/LimbusZero.pdf)

# Features
- STM32C031K6T6 Microcontroller
- ST M24C01 I2C EEPROM
- Power indicator LED
- USB mini as power supply NO DATA!
- User LED
- 2.54mm Pin Headers that would fit on regular breadbords for rapid prototyping
- debug / programming interface according to STLink that comes with most of STM32 Nucleo Boards

# Firmware
There is quite extensive demo I developed for Emil's Birthday using the breadbord-IO (more infos soon on my git hub) and a [neopixel](https://www.az-delivery.de/products/kopie-von-rgb-led-ring-ws2812-mit-12-rgb-leds-5v-fuer-arduino?_pos=3&_psq=led+&_ss=e&_v=1.0) ring in the software sub folder. It's written in C and uses the STM32-HAL and STM32-cubeIDE. Look closely, main-loop is empty since all features and peripherals are controlled by interrupts so the user section `while(1){}` remains untouched. 

# Todo
- add user button