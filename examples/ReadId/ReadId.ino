// This Arduino sketch demonstrates how to use the ArduTAP library to read the ID of a microchip via JTAG.
// It initializes the Test Access Port (TAP) with the necessary pins and defines several instructions.
// The sketch then reads the ID of the microchip using the IDCODE instruction and prints it to the Serial Monitor.
// Reading chip IDs is a common operation in verifying communication with and the identity of JTAG-compatible devices.

#include "TAP.hpp"
#include <Arduino.h>

// Define the pin numbers for JTAG interface
#define TCK 2  // Test Clock
#define TMS 3  // Test Mode Select
#define TDI 4  // Test Data In
#define TDO 5  // Test Data Out
#define RST 6  // Reset

// Create an instance of the TAP class with the specified pin assignments
TAP tap = TAP(TMS, TDI, TDO, TCK, RST);

// Define JTAG instructions for various operations
Instruction_s IDCODE = {.code = 0x1FE, .ir_len = 9, .dr_len = 32};  // Instruction to read chip ID
Instruction_s DPACC = {.code = 0x1FA, .ir_len = 9, .dr_len = 36};   // Data Processing Access Code instruction
Instruction_s APACC = {.code = 0x1FB, .ir_len = 9, .dr_len = 36};   // Access Port Access Code instruction

void setup()
{
  Serial.begin(115200);
}

void loop()
{
  uint32_t id = 0;

  tap.reset();                       // Reset the TAP controller to the Test-Logic-Reset state
  tap.read(IDCODE, (uint8_t *)&id);  // Read the chip ID using the IDCODE instruction

  Serial.print("> ");
  Serial.println(id, HEX);
}
