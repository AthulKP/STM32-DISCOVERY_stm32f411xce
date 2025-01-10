# Basic delay generation
In this specific example, the General Purpose Timer (Timer 4) was used to generate a delay in milliseconds, which is used to blink the green LED (PD 12) on board. The Timer delay in mapped to the NVIC inturrupt so that the main code run and when the counter reaches the predefined value interrupt is triggered. To verify whether the system in is non-blocking mode, the user button press will toggle the on board orange led status.   \
[More about STM32 board](https://www.st.com/resource/en/user_manual/um1842-discovery-kit-with-stm32f411ve-mcu-stmicroelectronics.pdf)
