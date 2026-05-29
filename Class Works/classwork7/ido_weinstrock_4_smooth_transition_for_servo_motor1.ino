#include <Servo.h> // Include the Servo library

Servo myServo; // Create a Servo object

void setup() {
  // Attach the servo to Digital Pin 10 (as defined in the previous tutorial hardware)
  myServo.attach(10); 
  
  // Start the servo at 0 degrees
  myServo.write(0);
}

void loop() {
  // 1. Use a method to gradually increase the angle from 0° to 180°
  for (int angle = 0; angle <= 180; angle++) {
    myServo.write(angle); // Move the servo to the current angle
    delay(15);            // 3. Add a short delay to ensure smooth movement
  }

  delay(500); // Small pause at 180 degrees before moving back

  // 2. Use a method to gradually decrease the angle from 180° to 0°
  for (int angle = 180; angle >= 0; angle--) {
    myServo.write(angle); // Move the servo to the current angle
    delay(15);            // 3. Add a short delay to ensure smooth movement
  }

  delay(500); // Small pause at 0 degrees before restarting the loop
}