void WriteSCG_SOSC(volatile unsigned int EREFS, volatile unsigned int HGO, volatile unsigned int RANGE, volatile unsigned int SOSCDIV1, volatile unsigned int SOSCDIV2);

void WriteSCG_SPLL(volatile unsigned int SOURCE, volatile unsigned int PREDIV, volatile unsigned int MULT, volatile unsigned int SPLLDIV1, volatile unsigned int SPLLDIV2);

void WriteSCG_xCCG(volatile unsigned int *xCCR, volatile unsigned int SCS, volatile unsigned int DIVCORE, volatile unsigned int DIVBUS, volatile unsigned int DIVSLOW);

void WriteSCG_IRC(volatile unsigned int *xIRC, volatile unsigned int RANGE, volatile unsigned int xIRCDIV1, volatile unsigned int xIRCDIV2);
