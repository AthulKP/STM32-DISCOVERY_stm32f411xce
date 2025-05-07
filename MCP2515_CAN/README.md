# Basic MCP2515 CAN driver code 
## Current configuration :
- CAN bus speed fixed to 500kbps
- MCP clock set to 16MHz
- CAN send: both standard ID and extended ID
- CAN receive: both standard ID and extended ID\
## PinMap :
| STM Pin       | MCP Pin       |
| ------------- |:-------------:|
| VCC           | 5v            |
| GND           | GND           |
| PD8           | CS            |
| PB14          | SO (MISO)     |
| PB15          | SI (MOSI)     |
| PB13          | SCK           |
| PD8           | INT           |

[More about STM32F411CE ](https://www.st.com/resource/en/reference_manual/rm0383-stm32f411xce-advanced-armbased-32bit-mcus-stmicroelectronics.pdf)\
[More about MCP2515 ](https://ww1.microchip.com/downloads/en/DeviceDoc/MCP2515-Stand-Alone-CAN-Controller-with-SPI-20001801J.pdf)


