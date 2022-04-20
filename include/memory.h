#pragma once
#include <iostream>
#define ROMSIZE 16000
#define SRAMSIZE 264000
#define USBRAMSIZE 3000
#define ROMBASE 0x00000000
#define SRAMBASE 0x20000000
#define USBRAMBASE 0x50100400
#define SIOBASE 0xd0000000
#define SIOREGISTERS 94

class memory{
    public:
        memory();
        ~memory();
        short getCPUID();
    private:
        void initSIO();
        unsigned char ROM[ROMSIZE];
        unsigned char SRAM[SRAMSIZE];
        unsigned char USBRAM[USBRAMSIZE];
        std::uint32_t SIO[SIOREGISTERS];
        void initMemory();
};

