# 🔧 STM32F411 Discovery Projects (Bare-Metal / Register-Level)

This repository contains a collection of embedded systems projects built using the **STM32F411 Discovery board**, focused on **bare-metal development** by directly addressing hardware **registers** — no HAL, no libraries, just close-to-the-metal C code.

These projects explore the **ARM Cortex-M4** microcontroller architecture, built for performance, control, and a deep understanding of the **ARM M-class processor** internals.

---

## 🎯 Purpose

- To develop **hands-on embedded experience** with STM32F411 using **bare-metal C**.
- To gain a deep understanding of **ARM Cortex-M** architecture and **peripheral control** via direct register access.
- To create reusable examples for beginners and enthusiasts learning **low-level microcontroller programming**.

---

## 🧠 Key Concepts

- **Bare-metal programming**: No operating system or abstraction layers.
- **Direct register access**: Using memory-mapped I/O and register-level manipulation.
- **ARM Cortex-M4F**: Focused on the M-class core features such as NVIC, SysTick, and CMSIS.
- **Embedded peripherals**: GPIO, USART, SPI, I2C, Timers, EXTI, ADC, etc.

---

## 📁 Project Structure
📦32F411EDISCOVERY    
 ┣ 📂[I3G4250D_gyro](./I3G4250D_gyro)   
 ┣ 📂[Interrupt](./Interrupt)   
 ┣ 📂[LED_Blink](./LED_Blink)    
 ┣ 📂[LSM303AGR_accelero_magneto](./LSM303AGR_accelero_magneto)   
 ┣ 📂[MCP2515_CAN](./MCP2515_CAN/)    
 ┣ 📂[PWM_led_fading](./PWM_led_fading)    
 ┣ 📂[STM32 CAN bus analyzer tool](./STM32%20CAN%20bus%20analyzer%20tool/)    
 ┣ 📂[SYSCLK_PLL](./SYSCLK_PLL)  
 ┣ 📂[Timer](./Timer)    
 ┣ 📂[USART_serial_port](./USART_serial_port)    
 ┣ 📂[User_Push_Button](./User_Push_Button)    
 ┣ 📂[WS2818_addressable_led](./WS2818_addressable_led)    
 ┗ 📜README.md
 
Each folder represents an **independent project**, designed to be minimal and educational.

---

## 🛠️ Toolchain

- **IDE**: [STM32CUBEIDE](https://www.st.com/en/development-tools/stm32cubeide.html).

---

## 🚀 Getting Started

### 🔧 Prerequisites

- [STM32F411 Discovery Board](https://www.st.com/en/evaluation-tools/32f411ediscovery.html)
- USB to Micro USB cable


---
### 📚 Learning Focus
- ARM Cortex-M core registers and system control
- NVIC configuration and interrupt handling
- Bit-banding and memory-mapped I/O
- SysTick and custom delay functions
- GPIO toggling, button inputs, and debouncing
- Serial communication (UART, SPI, I2C)
- Peripheral clock and RCC configuration

---
# 🤝 Contributions

You can feel free to contribute your own bare-metal examples or improvements through pull requests.
