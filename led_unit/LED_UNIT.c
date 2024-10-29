#include"../LIB/SPI.h"
#include"LED_UNIT.h"
#include"BUTTON_UNIT.h"

void CONFIG_LED(void)
{
	/*configuage address 
	volatile unsigned short ShutdownFormat = 0x1C11;      // set 1 for D0  NormalOperation
	volatile unsigned short DecodeMode     = 0x19FF;			// Code B decode for digits 7–0
	volatile unsigned short Intensity      = 0x1A1A;			// 21/32
	volatile unsigned short ScanLimit      = 0x1B07;			// Display digit 0-4 only*
	volatile unsigned short DisplayTest    = 0x1F00;			// Display TestMode */
	
	/* 1. Normal      */
	Transmit_SPI (0x0C , 0x11);
	/* 2. Scan Limit  */
	Transmit_SPI (0x1B, 0x07);
	/* 3. DeCode Mode */
	Transmit_SPI (0x19 , 0xFF);
	/* 4. INTENSITY   */
	Transmit_SPI (0x1A , 0x1F);
	/* 5. Display     */
	Transmit_SPI (0x1F , 0x00);
}

/* Function transmit data */
void Transmit_Point (char address, char point  ,char data)
{
	while ( !(LPSPI_0->SR & (1u << 0)) );
	LPSPI_0->TDR = (address << 8) | (point << 7)| data ;
}

void Transmit_SPI (char address ,char data)
{
	while ( !(LPSPI_0->SR & (1u << 0)) );
	LPSPI_0->TDR = (address << 8) | data ;
}

