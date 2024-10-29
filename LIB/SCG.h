typedef struct
{
	volatile unsigned int VERID;
	char empty1[8];
	volatile unsigned int PARAM;
	volatile unsigned int CSR;
	volatile unsigned int RCCR;
	volatile unsigned int VCCR;
	volatile unsigned int HCCR;
	volatile unsigned int CLKOUTCNFG;
	char empty2[220];
	volatile unsigned int SOSCCSR;
	volatile unsigned int SOSCDIV;
	volatile unsigned int SOSCCFG;
	char empty3[244];
	volatile unsigned int SIRCCSR;
	volatile unsigned int SIRCDIV;
	volatile unsigned int SIRCCFG;
	char empty4[244];
	volatile unsigned int FIRCCSR;
	volatile unsigned int FIRCDIV;
	volatile unsigned int FIRCCFG;
	char empty5[756];
	volatile unsigned int SPLLCSR;
	volatile unsigned int SPLLDIV;
	volatile unsigned int SPLLCFG;
} SCG_REG;

#define SCG_REG_BASE		0x40064000
#define SCG							((SCG_REG*)SCG_REG_BASE)
