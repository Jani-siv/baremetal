#include "../include/memory.h"

memory::memory()
{
 this->initSIO();
}
memory::~memory()
{
}
void memory::initMemory()
{
    for (int i = 0; i < ROMSIZE; i++)
    {
      this->ROM[i] = 0x0;
    }

}

void memory::initSIO()
{
    for (int i = 0; i < SIOREGISTERS; i++)
    {
        this->SIO[i] = 0x0;
    }
}

short memory::getCPUID()
{
    short ID = (this->SIO[0] & 0x1);
    this->SIO[0] ^= 1UL << 0;
    return ID;
}
