// This Arduino sketch demonstrates how to use the ArduTAP library to interact with a device via JTAG, specifically for
// enabling and checking status via the DPACC instruction. It initializes the Test Access Port (TAP) with the necessary
// pins and defines several instructions and associated operations. The sketch sends the DPACC instruction with data to
// enable certain features and then checks the status. This is a common operation for configuration and status
// verification of JTAG-compatible devices.

#include "TAP.hpp"
#include <Arduino.h>

// Define the pin numbers for the JTAG interface
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

byte output[56] = {};

void setup()
{
  Serial.begin(115200);
}

void loop()
{
  uint16_t length = 9;  // Define the length of the operation
  // Define data sequences for the DPACC instruction
  uint8_t DP_ENABLE[] = {0x02, 0x00, 0x00, 0x80, 0x02};        // Data to enable certain DP features
  uint8_t DP_ENABLE_CHECK[] = {0x03, 0x00, 0x00, 0x80, 0x02};  // Data to check the enable operation

  tap.reset();  // Reset the TAP controller to the Test-Logic-Reset state
  // Execute the DPACC instruction with the enable data
  tap.execute(DPACC, DP_ENABLE, nullptr);  // Send DP_ENABLE sequence
  // Execute the DPACC instruction with the enable check data and read the output into the buffer
  tap.execute(DPACC, DP_ENABLE_CHECK, output);  // Send DP_ENABLE_CHECK sequence and read the status
}
