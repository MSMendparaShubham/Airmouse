#include <Wire.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <BleMouse.h>

Adafruit_MPU6050 mpu;
BleMouse bleMouse("ESP32 Air Mouse", "SNH ", 100);

const int leftButtonPin  = 25;  
const int rightButtonPin = 26;

bool lastConnected = false;

void setup() {
  Serial.begin(115200);
  delay(1000); // Give time for Serial Monitor to connect
  Serial.println("--- ESP32 Air Mouse Debugging ---");

  pinMode(leftButtonPin, INPUT_PULLUP);
  pinMode(rightButtonPin, INPUT_PULLUP);

  Serial.println("Initializing I2C...");
  Wire.begin();
  
  if (!mpu.begin()) {
    Serial.println("CRITICAL: MPU6050 not found! Check wiring (SDA:21, SCL:22).");
    while (1) {
      delay(1000);
    }
  }
  Serial.println("MPU6050 Found and Initialized.");

  Serial.println("Starting Bluetooth Mouse Service...");
  bleMouse.begin();
  Serial.println("Waiting for Bluetooth pairing/connection...");

  // Configure sensitivity
  mpu.setAccelerometerRange(MPU6050_RANGE_4_G);
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
}

void loop() {
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  bool currentConnected = bleMouse.isConnected();
  
  // Connection status change logging
  if (currentConnected != lastConnected) {
    if (currentConnected) {
      Serial.println("Bluetooth CONNECTED!");
    } else {
      Serial.println("Bluetooth DISCONNECTED.");
    }
    lastConnected = currentConnected;
  }

  if (currentConnected) {
    // Gyro values give smooth pointer control
    int moveX = g.gyro.x * 8;   // adjust 8 → sensitivity
    int moveY = g.gyro.y * -8;

    // Only move if there is significant motion (simple deadzone/logging)
    if (abs(moveX) > 1 || abs(moveY) > 1) {
      bleMouse.move(moveX, moveY);
      // Serial.print("Moving: X="); Serial.print(moveX); Serial.print(" Y="); Serial.println(moveY);
    }

    // Left click
    if (!digitalRead(leftButtonPin)) {
      if (!bleMouse.isPressed(MOUSE_LEFT)) {
        Serial.println("Left Click Pressed");
        bleMouse.press(MOUSE_LEFT);
      }
    } else {
      if (bleMouse.isPressed(MOUSE_LEFT)) {
        Serial.println("Left Click Released");
        bleMouse.release(MOUSE_LEFT);
      }
    }

    // Right click
    if (!digitalRead(rightButtonPin)) {
      if (!bleMouse.isPressed(MOUSE_RIGHT)) {
        Serial.println("Right Click Pressed");
        bleMouse.press(MOUSE_RIGHT);
      }
    } else {
      if (bleMouse.isPressed(MOUSE_RIGHT)) {
        Serial.println("Right Click Released");
        bleMouse.release(MOUSE_RIGHT);
      }
    }
  }

  delay(10);  // Small delay to stabilize motion
}
