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
#define XIPCACHESIZE 16000
#define SIOREGISTERS 94

namespace core{

    class memory{
    public:
        void initMemory();
        short getCPUID();
        void writeMemory(std::uint32_t address,const std::uint16_t &value);
        void writeMemory32(std::uint32_t, const std::uint32_t &value);
        std::uint16_t readMemory(std::uint32_t address);
        std::uint32_t readMemory32(std::uint32_t address);

    private:
        void writeRom(const std::uint32_t address,const std::uint16_t &value);
        void writeSram(std::uint32_t address, const std::uint16_t &value);
        void writeUsbram(std::uint32_t address, const std::uint16_t &value);
        uint32_t *stackBaseAddress = nullptr;
        uint32_t *tempStackBaseAddress = nullptr;
        void initSIO();
        std::uint8_t ROM[ROMSIZE];
        std::uint8_t SRAM[SRAMSIZE];
        std::uint8_t USBRAM[USBRAMSIZE];
        char XIPCACHE[XIPCACHESIZE];
        std::uint32_t SIO[SIOREGISTERS];
};
}

namespace core{
    namespace systemMemory{
        extern core::memory sysMem;
    }
}

