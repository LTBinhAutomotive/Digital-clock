typedef struct
{
	volatile unsigned int CSR;
	volatile unsigned int RVR;
	volatile unsigned int CVR;
	volatile const unsigned int CALIB;
} TIMER_ADDRESS;

#define SYST_BASE			0xE000E010
#define SYST				((TIMER_ADDRESS*)SYST_BASE)