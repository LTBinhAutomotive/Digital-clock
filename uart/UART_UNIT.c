#include"../LIB/Port.h"
#include"../LIB/PCC.h"
#include"../LIB/UART.h"
#include"../LIB/NVIC.h"
#include"UART_UNIT.h"

void CONFIG_UART(void)
{
	/*Setting Tx/Rx pin */
	PCC->PortC   |=  (1u<<30); 	               //CGC Set bit 30 to 1 
	PORTC->PCR6  &= ~(7u<<8); 								 //clear MUX 8-10
	PORTC->PCR6  |=  (1u<<9);									 //Set 0-1-0 -> ALT2
	PORTC->PCR7  &= ~(7u<<8); 								 //clear MUX 8-10
	PORTC->PCR7  |=  (1u<<9);									 //Set 0-1-0 -> ALT2
	
	/*Select source LPUAR0*/
	PCC->LPUART1 &= ~(1u<<30);  							 //Disable bit 30 CGC
	PCC->LPUART1 &= ~(7u<<24);  							 //clear bit 24-26 PCS
	PCC->LPUART1 |=  (6u<<24);  						 	 //clock option 6
	PCC->LPUART1 |=  (1u<<30);  							 //enable CGC
	
	/*Setting baud rate  38400*/
	static volatile unsigned int nTemp;
	nTemp = LPUART_1->BAUD;
	nTemp &= ~(31u << 24);
	nTemp |=  (8u << 24);                       //OSR = 9 
	nTemp &= ~(0x1FFFu << 0); 
	nTemp |=  (52u << 0);                       //BSR = 52.08333
	LPUART_1->BAUD = nTemp;                     //52 = 18MHz / ( 38400* 9)
	             
	/*Setting Frame*/
	LPUART_1->CTRL &= ~(1u<<4);                 //Set data characters number: CTRL[M]
	LPUART_1->CTRL |=  (1u<<4);                 //9 bit data
	LPUART_1->CTRL &= ~(1u<<1);                 //Set parity bit: CTRL[PE]
	LPUART_1->CTRL |=  (1u<<1);                 //select enable parity
	LPUART_1->CTRL &= ~(1u<<0);                 //select parity : CTRL[PT] -->even parity
	
	/*Enable transmitter & receiver*/
	LPUART_1->CTRL &= ~((1u<<18)|(1u<<19));     //Clear bit 18 19
	LPUART_1->CTRL |=  (1u<<19);  							//Transmitter Enable: CTRL[TE]
	LPUART_1->CTRL |=  (1u<<18);  							//Receiver Enable: CTRL[RE]
	
	/*set enable Receiver interrupt*/
	NVIC->ISER1    &= ~(1u << 1);
	NVIC->ISER1    |=  (1u << 1);               //ID 33 --> bit 1
	LPUART_1->CTRL &= ~(1u << 21);              //clear bit Receiver Interrupt Enable
	LPUART_1->CTRL |=  (1u << 21);              //Receiver Interrupt Enable
	
	/*set enable IDLE interrupt*/
	LPUART_1->CTRL &= ~(1u << 20);              //clear bit IDLE Interrupt Enable
	LPUART_1->CTRL |=  (1u << 20);              //IDLE Interrupt Enable
}


void UART_SendCharacter(char data)
{
	while ( !( LPUART_1->STAT & (1<<23) ) );
	LPUART_1->DATA = data;
}

void UART_SendString(char *string)
{
	int z = 0;
	while(string[z] != '\0')
	{
		UART_SendCharacter(string[z]);	
		z++;
	}
}
