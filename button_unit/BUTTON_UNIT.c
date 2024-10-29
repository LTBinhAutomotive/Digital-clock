#include"../LIB/Port.h"
#include"../LIB/PCC.h"
#include"../LIB/GPIO.h"
#include"../LIB/NVIC.h"
#include"../LIB/LPIT.h"
#include"\BUTTON_UNIT.h"

extern volatile int StateBTN1 ;
extern volatile int StateBTN2 ;
extern volatile int Set_Display ;
extern volatile int Count;
extern volatile int Second;
extern volatile int BTN_LED;

extern volatile int  SecondAlarm;
extern volatile int  MinuteAlarm;
extern volatile int  HourAlarm;

extern volatile int  Hour;
extern volatile int  Minute;

static volatile int  CountStop10s = 0;

void CONFIG_TIMMER(void)
{
	/*0. set NVIC */
	NVIC->ISER1 |= (1u << 16); 					// ID 48 
	NVIC->ISER1 |= (1u << 17); 					// ID 49 
	
	/*1. Setting Clocking */ 
	PCC->LPIT_0 &= ~(1u << 30);					// disable PCC[PCS]
	PCC->LPIT_0 &= ~(7u << 24);					// CLEAR
	PCC->LPIT_0 |=  (6u << 24);					// option 6 SPLLDIV
	PCC->LPIT_0 |=  (1u << 30);	        // Enable  PCC[CGC]
	
	//LPIT->PARAM &= ~(0x7Fu << 0);
	//LPIT->PARAM &=  (3u  << 0);
	
	/*2. LPIT Initialization*/
	LPIT->MCR |= (1u << 0);							// Module Clock Enable: MCR[M_CEN]
	LPIT->MCR |= (1u << 3);							// Run in Debug mode: MCR[DBG_EN]
	
	/*3. Enable Channel Timer Interrupt*/ 
	LPIT->MIER |= (1u << 0);						//MIER[TIEn]
	LPIT->MIER |= (1u << 1);						//MIER[TIEn]
	/*4. Set Timer Value start */
	LPIT->TVAL0 = 18000000-1;						//Timer Value Register: TVALn
	LPIT->TVAL1 =  6000000-1;						//Timer Value Register: TVALn
	/*5. Configuration for channel*/
	LPIT->TCTRL0 &= ~(3u << 2);					//Timer Operation Mode --> 32-bit Periodic Counter
	LPIT->TCTRL1 &= ~(3u << 2);					//Timer Operation Mode --> 32-bit Periodic Counter
	/*6. Timer Channel*/
	LPIT->TCTRL0 |= (1u << 0);					//Enable Timer Channel: TCTRLn[T_EN]
	LPIT->TCTRL1 |= (1u << 0);					//Enable Timer Channel: TCTRLn[T_EN]
	
}

void CONFIG_LEDGREEN (void)
{
	PCC->PortD   |=  (1u << 30);      	//Set Bit CGC (30) to 1.
	PORTD->PCR16 &= ~(7u << 8);  			  //Clear Bit MUX (8-10) to 0.
	PORTD->PCR16 |=  (1u << 8);   			//Set Bit 8 MUX to 1 (set GPIO function).
	GPIOD->PDDR  |=  (1u << 16);   			//set bit 16 OUTPUT to 1 LED green
	GPIOD->PDOR  |=  (1u << 16);
}

void LED_TEN_SECOND (void)
{
	if ( (SecondAlarm == Second) && (MinuteAlarm == Minute) && (HourAlarm == Hour) )
	{
		BTN_LED = 0;
	}
	
	if(BTN_LED == 1) GPIOD->PDOR |= (1u << 16);
	if(BTN_LED == 0) GPIOD->PDOR ^= (1u << 16);
	if ( CountStop10s == 10 )
	{
		GPIOD->PDOR |=  (1u << 16);
		BTN_LED = 1;
		CountStop10s = 0; 
	}
}

void CONFIG_BTN1(void)
{
	PCC->PortC   |=  (1u << 30);      	//Set Bit CGC (30) to 1.
	PORTC->PCR12 &= ~(7u << 8); 			  //Clear Bit MUX (8-10) to 0.
	PORTC->PCR12 |=  (1u << 8);  			  //Set Bit 8 MUX to 1 (set GPIO function).
	PORTC->PCR12 |=  (9u << 16);  			  //set 1001 Interrupt on rising-edge
	GPIOC->PDDR  &= ~(1u << 12);			  //Set Pin 12 (bit 12 of PDDR) to 0 (set input).
	NVIC->ISER1  |=  (1u << 29);				//set bit 29 ISER1 interrupt PORTC
}

void CONFIG_BTN2(void)
{
	PCC->PortC   |=  (1u << 30);      	//Set Bit CGC (30) to 1.
	PORTC->PCR13 &= ~(7u << 8); 			  //Clear Bit MUX (8-10) to 0.
	PORTC->PCR13 |=  (1u << 8);  			  //Set Bit 8 MUX to 1 (set GPIO function).
	PORTC->PCR13 |=  (9u << 16);  			 //set 1001 Interrupt on rising-edge
	GPIOC->PDDR  &= ~(1u << 13);			  //Set Pin 13 (bit 13 of PDDR) to 0 (set input).
}

void PORTC_IRQHandler(void)
{
	if((PORTC->PCR12 & (1u << 24)) == (1u << 24))
	{
		PORTC->PCR12 |= (1u << 24);    		// write 1 clear ISF
		
    StateBTN1++;
		
		Set_Display = 1;
		
		if(StateBTN1 > 3)
		{
			StateBTN1 = 0;
		}
		
		if(BTN_LED == 0)
		{
			BTN_LED = 1;
			StateBTN1--;
		}
	}
	
	if((PORTC->PCR13 & (1u << 24)) == (1u << 24))
	{
		PORTC->PCR13 |= (1u << 24);    		// write 1 clear ISF
		
		StateBTN2++;
		
		if(StateBTN2 > 4)
		{
			StateBTN2 = 0;
		}
		
		if(BTN_LED == 0)
		{
			BTN_LED = 1;
			StateBTN2--;
		}
	}
}

void LPIT0_Ch0_IRQHandler(void)
{
	if ( (LPIT->MSR & (1u << 0)) == (1u << 0) )
	{
		LPIT->MSR |= (1u << 0);
		
		Count++;
		
		if(Count == 10)
		{
			Count = 0;
		}
		
		Second ++;
		
		if(BTN_LED == 0) CountStop10s++;
	}
}

void LPIT0_Ch1_IRQHandler(void)
{
		
	if ( (LPIT->MSR & (1u << 1)) == (1u << 1) )
	{
		LPIT->MSR |= (1u << 1);
		
		LED_TEN_SECOND ();

	}
}
