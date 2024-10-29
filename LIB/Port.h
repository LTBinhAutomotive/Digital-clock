typedef struct
{
	volatile unsigned int PCR0;
	volatile unsigned int PCR1;
	volatile unsigned int PCR2;
	volatile unsigned int PCR3;
	volatile unsigned int PCR4;
	volatile unsigned int PCR5;
	volatile unsigned int PCR6;
	volatile unsigned int PCR7;
	volatile unsigned int PCR8;
	volatile unsigned int PCR9;
	volatile unsigned int PCR10;
	volatile unsigned int PCR11;
	volatile unsigned int PCR12;
	volatile unsigned int PCR13;
	volatile unsigned int PCR14;
	volatile unsigned int PCR15;
	volatile unsigned int PCR16;
	volatile unsigned int PCR17;
	volatile unsigned int PCR18;
	volatile unsigned int PCR19;
	volatile unsigned int PCR20;
	volatile unsigned int PCR21;
	volatile unsigned int PCR22;
	volatile unsigned int PCR23;
	volatile unsigned int PCR24;
	volatile unsigned int PCR25;
	volatile unsigned int PCR26;
	volatile unsigned int PCR27;
	volatile unsigned int PCR28;
	volatile unsigned int PCR29;
	volatile unsigned int PCR30;
	volatile unsigned int PCR31;
	volatile unsigned int GPCLR;
	volatile unsigned int GPCHR;
	volatile unsigned int GICLR;
	volatile unsigned int GICHR;
	char a[16];
	volatile unsigned int ISFR;
	char b[28];
	volatile unsigned int DFER;
	volatile unsigned int DFCR;
	volatile unsigned int DFWR;
} PORT;

#define PORTA_BASE		0x40049000
#define PORTB_BASE    0x4004A000
#define PORTC_BASE    0x4004B000
#define PORTD_BASE    0x4004C000
#define PORTE_BASE    0x4004D000

#define PORTA ((PORT*)PORTA_BASE)
#define PORTB ((PORT*)PORTB_BASE)
#define PORTC ((PORT*)PORTC_BASE)
#define PORTD ((PORT*)PORTD_BASE)
#define PORTE ((PORT*)PORTE_BASE)
