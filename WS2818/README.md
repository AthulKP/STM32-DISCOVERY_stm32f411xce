# Basic USART data TX 
In this specific example, made use of the PWM and DMA for interfacing the WS2818 addresable led.
PWM - Act as the communiccation protocol
DMA - For controlling the PWm duty cycle i.e. the data bits
WS2818 uses the signal high period for interpreting the data which resembles to the duty cycle in PWM, so if we create a 800KHz PWM of which if we set the duty cycle = 60% (0.75 µs) will make LED interpret it as bit 1 and duty cycle = 30% (0.375 µs)will interpret as bit 0.
# Connection diagram
![Alt text](connection.png)
\
| STM 32  | WS2818 |
| ------- | ------ |
| 5V      | VCC    |
| GND     | GND    |
| PC6     | DIN    |
\
[More about STM32 board](https://www.st.com/resource/en/user_manual/um1842-discovery-kit-with-stm32f411ve-mcu-stmicroelectronics.pdf)
\
[More about WS2818 LED](https://www.tme.com/Document/1d930d9b83e8cce43e5d1c490ab0fbe8/WS2818A.pdf)


