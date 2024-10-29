typedef struct
{
	volatile unsigned int VERID;
	volatile unsigned int PARAM;
	volatile unsigned int GLOBAL;
	volatile unsigned int PINCFG;
	volatile unsigned int BAUD;
	volatile unsigned int STAT;
	volatile unsigned int CTRL;
	volatile unsigned int DATA;
	volatile unsigned int MATCH;
	volatile unsigned int MODIR;
	volatile unsigned int FIFO;
	volatile unsigned int WATER;

} LPUART_Type;

#define LPUART_0_base_address (0x4006A000)
#define LPUART_1_base_address (0x4006B000)
#define LPUART_2_base_address (0x4006C000)

#define LPUART_0 ((LPUART_Type*)LPUART_0_base_address)
#define LPUART_1 ((LPUART_Type*)LPUART_1_base_address)
#define LPUART_2 ((LPUART_Type*)LPUART_2_base_address)
