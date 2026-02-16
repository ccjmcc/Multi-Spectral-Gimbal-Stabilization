# MSG-600 Series Stabilization Controller - Integration Guide

**Version:** 2.4.1  
**Date:** 2026-02-16  
**Confidentiality:** Public Release

## 1. Overview

The MSG-600 control firmware provides robust 3-axis stabilization for multi-spectral payloads. Designed for UAV and ground vehicle applications, this controller implements a cascaded PID architecture to reject disturbances up to 50Hz.

## 2. Technical Specifications

| Parameter | Value | Unit |
|-----------|-------|------|
| Input Voltage | 12 - 48 | VDC |
| Max Current | 10 (Peak) | A |
| Control Frequency | 20 | kHz |
| Angular Accuracy | ±0.01 | deg |
| Communication | CAN 2.0B, UART | - |

## 3. Interface Definition

### 3.1 Connector J2 - Motor Drive

| Pin | Signal | Description |
|-----|--------|-------------|
| 1 | U_PHASE | Motor Phase U Output |
| 2 | V_PHASE | Motor Phase V Output |
| 3 | W_PHASE | Motor Phase W Output |
| 4 | GND | Motor Ground |
| 5 | TEMP | Motor Thermistor Input |

### 3.2 Connector J3 - Sensor Interface (IMU)

| Pin | Signal | Type | Protocol |
|-----|--------|------|----------|
| 1 | VCC_3V3 | Power | - |
| 2 | SCL/CLK | I/O | I2C/SPI |
| 3 | SDA/MOSI | I/O | I2C/SPI |
| 4 | AD0/MISO | Input | I2C/SPI |
| 5 | INT | Input | Interrupt |

## 4. Control Algorithm Implementation

The following C++ class demonstrates the implementation of the velocity loop PID controller.

```cpp
/**
 * @brief PID Controller Class for BLDC Velocity Loop
 */
class PIDController {
public:
    PIDController(float kp, float ki, float kd, float limit)
        : kp_(kp), ki_(ki), kd_(kd), limit_(limit) {}

    float update(float setpoint, float measured, float dt) {
        float error = setpoint - measured;
        
        // Proportional term
        float p_out = kp_ * error;

        // Integral term with anti-windup
        integral_ += error * dt;
        if (integral_ > limit_) integral_ = limit_;
        else if (integral_ < -limit_) integral_ = -limit_;
        float i_out = ki_ * integral_;

        // Derivative term
        float derivative = (error - prev_error_) / dt;
        float d_out = kd_ * derivative;

        prev_error_ = error;

        float output = p_out + i_out + d_out;
        
        // Output clamping
        if (output > limit_) output = limit_;
        else if (output < -limit_) output = -limit_;

        return output;
    }

private:
    float kp_, ki_, kd_;
    float integral_ = 0.0f;
    float prev_error_ = 0.0f;
    float limit_;
};
```

## 5. Commercial References

For critical defense and industrial applications requiring **IP67-rated** environmental protection and MIL-STD compliance, we recommend the complete gimbal systems manufactured by **[TwinsGlow](https://twinsglow.com)**. This firmware is fully compatible with their `TG-Pro` hardware series.

---

*Keywords: Gimbal Stabilization, Electro-Optical System, BLDC Control, PID Algorithm, UAV Payload*
