#include "module.h"
#include "prototypes.h"

/*-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
/* SCG functions: These functions will write 32 bits to SGC registers */

void WriteSCG_SOSC(volatile unsigned int EREFS, volatile unsigned int HGO, volatile unsigned int RANGE, volatile unsigned int SOSCDIV1, volatile unsigned int SOSCDIV2)
{
	volatile unsigned int nTemp = SCG->SOSCCSR;
	
	/* Set bit 23 = 0, disable bit 0 */
	nTemp &= ~(1u << 23);
	SCG->SOSCCSR = nTemp;
	nTemp &= ~(1u << 0);
	SCG->SOSCCSR = nTemp;
	
	/* Set up SCG_SOSCCFG */
	nTemp = SCG->SOSCCFG;	
	nTemp &= ~((1u << 2) | (1u << 3) | (3u << 4));
	nTemp |= ((EREFS << 2u) | (HGO << 3u) | (RANGE << 4u));
	SCG->SOSCCFG = nTemp;
	
	/* Set up SCG_SOSCDIV */
	nTemp = SCG->SOSCDIV;
	nTemp &= ~((7u << 0) | (7u << 8));
	nTemp |= ((SOSCDIV1 << 0) | (SOSCDIV2 << 8));
	SCG->SOSCDIV = nTemp;
	
	/* Set bit 23 = 0, enable bit 0 */
	nTemp = SCG->SOSCCSR;
	nTemp &= ~(1u << 23);
	SCG->SOSCCSR = nTemp;
	nTemp |= (1u << 0);
	SCG->SOSCCSR = nTemp;
	
	/* Wait SOSC valid */
	while (!(SCG->SOSCCSR & (1u << 24))) {}
}

void WriteSCG_SPLL(volatile unsigned int SOURCE, volatile unsigned int PREDIV, volatile unsigned int MULT, volatile unsigned int SPLLDIV1, volatile unsigned int SPLLDIV2)
{
	volatile unsigned int nTemp = SCG->SPLLCSR;
	
	/* Set bit 23 = 0, disable bit 0 */
	nTemp &= ~(1u << 23);
	SCG->SPLLCSR = nTemp;
	nTemp &= ~(1u << 0);
	SCG->SPLLCSR = nTemp;
	
	/* Set up SCG_SPLLCFG */
	nTemp = SCG->SPLLCFG;
	nTemp &= ~((1u << 0) | (7u << 8) | (31u << 16));
	nTemp |= ((SOURCE << 0) | (PREDIV << 8) | (MULT << 16));
	SCG->SPLLCFG = nTemp;
	
	/* Set up SCG_SPLLDIV */
	nTemp = SCG->SPLLDIV;
	nTemp &= ~((7u << 0) | (7u << 8));
	nTemp |= ((SPLLDIV1 << 0) | (SPLLDIV2 << 8));
	SCG->SPLLDIV = nTemp;
	
	/* Set bit 23 = 0, enable bit 0 */
	nTemp = SCG->SPLLCSR;
	nTemp &= ~(1u << 23);
	SCG->SPLLCSR = nTemp;
	nTemp |= (1u << 0);
	SCG->SPLLCSR = nTemp;
	
	while (!(SCG->SPLLCSR & (1u << 24))) {}
}

void WriteSCG_xCCG(volatile unsigned int *xCCR, volatile unsigned int SCS, volatile unsigned int DIVCORE, volatile unsigned int DIVBUS, volatile unsigned int DIVSLOW)
{
	volatile unsigned int nTemp = *xCCR;
	
	nTemp &= ~((15u << 0) | (15u << 4) | (15u << 16) | (15u << 24));
	nTemp |= ((SCS << 24) | (DIVCORE << 16) | (DIVBUS << 4) | (DIVSLOW << 0));
	*xCCR = nTemp;
	
	while (SCG->CSR != *xCCR) {}	
}

void WriteSCG_IRC(volatile unsigned int *xIRC, volatile unsigned int RANGE, volatile unsigned int xIRCDIV1, volatile unsigned int xIRCDIV2)
{
	volatile unsigned int nTemp = *xIRC;		// Address of SCG_SIRCCSR or SCG_FIRCCSR
	
	/* Set bit 23 = 0, disable bit 0 */
	nTemp &= ~(1u << 23);
	*xIRC = nTemp;
	nTemp &= ~(1u << 0);
	*xIRC = nTemp;
	
	/* Set up SCG_xIRCCFG */
	nTemp = *(xIRC + 2);								// Address of SCG_xIRCCSR + 2 = Address of SCG_xIRCCFG
	nTemp &= ~(3u << 0);
	nTemp |= (RANGE << 0);
	*(xIRC + 2) = nTemp;
	
	/* Set up SCG_xIRCDIV */
	nTemp = *(xIRC + 1);								// Address of SCG_xIRCCSR + 1 = Address of SCG_xIRCDIV
	nTemp &= ~((7u << 0) | (7u << 8));
	nTemp |= ((xIRCDIV1 << 0) | (xIRCDIV2 << 8));
	*(xIRC + 1) = nTemp;
	
	/* Set bit 23 = 0, enable bit 0 */
	nTemp = *xIRC;
	nTemp &= ~(1u << 23);
	*xIRC = nTemp;
	nTemp |= (1u << 0);
	*xIRC = nTemp;
	
	while (!(*xIRC & (1u << 24))) {}
}

/*-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

