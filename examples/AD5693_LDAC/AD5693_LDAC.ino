// This sketch uses the LDAC pin rather than I2C to 'output' the
// DAC's register value to the output pin. note that even if LDAC 
// isn't connected and toggled by a GPIO, if you continously
// write to the input register, you'll still get voltages on the
// output because the new value 'pushes' the old value out.
// So its more for synchronization than 'keeping the output from 
// changing'!
// in this demo we'll just write one value, 1.25V

#include "Adafruit_AD569x.h"


Adafruit_AD569x ad5693; // Create an object of the AD5693 library
#define LDAC_PIN 2

void setup() {
  Serial.begin(115200);
  while (!Serial) delay(10); // Wait for serial port to start
  Serial.println("Adafruit AD5693 LDAC test sketch");

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

  pinMode(LDAC_PIN, OUTPUT);
  digitalWrite(LDAC_PIN, HIGH);

  Serial.println("Writing 1.25Vto output with LDAC");
  
  if (!ad5693.writeDAC(0x8000)) {
    Serial.println("Failed to write to DAC");
    while (1) delay(10);
  }
  Serial.println("Toggling LDAC pin!");
  // load the data to the output
  digitalWrite(LDAC_PIN, LOW);
  digitalWrite(LDAC_PIN, HIGH);
}

void loop() {

}
