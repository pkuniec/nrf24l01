#include <stdlib.h>
#include "stm8s.h"
#include "stm8s_it.h"
#include "common.h"
#include "nrf24l01.h"


nrf_t sys_nrf;

int main(void) {

	spi_init();
	setup();

	nrf_init_hw();
	nrf_reset();
	nrf_init_sw();

	// Reciver
	nrf_rx_enable();
	nrf_register_cb( callback_rx );

	rim();

	while( 1 ) {
		// Recv
		nrf_checkstatus();
	}
}


void callback_rx(void) {
	ChgBit(GPIOB->ODR, 5);
}
