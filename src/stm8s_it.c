#include "stm8s.h"
#include "stm8s_it.h"
#include "common.h"
#include "nrf24l01.h"

uint8_t sec = 100;

void tim4_update(void) __interrupt (IT_TIM4_OVR_UIF) {

	//static uint8_t sec = 100;
	TIM4->SR1 &= ~TIM4_SR1_UIF;

	if ( !sec-- ) {
		//ChgBit(GPIOB->ODR, 5);
		sec = 100;
	}
}


void exti2_irq(void) __interrupt(IT_EXTI2) {
	if( !(GPIOC->IDR & (PIN_4)) ) {
		// Faling edge on PC4
		sys_nrf.status |= 0x80;
	}
}
