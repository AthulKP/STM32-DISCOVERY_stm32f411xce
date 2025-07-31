# 🚗 CAN Bus Analyzer & Simulator

This repository contains a **CAN bus analyzer and simulator** built on an **STM32F411** microcontroller interfaced with an **MCP2515 CAN module**. It can sniff CAN traffic and send custom CAN frames with configurable periodicity.

---

## 🔄 Communication Flow

- **CAN Receive**:  
  `CAN Bus → MCP2515 → STM32F411 → USB (CDC) → PC`

- **CAN Send**:  
  `PC → USB (CDC) → STM32F411 → MCP2515 → CAN Bus`

---

## 📚 Learning Highlights (CAN Hardware)

- **FreeRTOS**:  
  Used to manage system tasks and ensure real-time behavior. Middleware from ST was used for integration.

- **SPI**:  
  High-speed SPI communication with the MCP2515, configured in **SPI Mode 1** with a clock of **10 MHz** for fast and reliable data transfer.

- **USB CDC (Virtual COM Port)**:  
  Configured USB peripheral for serial communication with the PC. Includes clock configuration and USB data transfer (using ST-provided middleware).

---

## 🛠️ Toolchain

- **IDE**: [STM32CubeIDE](https://www.st.com/en/development-tools/stm32cubeide.html)

---

## 🤝 Contributions

Contributions are welcome!  
Feel free to submit pull requests with improvements, bug fixes, or your own **bare-metal** implementations.

---

## 📄 License

This project is open-source. You can choose to add a license such as [MIT](https://opensource.org/licenses/MIT), GPL, or any other, depending on your preference.

---

## 🧑‍💻 Author

[Your Name] – *Feel free to include your contact, GitHub profile, or LinkedIn*

