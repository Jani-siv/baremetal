#pragma once
#include <iostream>
#include <cstring>
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
        void writeMemory(std::uint32_t address,const char &value);
        char* readMemory(std::uint32_t address);

    private:
        void writeRom(const std::uint32_t address,const char &value);
        void writeSram(std::uint32_t address, const char &value);
        void writeUsbram(std::uint32_t address, const char &value);
        uint32_t *stackBaseAddress = nullptr;
        uint32_t *tempStackBaseAddress = nullptr;
        void initSIO();
        char ROM[ROMSIZE];
        char SRAM[SRAMSIZE];
        char USBRAM[USBRAMSIZE];
        std::uint32_t SIO[SIOREGISTERS];
        void initMemory();
};

