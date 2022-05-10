//cpu PSR { APSR flags} page 93 
#define ZFLAG 0x0
#define CFLAG 0x1
#define NFLAG 0x2
#define VFLAG 0x4

#define SETFLAG(byte,nbit)  ((byte) |= (1<<(nbit)))
#define UNSETFLAG(byte,nbit) ((byte) &= ~(1<<(nbit)))


