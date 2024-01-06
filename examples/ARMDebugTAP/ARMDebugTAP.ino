#include <TAP.hpp>

class ARMDebugTAP : TAP
{
public:
  ARMDebugTAP(uint8_t tms, uint8_t tdi, uint8_t tdo, uint8_t tck, uint8_t trst);

  void enable();
  void disable();

  void clearErrors();
  bool isErrorState();
  uint32_t id();

  bool memoryWrite32(uint32_t addr, uint32_t value);
  bool memoryRead32(uint32_t addr, uint32_t *value);

private:
  Instruction_s IDCODE;
  Instruction_s APACC;
  Instruction_s DPACC;
  Instruction_s BYPASS;
  Instruction_s ABORT;
};

ARMDebugTAP::ARMDebugTAP(uint8_t tms, uint8_t tdi, uint8_t tdo, uint8_t tck, uint8_t trst):
    TAP(tms, tdi, tdo, tck, trst), IDCODE{.code = 0x1FE, .ir_len = 9, .dr_len = 32},
    DPACC{.code = 0x1FA, .ir_len = 9, .dr_len = 36}, APACC{.code = 0x1FB, .ir_len = 9, .dr_len = 36},
    BYPASS{.code = 0x1FF, .ir_len = 9, .dr_len = 1}, ABORT{.code = 0x1F8, .ir_len = 9, .dr_len = 0}
{
}

void ARMDebugTAP::enable()
{
  uint8_t enable[] = {0x02, 0x00, 0x00, 0x80, 0x02};

  TAP::reset();
  TAP::execute(this->DPACC, enable, nullptr);
}
void ARMDebugTAP::disable()
{
  uint8_t enable[] = {0x02, 0x00, 0x00, 0x00, 0x00};

  TAP::reset();
  TAP::execute(this->DPACC, enable, nullptr);
}

void ARMDebugTAP::clearErrors()
{
  // TODO: Add implementation
}
bool ARMDebugTAP::isErrorState()
{
  // TODO: Add implementation
  return false;
}

uint32_t ARMDebugTAP::id()
{
  uint32_t id = 0;

  TAP::reset();
  TAP::read(this->IDCODE, (uint8_t *)&id);

  return id;
}

bool ARMDebugTAP::memoryWrite32(uint32_t addr, uint32_t value)
{
  uint8_t data[] = {0x04, 0x00, 0x00, 0x00, 0x00};
  uint8_t data_1[] = {0x10, 0x00, 0x00, 0x00, 0x00};
  uint8_t data_2[] = {0x02, 0x00, 0x00, 0x00, 0x01};
  uint8_t data_3[] = {0x2E, 0x55, 0x55, 0x55, 0x55};

  this->enable();
  TAP::reset();
  TAP::execute(DPACC, /*const*/ data, nullptr);

  TAP::reset();
  TAP::execute(APACC, /*const*/ data_1, nullptr);

  TAP::reset();
  TAP::execute(APACC, /*const*/ data_2, nullptr);

  TAP::reset();
  TAP::execute(APACC, /*const*/ data_3, nullptr);

  return !this->isErrorState();
}

bool ARMDebugTAP::memoryRead32(uint32_t addr, uint32_t *value)
{
  uint8_t data[] = {0x04, 0x00, 0x00, 0x00, 0x00};
  uint8_t data_1[] = {0x10, 0x00, 0x00, 0x00, 0x00};
  uint8_t data_2[] = {0x02, 0x00, 0x00, 0x00, 0x01};
  uint8_t data_4[] = {0x07, 0x00, 0x00, 0x00, 0x00};
  uint8_t zeros[] = {0x00, 0x00, 0x00, 0x00, 0x00};
  uint8_t output[5] = {0, 0, 0, 0, 0};
  uint16_t length = 0;
  uint32_t variable = 0;

  TAP::reset();
  TAP::execute(DPACC, /*const*/ data, nullptr);

  TAP::reset();
  TAP::execute(APACC, /*const*/ data_1, nullptr);

  TAP::reset();
  TAP::execute(APACC, /*const*/ data_2, nullptr);

  TAP::reset();
  TAP::execute(APACC, /*const*/ data_4, nullptr);

  TAP::read_raw(zeros, output, length = 36);

  return !this->isErrorState();
}
