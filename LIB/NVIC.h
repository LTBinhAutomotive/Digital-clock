typedef struct
{
	volatile unsigned int ISER0;
	volatile unsigned int ISER1;
	volatile unsigned int ISER2;
	volatile unsigned int ISER3;
	volatile unsigned int ISER4;
	volatile unsigned int ISER5;
	volatile unsigned int ISER6;
	volatile unsigned int ISER7;
} NVIC_ISER_type;

#define  NVIC_ISER_base_address  0xE000E100

#define  NVIC ((NVIC_ISER_type*) NVIC_ISER_base_address )
