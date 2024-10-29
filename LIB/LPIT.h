typedef struct
{
	volatile unsigned int VERID;
	volatile unsigned int PARAM;
	volatile unsigned int MCR;
	volatile unsigned int MSR;
	volatile unsigned int MIER;
	volatile unsigned int SETTEN;
	volatile unsigned int CLRTEN;
	char empty1[4];
	volatile unsigned int TVAL0;
	volatile unsigned int CVAL0; 
	volatile unsigned int TCTRL0;
	char empty2[4];
	volatile unsigned int TVAL1;
	volatile unsigned int CVAL1;
	volatile unsigned int TCTRL1;
	char empty3[4];
	volatile unsigned int TVAL2;
	volatile unsigned int CVAL2;
	volatile unsigned int TCTRL2;
	char empty4[4];
	volatile unsigned int TVAL3;
	volatile unsigned int CVAL3;
	volatile unsigned int TCTRL3;
} LPIT_ADDRESS;

#define LPIT_base_address   0x40037000

#define LPIT ( (LPIT_ADDRESS*)LPIT_base_address )
