typedef struct
{
	volatile unsigned int VERID;
	volatile unsigned int PARAM;
	char empty1[8];
	volatile unsigned int CR;
	volatile unsigned int SR;
	volatile unsigned int IER;
	volatile unsigned int DER;
	volatile unsigned int CFGR0;
	volatile unsigned int CFGR1;
	char empty2[8];
	volatile unsigned int DMR0;
	volatile unsigned int DMR1;
	char empty3[8];
	volatile unsigned int CCR;
	char empty4[20];
	volatile unsigned int FCR;
	volatile unsigned int FSR;
	volatile unsigned int TCR;
	volatile int TDR;
	char empty5[8];
	volatile unsigned int RSR;
	volatile unsigned int RDR;
} LPSPI_ADDRESS;


#define LPSPI0_BASE		0x4002C000
#define LPSPI1_BASE		0x4002D000
#define LPSPI2_BASE		0x4002E000

#define LPSPI_0  ( (LPSPI_ADDRESS*)LPSPI0_BASE )
#define LPSPI_1  ( (LPSPI_ADDRESS*)LPSPI1_BASE )
#define LPSPI_2  ( (LPSPI_ADDRESS*)LPSPI2_BASE )
