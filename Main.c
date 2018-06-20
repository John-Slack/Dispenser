/*Final Project
 *Main code
 *Calls Initialization code for LEDs, Buttons, Distance Sensor,
 *and Pumps, then runs the Main Program
 */
 
	#include "LED.h"
	#include "Buttons.h"
	#include "stm32f4xx.h"
	#include "Distance_Sensor.h"
	#include "Pumps.h"
	#include "PumpPWM.h"

	void tim6_delay(void);
	void delay(int ms);

	int OLDVAL =0; 
	int NEWVAL =0;
	int PERIOD =0;
	float PERIOD_MS = 0.0;

	int overflow = 0;
 
 int main(void)
 {
	 int B_Flag0 = 0; // Pin 0 button flag
	 int B_Flag1 = 0; // Pin 1 button flag
	 int B_Flag2 = 0; // Pin 2 button flag
	 int B_Flag3 = 0; // Pin 3 button flag
	 int B_Flag4 = 0; // Pin 4 button flag
	 int B_Flag5 = 0; // Pin 5 button flag

	 
	 // Enable GPIOD and GPIOB in RCC AHB1ENR Register
	 RCC -> AHB1ENR = 0x0000000A;
	 RCC -> APB1ENR |= (1<<2); // Enable timer 4
	 RCC -> APB1ENR |= (1<<1); // enable TIM3
	 
	 LED_Port_init();
	 Button_Port_init();
	 distanceSensor_init();
	 Pump_init();
	 PWM_init();
	 
	 while(1)
	 {
		 //====================
		 //Select drink option
		 //====================
		 if(GPIOB -> IDR & (1<<0)) // if Button on GPIOC pin 0 is enabled
		 {
			 B_Flag0 = 1;
			 B_Flag1 = 0;
			 B_Flag2 = 0;
		 }
		 else if(GPIOB -> IDR & (1<<1)) // if Button on GPIOC pin 1 is enabled
		 {
			 B_Flag0 = 0;
			 B_Flag1 = 1;
			 B_Flag2 = 0;
		 }
		 else if(GPIOB -> IDR & (1<<2)) // if Button on GPIOC pin 2 is enabled
		 {
			 B_Flag0 = 0;
			 B_Flag1 = 0;
			 B_Flag2 = 1;
		 }
		 	else
		 {
			 B_Flag0 = 0;
			 B_Flag1 = 0;
			 B_Flag2 = 0;
		 }
		 //======================
		 //Select Dispense amount
		 //======================
		 if(GPIOB -> IDR & (1<<3)) // if Button on GPIOC pin 3 is enabled
		 {
			 B_Flag3 = 1;
			 B_Flag4 = 0;
			 B_Flag5 = 0;
		 }
		 else if(GPIOB -> IDR & (1<<4)) // if Button on GPIOC pin 4 is enabled
		 {
			 B_Flag3 = 0;
			 B_Flag4 = 1;
			 B_Flag5 = 0;
		 }
		 else if(GPIOB -> IDR & (1<<5)) // if Button on GPIOC pin 5 is enabled
		 {
			 B_Flag3 = 0;
			 B_Flag4 = 0;
			 B_Flag5 = 1;
		 }
		 else
		 {
			 B_Flag3 = 0;
			 B_Flag4 = 0;
			 B_Flag5 = 0;
		 }
		 //=======================
		 //Light up selected drink
		 //=======================
		 if(B_Flag0 == 1)
		 {
			 GPIOD -> ODR |= (1<<0); // Enable GPIOD pin 0 LED
			 GPIOD -> ODR &=~(1<<1); // Disable GPIOD pin 1 LED
			 GPIOD -> ODR &=~(1<<2); // Disable GPIOD pin 2 LED
		 }
		 
		 if(B_Flag1 == 1)
		 {
			 GPIOD -> ODR &=~(1<<0); // Disable GPIOD pin 0 LED
			 GPIOD -> ODR |= (1<<1); // Enable GPIOD pin 1 LED
			 GPIOD -> ODR &=~(1<<2); // Disable GPIOD pin 2 LED
		 }
		 
		 if(B_Flag2 == 1)
		 {
			 GPIOD -> ODR &=~(1<<0); // Disable GPIOD pin 0 LED
			 GPIOD -> ODR &=~(1<<1); // Disable GPIOD pin 1 LED
			 GPIOD -> ODR |= (1<<2); // Enable GPIOD pin 2 LED
		 }
		 //========================
		 //Light up selected amount
		 //========================
		 if(B_Flag3 == 1)
		 {
			 GPIOD -> ODR |= (1<<3); // Disable GPIOD pin 3 LED
			 GPIOD -> ODR &=~(1<<4); // Disable GPIOD pin 4 LED
			 GPIOD -> ODR &=~(1<<5); // Disable GPIOD pin 5 LED
		 }
		 
		 if(B_Flag4 == 1)
		 {
			 GPIOD -> ODR &=~(1<<3); // Disable GPIOD pin 3 LED
			 GPIOD -> ODR |= (1<<4); // Disable GPIOD pin 4 LED
			 GPIOD -> ODR &=~(1<<5); // Disable GPIOD pin 5 LED
		 }
		 
		 if(B_Flag5 == 1)
		 {
			 GPIOD -> ODR &=~(1<<3); // Disable GPIOD pin 3 LED
			 GPIOD -> ODR &=~(1<<4); // Disable GPIOD pin 4 LED
			 GPIOD -> ODR |= (1<<5); // Disable GPIOD pin 5 LED
		 }
		 //======================================
		 //Light up if cup is sensed under nozzle
		 //======================================
		 GPIOB -> ODR |= (1<<7);  // Set Trigger to high
		 delay(1); // wait one millisecond
		 GPIOB -> ODR &=~(1<<7); // set trigger low, then wait for echo input capture
		 delay(10);
		 if(period < 200) // if object sensed by distance sensor
		 {
			 GPIOD -> ODR |= (1<<6); // Enable GPIOD pin 6 LED		
			 
			 if(B_Flag0 == 1) // if drink 1 is selected
			 {
				 if(B_Flag3 == 1) // Dispense Drink 1, at Size 1
				 {
					 GPIOD -> ODR |= (1<<7); // enable H-Bridge for pump 1
					 delay(10000); // 10 second delay
					 GPIOD -> ODR &=~(1<<7);
				 }
				 else if(B_Flag4 == 1) // Dispense Drink 1, at Size 2
				 {
					 GPIOD -> ODR |= (1<<7); // enable H-Bridge for pump 1
					 delay(30000); // 30 second delay
					 GPIOD -> ODR &=~(1<<7);
				 }
				 else if(B_Flag5 == 1) // Dispense Drink 1, at Size 3
				 {
					 GPIOD -> ODR |= (1<<7); // enable H-Bridge for pump 1
					 delay(45000); // 45 second delay
					 GPIOD -> ODR &=~(1<<7);
				 }
			 }
			 else if(B_Flag1 == 1) // if drink 2 is selected
			 {
				 if(B_Flag3 == 1) // Dispense Drink 2, at Size 1
				 {
					 GPIOD -> ODR |= (1<<8); // enable H-Bridge for pump 2
					 delay(10000); // 10 second delay
					 GPIOD -> ODR &=~(1<<8);
				 }
				 else if(B_Flag4 == 1) // Dispense Drink 2, at Size 2
				 {
					 GPIOD -> ODR |= (1<<8); // enable H-Bridge for pump 2
					 delay(30000); // 30 second delay
					 GPIOD -> ODR &=~(1<<8);
				 }
				 else if(B_Flag5 == 1) // Dispense Drink 2, at Size 3
				 {
					 GPIOD -> ODR |= (1<<8); // enable H-Bridge for pump 2
					 delay(45000); // 45 second delay
					 GPIOD -> ODR &=~(1<<8);
				 }
			 }
			 else if(B_Flag2 == 1) // if drink 3 is selected
			 {
				 if(B_Flag3 == 1) // Dispense Drink 3, at Size 1
				 {
					 GPIOD -> ODR |= (1<<9); // enable H-Bridge for pump 3
					 delay(10000); // 10 second delay
					 GPIOD -> ODR &=~(1<<9);
				 }
				 else if(B_Flag4 == 1) // Dispense Drink 2, at Size 2
				 {
					 GPIOD -> ODR |= (1<<9); // enable H-Bridge for pump 3
					 delay(30000); // 30 second delay
					 GPIOD -> ODR &=~(1<<9);
				 }
				 else if(B_Flag5 == 1) // Dispense Drink 3, at Size 3
				 {
					 GPIOD -> ODR |= (1<<9); // enable H-Bridge for pump 3
					 delay(45000); // 45 second delay
					 GPIOD -> ODR &=~(1<<9);
				 }
			 }
		 }
			 else // no object sensed under nozzle
		 {
			 GPIOD -> ODR &=~(1<<6); // Disable GPIOD pin 6 LED
		 }
		 

		 
	 }
 }
 
 /*******************************
 * tim6_delay(void)
 * Inputs: NONE
 * Outputs: NONE
 * Based on PSC=0 and ARR=21000; 
 * we get delay of approximately 1.33ms
 *******************************
 */
void tim6_delay(void){
	// enable APB1 bus clock
	RCC->APB1ENR|=RCC_APB1ENR_TIM6EN;
	//TIM6 prescaler set at default to 0 for now
	TIM6->PSC=0; // prescalar
	TIM6->ARR = 21000;  //auto reload register 
	TIM6->CNT=0;   //clear counter register
	TIM6->CR1|=TIM_CR1_CEN;
	//WHEN COUNTER IS DONE THE TIM6_SR REG UIF FLAG IS SET
	while(TIM6->SR==0);
	TIM6->SR=0; //CLEAR uIF FLAG
}

/*******************************
 * delay(int ms)
 * Inputs: delay in milliseconds
 * Outputs: NONE
 * An approximate delay because  
 * call of tim6_delay() creates about 1.33ms
 *******************************
 */
void delay(int ms){
int i;
	for (i=ms; i>0; i--)
	{
		tim6_delay();
	}
}

void TIM4_IRQHandler(void)
{
// 1. If UIF flag is SET, we got here because of overflow; Update overflow variable.
	if(TIM4->SR &1)
	{
		overflow ++;
		TIM4->SR &=~(1<<0); //clear flag
	}
// 2. IF CC1IF flag is SET, We got here because of capture interrupt.
	else if(TIM4->SR &2)
	{
		OLDVAL = NEWVAL;
		TIM4->SR &=~(1<<1); // clear SR flag
		
		NVIC_ClearPendingIRQ(TIM4_IRQn); // clear pending IRQ
		NEWVAL = TIM4->CCR1; // flag cleared when NEWVAL is processed
		
		PERIOD = (NEWVAL - OLDVAL) + 0xFFFF * overflow; //calculates period
		PERIOD_MS = (double)(PERIOD / (100.00000)); // converts period to milliseconds
		
		overflow = 0;
		//OLDVAL = NEWVAL; // prepares for next value
	}
}
