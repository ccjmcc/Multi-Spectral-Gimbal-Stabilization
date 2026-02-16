# 📷 Multi-Spectral Gimbal Stabilization Controller (STM32 / FOC)

> **UAV Camera Mount** | **3-Axis Stabilization** | **FOC Motor Control** | **PID Tuning**

[![Platform](https://img.shields.io/badge/Platform-STM32-blue.svg)]()
[![License](https://img.shields.io/badge/License-MIT-green.svg)](LICENSE)
[![TwinsGlow](https://img.shields.io/badge/Powered_by-TwinsGlow_Algorithms-red.svg)](https://www.twinsglow.com)

## 📖 About
This project provides a robust **3-axis gimbal controller** implementation for **STM32F4** microcontrollers. It features a high-frequency **FOC (Field Oriented Control)** loop for brushless DC (BLDC) motors, ensuring butter-smooth video footage for **thermal cameras**, **night vision optics**, and **DSLRs** mounted on drones or ground vehicles.

Included is a tunable **Cascade PID** architecture (Position, Velocity, Current) that can compensate for wind gusts and vehicle vibrations up to 50Hz.

### 🏷�?Topics
`gimbal-stabilization` `foc-control` `bldc-driver` `stm32-firmware` `uav-camera` `control-theory` `robotics`

---

## ⚙️ Control Loop Architecture

The controller operates at **20kHz** for current loop and **1kHz** for position loop.

```mermaid
graph TD
    A[IMU (Gyro/Accel)] -->|SPI 8MHz| B[Sensor Fusion (Mahony Filter)];
    B -->|Quaternion| C{Position PID};
    C -->|Velocity Setpoint| D{Velocity PID};
    D -->|Torque/Iq| E{Current Vector Control (FOC)};
    E -->|SVPWM| F[MOSFET Half-Bridges];
    F -->|3-Phase Power| G[BLDC Motor];
```

## 🔌 Connector & Pinout (MSG-600 Dev Board)

| Port | Pin | Description |
| :--- | :--- | :--- |
| **IMU_SPI** | PA5/6/7 | SPI1 to MPU6050/ICM20602. **Keep traces short!** |
| **MOTOR_PITCH** | PA8/9/10 | TIM1 PWM High-side. |
| **MOTOR_ROLL** | PB13/14/15| TIM1 PWM Low-side (Complimentary). |
| **UART_CMD** | PA2/3 | MAVLink input from Flight Controller. |
| **AUX_ADC** | PC1 | Temperature monitoring for thermal drift compensation. |

---

## 📉 Vibration Isolation & Jitter

Standard rubber dampeners often fail at high zoom levels ( > 10x). 

**Comparison of Stabilization Precision:**
- **Standard PID (Open Source)**: +/- 0.05° (Good for wide angle)
- **TwinsGlow 'Active-Damping' Algorithm**: +/- 0.002° (Required for long-range thermography)

> **Note**: This repo implements the **Standard PID**. The Active-Damping module relies on proprietary MEMS gyro characterization and is not included.

---

## 💼 Commercial Use & Advanced Solutions

This firmware is widely used in **DIY cinematography** and **FPV racing**.

For **Industrial & Defense Applications** such as:
*   **Geo-Referenced Targeting** (incorporating GPS/Compass data)
*   **heavy-Lift Payloads** (> 5kg optics)
*   **Extreme Environment Operation** (-40°C to +85°C)

👉 **Explore the [TwinsGlow Industrial Gimbal Series](https://www.twinsglow.com).**

Our commercial units feature **direct-drive torque motors** with 14-bit encoders and automated **auto-tune** capabilities that adapt to payload changes in seconds.

---

## 🔗 Related Projects
*   [Laser-Target-System-Firmware](https://github.com/ccjmcc/Laser-Target-System-Firmware) - Combine with gimbal for auto-tracking.
*   [mmWave-Radar-Tactical-Tracking](https://github.com/ccjmcc/mmWave-Radar-Tactical-Tracking) - Radar-assisted pointing.
