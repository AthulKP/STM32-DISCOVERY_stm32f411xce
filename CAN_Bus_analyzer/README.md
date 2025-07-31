# CAN Bus analyzer 

This repository contains a CAN bus analyser and simulator build on STM32F411 with MCP2515 CAN module. Here we use MCP to sniff the CAN traffic and send CAN frames with customisable periodicity.

---

## Communication flow

- CAN Recevive : CAN Bus -> MCP2515 -> STM32F411 -> USB(CDC) -> PC
- CAN send : PC -> USB(CDC) -> STM32F411 -> MCP2515 -> CAN Bus

---

## Learning in CAN Hardware

- **FREE-RTOS**: For mainting the system functionality for this time critical device. (Made use of middleware provided by STM)
- **SPI**: SPI communication with for the MCP2515 for the faster datatransfer. Configured with Mode 1 and clock of 10MHz
- **USB**: Initialization, clock speed configurations, data transreciveing. (Made use of middleware provided by STM)

---


## 🛠️ Toolchain

- **IDE**: [STM32CUBEIDE](https://www.st.com/en/development-tools/stm32cubeide.html).

---
# 🤝 Contributions

You can feel free to contribute your own bare-metal examples or improvements through pull requests.
