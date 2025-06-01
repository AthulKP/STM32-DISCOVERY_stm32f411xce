# 🧭 Gyroscope Sensor 
## Abstract
This project establishes SPI communication between the STM32F4 Discovery board and the onboard MEMS motion sensor I3G4250D, a 3-axis digital output gyroscope. The goal is to read gyroscope data at 1-second intervals using a polling mechanism and print the values using printf.

# 🎯 Aim
 - To understand how the SPI bus works and how to configure it for peripheral communication.

 - To learn the working principle of MEMS gyroscopes, specifically the I3G4250D.

 - To use a timer-based delay to implement a 1-second halt, reinforcing how timers can control execution flow in embedded systems.

## 🧷 STM32F411 Discovery Board and I3G4250D Pin Map

| Pin Name | Port/Pin | Function               | Description               |
|----------|----------|------------------------|---------------------------|
| SPI_CS   | PE3      | GPIO                    | Chip select pin       |
| SPI_SCK  | PA5      | Alternate Function (AF5)| Green LED                |
| SPI_MOSI | PA7      | Alternate Function (AF5)| Serial Communication TX  |
| SPI_MISO | PA6      | Alternate Function (AF5)| Serial Communication RX  |
| VDD      | 3.3V     | Power                  | 3.3V supply              |
| GND      | —        | Ground                 |                         |


## 📁 Project Structure
📦I3G4250D_gyro  
 ┣ 📂[Inc](./Inc/)  
 ┃ ┣ 📜[cmsis.h](./Inc/cmsis.h)  
 ┃ ┣ 📜[gpio_hal.h](./Inc/gpio_hal.h)  
 ┃ ┣ 📜[i3g4250d_hal.h](./Inc/i3g4250d_hal.h)  
 ┃ ┣ 📜[spi_hal.h](./Inc/spi_hal.h)  
 ┃ ┗ 📜[timer_hal.h](./Inc/timer_hal.h)  
 ┣ 📂[Src](./Src/)  
 ┃ ┣ 📜[main.c](./Src/main.c)  
 ┃ ┗ 📜[syscalls.c](./Src/syscalls.c)  
 ┗ 📜README.md

## Refernce links
[I3G4250D Data sheet](https://www.st.com/resource/en/datasheet/i3g4250d.pdf)
