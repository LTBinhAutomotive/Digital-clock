typedef struct
{
	volatile unsigned int PDOR;
	volatile unsigned int PSOR;
	volatile unsigned int PCOR;
	volatile unsigned int PTOR;
	volatile unsigned int PDIR;
	volatile unsigned int PDDR;
	volatile unsigned int PIDR;
}GPIO;

#define GPIOA_BASE		0x400FF000
#define GPIOB_BASE  	0x400FF040
#define GPIOC_BASE		0x400FF080
#define GPIOD_BASE		0x400FF0C0
#define GPIOE_BASE  	0x400FF100

#define GPIOA 				((GPIO*)GPIOA_BASE)
#define GPIOB 				((GPIO*)GPIOB_BASE)
#define GPIOC 				((GPIO*)GPIOC_BASE)
#define GPIOD				((GPIO*)GPIOD_BASE)
