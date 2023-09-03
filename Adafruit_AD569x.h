/**
 * @file Adafruit_AD569x.h
 *
 * This is a library for the AD569x 16-/14-/12-bit DAC.
 *
 */

#ifndef ADAFRUIT_AD569X_H
#define ADAFRUIT_AD569X_H

#include <Adafruit_I2CDevice.h>
#include <Arduino.h>
#include <Wire.h>

/// Enum for AD569x commands.
typedef enum {
  NOP = 0x00,         ///< No operation command.
  WRITE_INPUT = 0x10, ///< Write to the input register.
  UPDATE_DAC = 0x20,  ///< Update the DAC register.
  WRITE_DAC_AND_INPUT =
      0x30, ///< Write to the input register and update the DAC register.
  WRITE_CONTROL = 0x40 ///< Write to the control register.
} ad569x_commands;

/// Enum for AD569x operating modes.
typedef enum {
  NORMAL_MODE = 0x00,           ///< Normal operating mode.
  OUTPUT_1K_IMPEDANCE = 0x01,   ///< 1k Ohm output impedance mode.
  OUTPUT_100K_IMPEDANCE = 0x02, ///< 100k Ohm output impedance mode.
  OUTPUT_TRISTATE = 0x03        ///< Tristate output mode.
} ad569x_operating_modes;

/// Class for communicating with AD569x family of I2C DACs
class Adafruit_AD569x {
public:
  Adafruit_AD569x();
  bool begin(uint8_t addr, TwoWire *wire = &Wire);
  bool writeDAC(uint16_t value);
  bool updateDAC(void);
  bool writeUpdateDAC(uint16_t value);
  void reset(void);
  bool setMode(ad569x_operating_modes newmode, bool enable_ref, bool gain2x);

private:
  Adafruit_I2CDevice *i2c_dev; // Pointer to I2C device
};

#endif // ADAFRUIT_AD569X_H
