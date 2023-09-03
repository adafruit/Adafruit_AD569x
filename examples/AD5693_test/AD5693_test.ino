#include "Adafruit_AD569x.h"
#include <math.h> // For sine function

Adafruit_AD569x ad5693; // Create an object of the AD5693 library

void setup() {
  Serial.begin(115200);
  while (!Serial) delay(10); // Wait for serial port to start
  Serial.println("Adafruit AD5693 Test Sketch");

  // Initialize the AD5693 chip
  if (ad5693.begin(0x4C, &Wire)) { // If A0 jumper is set high, use 0x4E
    Serial.println("AD5693 initialization successful!");
  } else {
    Serial.println("Failed to initialize AD5693. Please check your connections.");
    while (1) delay(10); // Halt
  }

  // Reset the DAC
  ad5693.reset();

  // Configure the DAC for normal mode, internal reference, and no 2x gain
  if (ad5693.setMode(NORMAL_MODE, true, false)) {
    Serial.println("AD5693 configured");
  } else {
    Serial.println("Failed to configure AD5693.");
    while (1) delay(10); // Halt
  }

  // You probably will want to set the I2C clock rate to faster
  // than the default 100KHz, try 400K or 800K or even 1M!
  Wire.setClock(800000);

  Serial.println("Writing 2.5Vpp sine wave to output");
}

void loop() {
  // Generate a sine wave and write it to the DAC
  for (float angle = 0; angle <= 2 * PI; angle += 0.1) {
    uint16_t value = (uint16_t)((sin(angle) + 1) * 32767.5); // Convert sine value to uint16_t
    if (!ad5693.writeUpdateDAC(value)) {
      Serial.println("Failed to update DAC.");
    }
  }
}
