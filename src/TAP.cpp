/**
 * \file         TAP.cpp
 * \author       Aliaksander Kavalchuk (aliaksander.kavalchuk@gmail.com)
 * \brief        This file contains the definition of the TAP (Test Access Port)
 * class which provides methods for interacting with the JTAG TAP controller.
 */

//_____ I N C L U D E S _______________________________________________________
#include "TAP.hpp"

#include <Arduino.h>

#include "Jtag.hpp"
#include "JtagCommon.hpp"

#include <assert.h>
//_____ C O N F I G S  ________________________________________________________
//_____ D E F I N I T I O N S _________________________________________________
//_____ P R I V A T E _________________________________________________________
//_____ C L A S S E S _________________________________________________________
TAP::TAP(uint8_t tms, uint8_t tdi, uint8_t tdo, uint8_t tck, uint8_t rst): jtag(tms, tdi, tdo, tck, rst) {}

void TAP::read(const Instruction_s &instruction, uint8_t *data)
{
  this->jtag.ir(instruction.code, instruction.ir_len);
  this->jtag.dr(data, instruction.dr_len, data);
}

void TAP::write(const Instruction_s &instruction, /*const*/ uint8_t *data)
{
  this->jtag.ir(instruction.code, instruction.ir_len);
  this->jtag.dr(data, instruction.dr_len, nullptr);
}

void TAP::execute(const Instruction_s &instruction, /*const*/ uint8_t *input, uint8_t *output)
{
  this->jtag.ir(instruction.code, instruction.ir_len);
  this->jtag.dr(input, instruction.dr_len, output);
}

void TAP::read_raw(uint8_t *input, uint8_t *data, uint16_t len)
{
  this->jtag.dr(input, len, data);
}

void TAP::reset()
{
  this->jtag.reset();
}

JTAG::ERROR TAP::setSpeed(uint32_t khz)
{
  return this->jtag.setSpeed(khz);
}
