#include "esphome.h"
#include "spi.h"

class TPL0501 : public Component {
public:
  TPL0501(SPIClass *spi, int cs_pin) : spi_(spi), cs_pin_(cs_pin) {}

  void setup() override {
    pinMode(cs_pin_, OUTPUT);
    digitalWrite(cs_pin_, HIGH);  // Set chip select high
  }

  void set_value(uint8_t value) {
    digitalWrite(cs_pin_, LOW);  // Set chip select low
    uint8_t buffer[1] = {value}; // Send value to potentiometer
    spi_->beginTransaction(SPISettings(1000000, MSBFIRST, SPI_MODE0));
    spi_->transfer(buffer, 1);
    spi_->endTransaction();
    digitalWrite(cs_pin_, HIGH);  // Set chip select high
  }

private:
  SPIClass *spi_;
  int cs_pin_;
};
