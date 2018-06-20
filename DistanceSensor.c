/*Final Project
 *Distance Sensor Code
 *and Initialization
 *4 pins: Vcc, GND, PB7, PB6
 */
	
	#include "stm32f4xx.h"
	
	
	void distanceSensor_init(void);
	
	void distanceSensor_init(void)
	{
		GPIOB -> MODER |= (1<<14); // PB7 set to output mode (TRIG pin)
		GPIOB -> MODER &=~(1<<15);

		// GPIOB mode pin 6 set to alternating mode (ECHO)
		GPIOB -> MODER |= (1<<13); 
		GPIOB -> MODER &= ~(1<<12);
		
		GPIOB -> AFR[0] |= (1<<25); // AF2 pin 6 set to alternate function mode
		
		TIM4 -> PSC = 159; // TIM4 freq set to 1.05 MHZ
		
		TIM4->CCMR1 &=~(1<<1); // Timer 4 channel set to input mode 
		TIM4->CCMR1 |= (1<<0); // IC1 mapped on TI1
		
		TIM4->CCER &=~(0x000A); // polarity set to noninverted rising edge
		
		TIM4->CCMR1 &=~(1<<2); // capture is done each time an edge is detected
		
		TIM4->CCER |= (1<<0); // capture enabled
		
		TIM4->DIER |= (1<<1); // Capture and compare 1 interrupt enabled
		
		TIM4->CR1 |= (1<<0); // CR1 registers counter enabled
		TIM4->CR1 &=~(1<<1);
		
		// Let CMSIS take care of NVIC interrupt regs
		NVIC_EnableIRQ(TIM4_IRQn); // enable TIM4 Interrupt
	}
