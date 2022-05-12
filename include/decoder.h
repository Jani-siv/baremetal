#pragma once
#include <iostream>
#include "../include/opcodes.h"

class decoder{
    public:
        decoder();
        ~decoder();
        std::uint32_t decodeData(std::uint32_t data);
        unsigned int decodeOP(std::uint16_t data);
        std::uint8_t getImm5(std::uint16_t data);
        std::uint8_t getImm8(std::uint16_t data);

};
