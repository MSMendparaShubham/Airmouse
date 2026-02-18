/*
  AirMouse | ESP32 + MPU6050 Motion Control
  A professional implementation for Bluetooth HID mouse control.
  
  Connections:
  - MPU6050 VCC -> ESP32 3.3V
  - MPU6050 GND -> ESP32 GND
  - MPU6050 SDA -> ESP32 GPIO 21
  - MPU6050 SCL -> ESP32 GPIO 22
  - Click Switch -> ESP32 GPIO 0 (Boot Button) to GND
*/

#include <BleMouse.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

// Initialize library instances
BleMouse bleMouse("AirMouse", "MS-Media", 100);
Adafruit_MPU6050 mpu;

// Configuration
const int clickPin = 0;        // Using Boot button for clicks
const float sensitivity = 15.0; // Adjust for cursor speed
const float deadzone = 0.05;   // Filter out small tremors

void setup() {
  Serial.begin(115200);

  // Initialize MPU6050
  if (!mpu.begin()) {
    Serial.println("Could not find MPU6050 chip! Check wiring.");
    while (1) delay(10);
  }

  // Configure Sensor
  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);

  // Setup Button
  pinMode(clickPin, INPUT_PULLUP);

  // Start Bluetooth Mouse
  bleMouse.begin();
  Serial.println("AirMouse Ready & Advertising...");
}

void loop() {
  if (bleMouse.isConnected()) {
    sensors_event_t a, g, temp;
    mpu.getEvent(&a, &g, &temp);

    // Translate Gyroscope Z and Y to Mouse X and Y
    float gx = g.gyro.z;
    float gy = g.gyro.y;

    // Apply movement if outside deadzone
    if (abs(gx) > deadzone || abs(gy) > deadzone) {
      int moveX = (int)(gx * sensitivity);
      int moveY = (int)(gy * sensitivity);
      bleMouse.move(moveX, moveY);
    }

    // Handle Left Click
    if (digitalRead(clickPin) == LOW) { // Button Pressed
      if (!bleMouse.isPressed(MOUSE_LEFT)) {
        bleMouse.press(MOUSE_LEFT);
      }
    } else { // Button Released
      if (bleMouse.isPressed(MOUSE_LEFT)) {
        bleMouse.release(MOUSE_LEFT);
      }
    }
  }
  
  delay(10); // Polling stability
}
