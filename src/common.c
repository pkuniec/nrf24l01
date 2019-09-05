#include "stm8s.h"
#include "common.h"

void setup(void) {

	// GPIO
	GPIOB->DDR |= LED;
	GPIOB->CR1 |= LED;

	//Tim4
	TIM4->PSCR = TIM4_PSCR_PSC; // pre. 128
	TIM4->ARR = 99;
	TIM4->IER |= TIM4_IER_UIE;
	TIM4->CR1 |= TIM4_CR1_CEN;
}


void delay(uint16_t time) {
	while( time-- ) {
		nop();
	}
}


void spi_init(void) {
	SPI->CR2 = SPI_CR2_SSM | SPI_CR2_SSI;
	SPI->CR1 = SPI_CR1_MSTR | SPI_CR1_SPE;
}


uint8_t spi_transmit(uint8_t data) {
	SPI->DR = data;
	while( !(SPI->SR & SPI_SR_TXE) );
	while( !(SPI->SR & SPI_SR_RXNE) );
	return SPI->DR;
}
