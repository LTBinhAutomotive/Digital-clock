#include"../LIB/Port.h"
#include"../LIB/PCC.h"
#include"../LIB/SPI.h"
#include"SPI_UNIT.h"

void CONFIG_SPI(void)
{
/*1. Setting SCK/PCS/SOUT/SIN pin--> SPI0 */
	PCC->PortE &= ~(1u << 30);  		//enable portE
	PCC->PortE |=  (1u << 30);			//enable portE
	
	PORTE->PCR0 &= ~(7u << 8);  		//SCK
	PORTE->PCR1 &= ~(7u << 8);			//IN
	PORTE->PCR2 &= ~(7u << 8);			//OUT
	PORTE->PCR6 &= ~(7u << 8);			//PCS
	
	PORTE->PCR0 |=  (2u << 8);			// 010 ALT2
	PORTE->PCR1 |=  (2u << 8);			// 010 ALT2
	PORTE->PCR2 |=  (2u << 8);			// 010 ALT2
	PORTE->PCR6 |=  (2u << 8);			// 010 ALT2
	
/*2. Peripheral Clock Source Select: PCC[PCS]*/
	PCC->LPSPI0 &= ~(1u << 30);     //disable
	PCC->LPSPI0 &= ~(7u << 24);     //clear bit
	PCC->LPSPI0 |=  (6u << 24);     //select option 6 SPLL_CLK
	PCC->LPSPI0 |=  (1u << 30);     //enable
	
/*3. setting clock  */
	static volatile unsigned int nTemp;
	
	nTemp  = LPSPI_0->TCR;
	nTemp &= ~(7u << 27);  					//set divide 1
	LPSPI_0->CCR |= (1u << 0);  		//write 1    -->SCK clock = 18/(1 *(1+2) ) = 6MHz
	
/*4. Configures Clock Phase and Polarity */
	nTemp &= ~(3u << 30);   				//CPOL =0 and CPHA = 0
	
/*5. Setting Frame data  */
	nTemp &= ~(0xFFFu << 0);     
	nTemp |=  (15u << 0);						//Frame = 16
	nTemp &= ~(1u << 23);         	//MSB
	
/*6. Configures the peripheral chip select*/
	nTemp &= ~(3u << 24);           
	nTemp |=  (2u << 24);           //PCS 2
	
	LPSPI_0->TCR = nTemp;
	
/*7. Setting Transmit/Receive FIFO*/
	LPSPI_0->FCR   |=  (1u << 0);      //Transmit FIFO Watermark	2 Word
	LPSPI_0->FCR   |=  (1u << 16);     //Receive FIFO Watermark   
	LPSPI_0->CFGR1 |=  (1u << 3); 		 //Set FIFO underrun
	
/*8.Configures LPSPI mode  */
	LPSPI_0->CFGR1 |= (1u << 0); 			//Set master
	LPSPI_0->CR    |= (1u << 3);			//LPSPI module is enabled in debug mode
	
/*9.Enable LPSPI module */
	LPSPI_0->CR    |= (1u << 0);			//enabled module

}	
