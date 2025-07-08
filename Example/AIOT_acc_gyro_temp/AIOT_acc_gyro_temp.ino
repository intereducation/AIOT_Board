#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>
#include "SensorQMI8658.hpp"

#define USE_WIRE

#ifndef SENSOR_SDA
#define SENSOR_SDA  4
#endif

#ifndef SENSOR_SCL
#define SENSOR_SCL  5
#endif

#ifndef SENSOR_IRQ
#define SENSOR_IRQ  -1
#endif

#define IMU_CS                      5

SensorQMI8658 qmi;

IMUdata acc;
IMUdata gyr;

void setup()
{
    Serial.begin(115200);
    while (!Serial);

#ifdef USE_WIRE
    //Using WIRE !!
    if (!qmi.begin(Wire, QMI8658_L_SLAVE_ADDRESS, SENSOR_SDA, SENSOR_SCL)) {
        Serial.println("Failed to find QMI8658 - check your wiring!");
        while (1) {
            delay(1000);
        }
    }
#else
    if (!qmi.begin(IMU_CS)) {
        Serial.println("Failed to find QMI8658 - check your wiring!");
        while (1) {
            delay(1000);
        }
    }
#endif

    /* Get chip id*/
    Serial.print("Device ID:");
    Serial.println(qmi.getChipID(), HEX);

    qmi.configAccelerometer(
        SensorQMI8658::ACC_RANGE_4G,
        SensorQMI8658::ACC_ODR_1000Hz,
        SensorQMI8658::LPF_MODE_0,
        // selfTest enable
        true);


    qmi.configGyroscope(
        SensorQMI8658::GYR_RANGE_64DPS,
        SensorQMI8658::GYR_ODR_896_8Hz,
        SensorQMI8658::LPF_MODE_3,
        // selfTest enable
        true);

    // In 6DOF mode (accelerometer and gyroscope are both enabled),
    // the output data rate is derived from the nature frequency of gyroscope
    qmi.enableGyroscope();
    qmi.enableAccelerometer();
    // Print register configuration information
    qmi.dumpCtrlRegister();

    Serial.println("Read data now...");
}

void loop()
{

    if (qmi.getDataReady()) {
        if (qmi.getAccelerometer(acc.x, acc.y, acc.z)) {
            Serial.print("{ACCEL: ");
            Serial.print(acc.x);
            Serial.print(",");
            Serial.print(acc.y);
            Serial.print(",");
            Serial.print(acc.z);
            Serial.println("}");
        }
        if (qmi.getGyroscope(gyr.x, gyr.y, gyr.z)) {
            Serial.print("{GYRO: ");
            Serial.print(gyr.x);
            Serial.print(",");
            Serial.print(gyr.y );
            Serial.print(",");
            Serial.print(gyr.z);
            Serial.println("}");
        }
        Serial.printf("\t\t\t\t > %lu  %.2f *C\n", qmi.getTimestamp(), qmi.getTemperature_C());
    }
    delay(100);
}



