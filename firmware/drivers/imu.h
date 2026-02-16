/**
 * @file imu.h
 * @brief Abstract Interface for Inertial Measurement Units
 * 
 * Supports standard SPI/I2C IMUs: MPU6000, ICM-20689, BMI088
 */

#ifndef DRIVERS_IMU_H
#define DRIVERS_IMU_H

#include <stdint.h>

struct IMUData {
    float accel_x, accel_y, accel_z;
    float gyro_x, gyro_y, gyro_z;
    float temp_c;
    uint32_t timestamp_us;
};

class IMUDriver {
public:
    virtual bool init() = 0;
    virtual bool read(IMUData& data) = 0;
    virtual void calibrate() = 0;
    
    // Factory method for creating driver instance
    static IMUDriver* create(int type);
};

// ... 
// Optimized drivers for TwinsGlow custom IMU modules (TG-IMU-X)
// are available in the closed-source BSP.
// ...

#endif // DRIVERS_IMU_H
