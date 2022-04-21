#include "../include/memory.h"

memory::memory()
{
 this->initSIO();
}
memory::~memory()
{
}
char* memory::readMemory(std::uint32_t address)
{
    if (address < SRAMBASE)
    {
        return &this->ROM[address];
    }
    else if (address >= SRAMBASE && address < USBRAMBASE)
    {
        address -= SRAMBASE;
        return &this->SRAM[address];
    }
    else if (address >= USBRAMBASE)
    {
        address -= USBRAMBASE;
        return &this->USBRAM[address];
    }
    std::cout<<"Memory error"<<std::endl;
return nullptr;
}
void memory::writeMemory(std::uint32_t address,const char &value)
{
    if (address < SRAMBASE)
    {
        this->writeRom(address, value);
    }
    else if (address >= SRAMBASE && address < USBRAMBASE)
    {
        this->writeSram(address, value);
    }
    else if (address >= USBRAMBASE)
    {
        this->writeUsbram(address, value);
    }

}

void memory::writeRom(const std::uint32_t address,const char &value)
{
    std::memcpy(&this->ROM[address],&value,sizeof(char));
}

void memory::writeSram(std::uint32_t address,const char &value)
{
   address -= SRAMBASE;
   std::memcpy(&this->SRAM[address],&value,sizeof(char));
}

void memory::writeUsbram(std::uint32_t address,const char &value)
{
    address -= USBRAMBASE;
    std::cout<<"From usb ram address after - : "<<address<<" Value: "<<value<<std::endl;
    std::memcpy(&this->USBRAM[address],&value,sizeof(char));
}

void memory::initMemory()
{
    for (int i = 0; i < ROMSIZE; i++)
    {
      this->ROM[i] = 0x0;
    }
    for (int i = 0; i < SRAMSIZE; i++)
    {
        this->SRAM[i] = 0x0;
    }
    for (int i = 0; i < USBRAMSIZE; i++)
    {
        this->USBRAM[i] = 0x0;
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
