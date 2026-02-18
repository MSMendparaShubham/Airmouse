# AirMouse 🖱️🖐️

AirMouse is a high-performance, hardware-based spatial computing interface. It utilizes an **MPU6050 6-axis motion tracking sensor** and an **ESP32 microcontroller** to translate hand tilts and movements into precise desktop mouse actions wirelessly.

Unlike camera-based systems (OpenCV/MediaPipe), AirMouse provides **zero-latency**, surface-independent control that works in any lighting condition.

## 🚀 Key Features

- **Hardware Precision**: Sub-degree accuracy for smooth, jitter-free cursor tracking.
- **Wireless Freedom**: Uses Bluetooth HID (Human Interface Device) to pair with any PC/Laptop — no drivers required.
- **Cross-Platform**: Works natively on Windows, macOS, Linux, and Android.
- **Presentation Mode**: Control slides and pointers from up to 10 meters away.
- **Low Power**: Optimized for long-running sessions with ESP32 deep sleep support.

## 🛠️ Hardware Requirements

- **Microcontroller**: ESP32 DevKit V1 (or compatible)
- **Sensor**: MPU6050 (Accelerometer + Gyroscope)
- **Input**: Tactile Push Button (for clicks)
- **Misc**: Jumper Wires, Breadboard, Micro-USB Cable

## 🔌 Wiring Diagram

| MPU6050 Pin | ESP32 Pin | Note |
| :--- | :--- | :--- |
| **VCC** | 3.3V | ⚠️ Do not use 5V! |
| **GND** | GND | Common Ground |
| **SDA** | GPIO 21 | I2C Data |
| **SCL** | GPIO 22 | I2C Clock |
| **INT** | - | N/C (Optional) |

*The Click Button should be connected between **GPIO 0 (Boot Button)** and **GND**.*

## 💻 Software Setup

### Prerequisites
1. Install **Arduino IDE**.
2. Install the **ESP32 Board Package**.
3. Install the following libraries via Library Manager:
   - `ESP32-BLE-Mouse` by T-vK
   - `Adafruit MPU6050`
   - `Adafruit Unified Sensor`

### Installation
1. Open `airmouse.ino` in Arduino IDE.
2. Select your ESP32 board (`DOIT ESP32 DEVKIT V1`).
3. Compile and Upload to your device.
4. Scan for Bluetooth devices on your PC/Laptop and connect to **"AirMouse"**.

## 👥 The Team

- **Mendpara Shubham**
- **Nisarg Makwana**
- **Hardik Parmar**

## 📜 License

This project is open-source and available under the [MIT License](LICENSE).

---
Developed by **MS-Media**
