/*Final Project
 *LED Code should
 *initialize LEDs as outputs
 *7 LEDs total, PD0-PD6
 */
 
 #include "stm32f4xx.h" 
 
 //LED Functions
 void LED_Port_init(void);
 
 void LED_Port_init()
 {
	 
	 // Set MODER of GPIOD Pins 0, 1, 2, 3, 4, 5 as outputs (01)
	 GPIOD -> MODER |=(1<<0); // Set MODER of GPIOD pin 0 to output 01
	 GPIOD -> MODER &=~(1<<1);
	 
	 GPIOD -> MODER |=(1<<2); // Set MODER of GPIOD pin 1 to output 01
	 GPIOD -> MODER &=~(1<<3);
	 
	 GPIOD -> MODER |=(1<<4); // Set MODER of GPIOD pin 2 to output 01
	 GPIOD -> MODER &=~(1<<5);
	 
	 GPIOD -> MODER |=(1<<6); // Set MODER of GPIOD pin 3 to output 01
	 GPIOD -> MODER &=~(1<<7);
	 
	 GPIOD -> MODER |=(1<<8); // Set MODER of GPIOD pin 4 to output 01
	 GPIOD -> MODER &=~(1<<9);
	 
	 GPIOD -> MODER |=(1<<10); // Set MODER of GPIOD pin 5 to output 01
	 GPIOD -> MODER &=~(1<<11);
	 
	 GPIOD -> MODER |=(1<<12); // Set MODER of GPIOD pin 6 to output 01
	 GPIOD -> MODER &=~(1<<13);
	 
	 // set PUPDR of GPIOD pins 0, 1, 2, 3, 4, 5 to no Pull-up, no pull-down (00)
	 GPIOD -> PUPDR &=~(1<<1); // GPIOD pin 0 PUPDR set to 00
	 GPIOD -> PUPDR &=~(1<<0);
	 
	 GPIOD -> PUPDR &=~(1<<3); // GPIOD pin 1 PUPDR set to 00
	 GPIOD -> PUPDR &=~(1<<2);
	 
	 GPIOD -> PUPDR &=~(1<<5); // GPIOD pin 2 PUPDR set to 00
	 GPIOD -> PUPDR &=~(1<<4);
	 
	 GPIOD -> PUPDR &=~(1<<6); // GPIOD pin 3 PUPDR set to 00
	 GPIOD -> PUPDR &=~(1<<7);
	 
	 GPIOD -> PUPDR &=~(1<<8); // GPIOD pin 4 PUPDR set to 00
	 GPIOD -> PUPDR &=~(1<<9);
	 
	 GPIOD -> PUPDR &=~(1<<10); // GPIOD pin 5 PUPDR set to 00
	 GPIOD -> PUPDR &=~(1<<11);
	 
	 GPIOD -> PUPDR &=~(1<<12); // GPIOD pin 6 PUPDR set to 00
	 GPIOD -> PUPDR &=~(1<<13);
	 
	 // Set OTYPER of GPIOD pins 0, 1, 2, 3, 4, 5 to Push-Pull (0)
	 GPIOD -> OTYPER &=~(1<<0); // GPIOD pin 0 OTYPER set to 0
	 
	 GPIOD -> OTYPER &=~(1<<1); // GPIOD pin 1 OTYPER set to 0
	 
	 GPIOD -> OTYPER &=~(1<<2); // GPIOD pin 2 OTYPER set to 0
	 
	 GPIOD -> OTYPER &=~(1<<3); // GPIOD pin 3 OTYPER set to 0
	 
	 GPIOD -> OTYPER &=~(1<<4); // GPIOD pin 4 OTYPER set to 0
	 
	 GPIOD -> OTYPER &=~(1<<5); // GPIOD pin 5 OTYPER set to 0
	 
	 GPIOD -> OTYPER &=~(1<<6); // GPIOD pin 6 OTYPER set to 0
 }
