#ifndef COMMON__H
#define COMMON__H

#define LED     (1<<5)


void setup(void);
void delay(uint16_t time);
void uart_event(void);

uint8_t eeprom_read(uint8_t addr);
void eeprom_write(uint8_t addr, uint8_t *data, uint8_t len);

void spi_init(void);
uint8_t spi_transmit(uint8_t data);

void callback_rx(void);

#endif