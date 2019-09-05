#include <stdlib.h>
#include "stm8s.h"
#include "common.h"
#include "nrf24l01.h"
#include "nrf24l01_mem.h"

void nrf_init_hw(void) {
	// GPIO
	GPIOD->DDR = SPI_CE | SPI_CSN;
	GPIOD->CR1 = SPI_CE | SPI_CSN;
	GPIOD->CR2 = SPI_CE | SPI_CSN;
	GPIOD->ODR = SPI_CSN;

	//GPIOC->CR1 |= NRF_IRQ;
	GPIOC->CR2 = NRF_IRQ;

	// EXTI
	EXTI->CR1 = 0x20; // PORTC faling edge
}


void nrf_init_sw(void) {
	uint8_t addr[5] = {0xA5, 0xE7, 0xE7, 0xE7, 0xA7};

	nrf_writereg( SETUP_AW, AW_5 );
	nrf_writereg_many( 0, TX_ADDR, addr, 5);
	nrf_writereg( EN_RXADDR, ERX_P0 | ERX_P1 );
	nrf_writereg_many( 0, RX_ADDR_P0, addr, 5);
	nrf_writereg( RX_PW_P0, PAYLOADSIZE);
	nrf_writereg( RX_PW_P1, PAYLOADSIZE);
	nrf_writereg( EN_AA, 0x00);
	nrf_writereg( RF_CH, 11);
	nrf_writereg( RF_SETUP, TRANS_SPEED_1MB );
	nrf_writereg( SETUP_RETR, 0x40);
	nrf_writereg( FEATURE, EN_DYN_ACK);
	nrf_writereg( CONFIG, EN_CRC | CRC0 | MASK_MAX_RT | MASK_TX_DS);
}


void nrf_reset(void) {
	nrf_ce_high();

	nrf_writereg( CONFIG, 0x08 );
	nrf_writereg( RX_PW_P0, 0x00);
	nrf_writereg( EN_AA, 0x00 );
	nrf_writereg( EN_RXADDR, 0x00 );
	nrf_writereg( RF_CH, 0x00 );
	nrf_writereg( RF_SETUP, 0x00 );
	nrf_writereg( STATUS, 0xe0 );
	nrf_sendcmd( FLUSH_TX );
	nrf_sendcmd( FLUSH_RX );

	nrf_ce_low();
}


void nrf_powerdown(void) {
	uint8_t config;
	GPIOD->ODR &= ~SPI_CE;
	config = nrf_readreg( CONFIG );
	config &= ~(PWR_UP | PRIM_RX);
	nrf_writereg( CONFIG, config );
}


void nrf_rx_enable(void) {
	uint8_t config = 0;
	nrf_ce_low();

	config = nrf_readreg( CONFIG );
	nrf_writereg( CONFIG, config | PRIM_RX | PWR_UP );
	while( !(config & (PWR_UP | PRIM_RX)) ) {
		config = nrf_readreg( CONFIG );
	}

	nrf_ce_high();
	nrf_sendcmd( FLUSH_RX );
}


void nrf_tx_enable(void) {
	uint8_t config;
	nrf_ce_low();

	config = nrf_readreg( CONFIG );
	config &= ~(PRIM_RX);
	nrf_writereg( CONFIG, config | PWR_UP );
	while( !(config & PWR_UP) ) {
		config = nrf_readreg( CONFIG );
	}
	nrf_sendcmd( FLUSH_TX );
}


void nrf_read_rx(uint8_t *data, uint8_t len) {
	nrf_csn_enable();
	spi_transmit( R_RX_PAYLOAD );
	while(len--) {
		*data++ = spi_transmit( NOP );
	}
	nrf_csn_disable();
}


void nrf_write_tx(uint8_t *data, uint8_t len) {
	nrf_writereg_many(1, W_TX_PAYLOAD, data, len);
	nrf_ce_high();
	delay(100);
	nrf_ce_low();
}


void nrf_register_cb(nrf_cb_f func) {
	sys_nrf.func = func;
}


void nrf_checkstatus(void) {
	uint8_t nstatus = 0;

	if( (sys_nrf.status) ) {
		// NRF24L01 interrupt notify
		sys_nrf.status = nrf_readreg( STATUS );
		sys_nrf.pipe_no = (sys_nrf.status >> 1) & 0x07;

		if( (sys_nrf.status & RX_DR) ) {
			// odebrano dane
			nstatus |= RX_DR;
			nrf_read_rx(sys_nrf.data_rx, PAYLOADSIZE);
		}

		if( (sys_nrf.status & TX_DS) ) {
			// wyslano dane
			nstatus |= TX_DS;
		}

		if( (sys_nrf.status & MAX_RT) ) {
			// max. retry reached
			nstatus |= MAX_RT;
		}

		if( (sys_nrf.status & TX_FULL) ) {
			// bufor nadawczy pełny
			
		}

		if( sys_nrf.func ) {
			sys_nrf.func();
		}

		sys_nrf.status = 0;
		nrf_writereg( STATUS, nstatus );
	}
}


void nrf_csn_enable(void) {
	GPIOD->ODR &= ~SPI_CSN;
}


void nrf_csn_disable(void) {
	while( (SPI->SR & SPI_SR_BSY) );
	GPIOD->ODR |= SPI_CSN;
}


void nrf_ce_low(void) {
	GPIOD->ODR &= ~SPI_CE;
}


void nrf_ce_high(void) {
	GPIOD->ODR |= SPI_CE;
}


uint8_t nrf_sendcmd(uint8_t cmd) {
	uint8_t status;
	nrf_csn_enable();
	status = spi_transmit( cmd );
	nrf_csn_disable();
	return status;
}


uint8_t nrf_readreg(uint8_t reg) {
	uint8_t data;
	nrf_csn_enable();
	spi_transmit(R_REGISTER | (REGISTER_MASK & reg) );
	data = spi_transmit(NOP);
	nrf_csn_disable();
	return data;
}


void nrf_writereg(uint8_t reg, uint8_t data) {
	nrf_csn_enable();
	spi_transmit(W_REGISTER | (REGISTER_MASK & reg) );
	spi_transmit(data);
	nrf_csn_disable();
}


void nrf_writereg_many(uint8_t cmd, uint8_t reg, uint8_t *data, uint8_t len) {
	nrf_csn_enable();

	if( cmd ) {
		spi_transmit( reg );
	} else {
		spi_transmit(W_REGISTER | (REGISTER_MASK & reg) );
	}

	while(len--) {
		spi_transmit(*data++);
	}
	nrf_csn_disable();
}
