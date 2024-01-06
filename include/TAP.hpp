/**
 * \file         TAP.hpp
 * \author       Aliaksander Kavalchuk (aliaksander.kavalchuk@gmail.com)
 * \brief        This file contains the definition of the TAP (Test Access Port)
 * class which provides methods for interacting with the JTAG TAP controller.
 */

#pragma once

//_____ I N C L U D E S _______________________________________________________
#include <Jtag.hpp>

//_____ C O N F I G S  ________________________________________________________
//_____ D E F I N I T I O N S _________________________________________________
// Structure to represent an instruction with its associated lengths
struct Instruction
{
  uint16_t code;    // Instruction code
  uint16_t ir_len;  // Length of the instruction register
  uint16_t dr_len;  // Length of the data register
};

using Instruction_s = Instruction;
//_____ C L A S S E S _________________________________________________________
/**
 * \brief The TAP class represents the Test Access Port (TAP) and provides
 * methods to manipulate and interact with it using JTAG commands.
 */
class TAP
{
public:
  TAP() = delete;

  /**
   * \brief Construct a new TAP object with specified JTAG pin assignments
   *
   * \param tms Pin number for Test Mode Select
   * \param tdi Pin number for Test Data In
   * \param tdo Pin number for Test Data Out
   * \param tck Pin number for Test Clock
   * \param trst Pin number for Test Reset (optional, depending on JTAG
   * hardware)
   */
  explicit TAP(uint8_t tms, uint8_t tdi, uint8_t tdo, uint8_t tck, uint8_t trst);

  /**
   * \brief Read data from the device by applying the given instruction and
   * storing the output
   *
   * \param instruction Instruction structure containing the code and lengths
   * \param data Pointer to a buffer where the output data will be stored
   */
  void read(const Instruction_s &instruction, uint8_t *data);

  /**
   * \brief Write data to the device using the given instruction
   *
   * \param instruction Instruction structure containing the code and lengths
   * \param data Pointer to the data to be written
   */
  void write(const Instruction_s &instruction, /*const*/ uint8_t *data);

  /**
   * \brief Execute a JTAG operation given an instruction, input data, and an
   * output buffer
   *
   * \param instruction Instruction structure containing the code and lengths
   * \param input Pointer to the input data
   * \param output Pointer to the buffer where the output data will be stored
   */
  void execute(const Instruction_s &instruction, /*const*/ uint8_t *input, uint8_t *output);

  /**
   * \brief Read raw data of specified length from the device
   *
   * \param input Pointer to the input data
   * \param data Pointer to a buffer where the output data will be stored
   * \param len Length of the data to read
   */
  void read_raw(uint8_t *input, uint8_t *data, uint16_t len);

  /**
   * \brief Reset the TAP controller to the Test-Logic-Reset state
   */
  void reset();

  /**
   * \brief Set the JTAG communication speed
   *
   * \param khz Desired speed in kHz
   * \return JTAG::ERROR Status of the speed setting operation
   */
  JTAG::ERROR setSpeed(uint32_t khz);

private:
  Jtag jtag;
};
