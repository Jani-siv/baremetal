#include "../include/decoder.h"

decoder::decoder()
{

}

decoder::~decoder()
{

}
std::uint32_t decoder::decodeData(std::uint32_t data)
{
    std::uint32_t test = data;
    return test;
}

unsigned int decoder::decodeOP(std::uint16_t data)
{
    uint8_t op = 0x00;
    op = (data >> 12) & 0xF;
std::cout<<"in decorder: "<<std::hex<<static_cast<int>(op)<<std::endl;
    if (op == LSLS)
    {
        return LSLS;
    }
    else if (op == MOVS)
    {
        return MOVS;
    }
    else if (op == STR)
    {
        return STR;
    }
    else if (op == PUSH)
    {
        return PUSH;
    }
    else if (op == BL)
    {
        return BL;
    }
    else
    {
    return 100;
    }
}


