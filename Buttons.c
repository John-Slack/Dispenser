/*Final Project
 *Button Code
 *Button Initialization
 *6 Buttons set to GPIOB 0-5
 */
 
  #include "stm32f4xx.h"
	
	
	// Button Function
	void Button_Port_init(void);
	
	void Button_Port_init()
	{
		// Set GPIOC pins 0-5 MODER to input (00)
		GPIOB -> MODER &=~(1<<0); // GPIOB pin 0 MODER set to 00
		GPIOB -> MODER &=~(1<<1);

		GPIOB -> MODER &=~(1<<2); // GPIOB pin 1 MODER set to 00
		GPIOB -> MODER &=~(1<<3);

		GPIOB -> MODER &=~(1<<4); // GPIOB pin 2 MODER set to 00
		GPIOB -> MODER &=~(1<<5);
		
		GPIOB -> MODER &=~(1<<6); // GPIOB pin 3 MODER set to 00
		GPIOB -> MODER &=~(1<<7);

		GPIOB -> MODER &=~(1<<8); // GPIOB pin 4 MODER set to 00
		GPIOB -> MODER &=~(1<<9);

		GPIOB -> MODER &=~(1<<10); // GPIOB pin 5 MODER set to 00
		GPIOB -> MODER &=~(1<<11);
		
		// set PUPDR of GPIOC pins 0-5 to pull-down (10)
		GPIOB -> PUPDR &=~(1<<0); // GPIOB pin 0 PUPDR set to 10
		GPIOB -> PUPDR |= (1<<1);

		GPIOB -> PUPDR &=~(1<<2); // GPIOB pin 1 PUPDR set to 10
		GPIOB -> PUPDR |= (1<<3);

		GPIOB -> PUPDR &=~(1<<4); // GPIOB pin 2 PUPDR set to 10
		GPIOB -> PUPDR |= (1<<5);	
		
		GPIOB -> PUPDR &=~(1<<6); // GPIOB pin 3 PUPDR set to 10
		GPIOB -> PUPDR |= (1<<7);

		GPIOB -> PUPDR &=~(1<<8); // GPIOB pin 4 PUPDR set to 10
		GPIOB -> PUPDR |= (1<<9);

		GPIOB -> PUPDR &=~(1<<10); // GPIOB pin 5 PUPDR set to 10
		GPIOB -> PUPDR |= (1<<11);	
	}
