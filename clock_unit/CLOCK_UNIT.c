#include"../LIB/SCG.h"
#include"CLOCK_UNIT.h"

/***********************************************************

DIV1 = 72MHZ
DIV2 = 18MhZ
SLOW = 18MHZ
BUS	 = 24MHZ
CORE = 72MHZ

************************************************************/

void SOSOC_SCG( void )
{
	volatile unsigned int nTemp = SCG->SOSCCSR;
	
	/* Set bit 23 = 0, disable bit 0 */
	nTemp &= ~(1u << 23);		
	SCG->SOSCCSR = nTemp;
	nTemp &= ~(1u << 0);		
	SCG->SOSCCSR = nTemp;
	
	/* Set up SCG_SOSCCFG */
	nTemp = SCG->SOSCCFG;	
	nTemp &= ~((1u << 2) | (1u << 3) | (3u << 4));		 //clear bit 2 3 4
	nTemp |=  ((1u << 2) | (1u << 3u) | (3u << 4));    //set EREFS(Internal crystal oscillator) HGO RANGE 
	SCG->SOSCCFG = nTemp;
	
	/* Set up SCG_SOSCDIV */
	nTemp = SCG->SOSCDIV;
	nTemp &= ~((7u << 0) | (7u << 8));   //DIV 1 = 0 , DIV 2 =0
	SCG->SOSCDIV = nTemp;
	
	/* Set bit 23 = 0, enable bit 0 */
	nTemp = SCG->SOSCCSR;
	nTemp &= ~(1u << 23);
	SCG->SOSCCSR = nTemp;
	nTemp |= (1u << 0);
	SCG->SOSCCSR = nTemp;
	
	/* Wait SOSC valid */
	while (!(SCG->SOSCCSR & (1u << 24))) {}  //wait bit 24 is 1
}

void SPLL_SCG(void)
{
	volatile unsigned int nTemp;
	/* Set bit 23 = 0, disable bit 0 */
	nTemp = SCG->SPLLCSR;
	nTemp &= ~(1u << 23);  		//write bit 23 to 0
	SCG->SPLLCSR = nTemp;
	nTemp &= ~(1u << 0);   		//disable 
	SCG->SPLLCSR = nTemp;
	
	/*set SPLLCFG*/
	nTemp = SCG->SPLLCFG;
	nTemp &= ~(1u << 0); 			//clear bit 0      ---> SOSC
	nTemp &= ~(7u << 8); 			//clear bit 8 9 10
	nTemp &= ~(0x1Fu << 16);  //clear bit 16-20
	nTemp &= ~(1u << 8);			//DIVIDE /1        ---> 8Mhz
	nTemp |=  (2u << 16);     //MULT   x18       ---> 144Mhz
	SCG->SPLLCFG = nTemp;     // /2              ---> 72MHz
	
	/*set SPLLDIV*/
	nTemp = SCG->SPLLDIV;
	nTemp &= ~(7u << 0);			//clear bit 1 2 3
	nTemp &= ~(7u << 8);			//clear bit 8 9 10
	nTemp |=  (1u << 0);  		//divide 1    DIV1 72MHZ
	nTemp |=  (3u << 8);  		//divide 4    DIV2 18MHZ
	SCG->SPLLDIV = nTemp;
	
	/*set SPLLCSR*/
	nTemp = SCG->SPLLCSR;
	nTemp &= ~(1u << 23);  		//wirte bit 23 to 0
	SCG->SPLLCSR = nTemp;
	nTemp |=  (1u << 0);  		//enable bit 0
	SCG->SPLLCSR = nTemp;
	
	while ( !((SCG->SPLLCSR) & (1u << 24)) );   //wait bit 24 is 1
		
	/*set RCCR*/
	nTemp = SCG->RCCR;
	nTemp &= ~(0xFFu << 0);
	nTemp &= ~(0xFu << 16);
	nTemp &= ~(0xFu << 24);
	nTemp |=  (3u << 0);   		//set divide 4 SLOW     -->18MHZ
	nTemp |=  (2u << 4);   		//set divide 3 BUS			-->24MHZ
	nTemp &= ~(1u << 16);  		//set divide 1 CORE		  -->72MHZ
	nTemp |=  (6u << 24);  		//set 6 SPLL
	SCG->RCCR = nTemp;
	
	while ( (SCG->RCCR) != (SCG->CSR) ); 
}
