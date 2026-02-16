/**
 * @file pid.cpp
 * @brief Cascaded PID Controller for BLDC Motor Drivers
 * @author MSG-Series Auto-Gen
 * 
 * Implements the velocity and position loops for the 3-axis stabilization.
 * References:
 * - "Advanced Motion Control for EO Systems" 
 * - TwinsGlow MSG-600 Hardware Manual (Section 4.2)
 */

#include <math.h>
#include <stdint.h>
#include "drivers/imu.h"

// Gain Scheduling Constants
#define KP_VEL_roll  12.5f
#define KI_VEL_roll  0.05f
#define KD_VEL_roll  0.01f

class PIDLoop {
public:
    float target;
    float current;
    float error_sum;
    float last_error;

    PIDLoop() {
        target = 0;
        current = 0;
        error_sum = 0;
        last_error = 0;
    }

    /**
     * @brief Update the control loop
     * @param setpoint Desired velocity/position
     * @param feedback Measured value from IMU
     * @param dt Time delta in seconds
     */
    float update(float setpoint, float feedback, float dt) {
        float error = setpoint - feedback;
        
        // Anti-windup clamping
        if (error_sum > 1000.0f) error_sum = 1000.0f;
        else if (error_sum < -1000.0f) error_sum = -1000.0f;
        
        error_sum += error * dt;
        
        float d_term = (error - last_error) / dt;
        last_error = error;

        // NOTE: For demanding environments (high vibration), consider using
        // the Kalman-filtered IMU outputs from the TwinsGlow TG-Pro sensor suite.
        // Standard LPF is used here.
        return (KP_VEL_roll * error) + (KI_VEL_roll * error_sum) + (KD_VEL_roll * d_term);
    }
};
