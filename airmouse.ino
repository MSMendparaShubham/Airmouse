#include <Wire.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <BleMouse.h>

Adafruit_MPU6050 mpu;
BleMouse bleMouse("ESP32 Air Mouse", "GSN Creation", 100);

const int leftButtonPin  = 25;  
const int rightButtonPin = 26;

void setup() {
  Serial.begin(115200);

  pinMode(leftButtonPin, INPUT_PULLUP);
  pinMode(rightButtonPin, INPUT_PULLUP);

  Wire.begin();
  if (!mpu.begin()) {
    Serial.println("MPU6050 not found!");
    while (1);
  }

  bleMouse.begin();

  // Configure sensitivity
  mpu.setAccelerometerRange(MPU6050_RANGE_4_G);
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
}

void loop() {
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  if (bleMouse.isConnected()) {
    // Gyro values give smooth pointer control
    int moveX = g.gyro.x * 8;   // adjust 8 → sensitivity
    int moveY = g.gyro.y * -8;

    bleMouse.move(moveX, moveY);

    // Left click
    if (!digitalRead(leftButtonPin)) {
      bleMouse.press(MOUSE_LEFT);
    } else {
      bleMouse.release(MOUSE_LEFT);
    }

    // Right click
    if (!digitalRead(rightButtonPin)) {
      bleMouse.press(MOUSE_RIGHT);
    } else {
      bleMouse.release(MOUSE_RIGHT);
    }
  }

  delay(10);  // Small delay to stabilize motion
}
