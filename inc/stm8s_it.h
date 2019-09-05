#ifndef STM8S_IT__H
#define STM8S_IT__H

/* Interrupt numbers */
#define IT_TLI				0
#define IT_AWU				1
#define IT_CLK				2
#define IT_EXTI0			3
#define IT_EXTI1			4
#define IT_EXTI2			5
#define IT_EXTI3			6
#define IT_EXTI4			7
#define IT_SPI				10
#define IT_TIM1_OVR_UIF 	11
#define IT_TIM1_CAP_COM 	12
#define IT_TIM2_OVR_UIF 	13
#define IT_TIM2_CAP_COM 	14
#define IT_UART1_TX			17
#define IT_UART1_RX			18
#define IT_I2C				19
#define IT_ADC1_EOC 		22
#define IT_TIM4_OVR_UIF 	23
#define IT_FLASH			24


void tim4_update(void) __interrupt (IT_TIM4_OVR_UIF);
void exti2_irq(void) __interrupt(IT_EXTI2);

#endif
