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
    if (op == 0xB)
    {
        return PUSH;
    }

    std::cout<<"data: "<<data<<" op: "<<std::hex<<static_cast<int>(op)<<std::endl;
    
    return op;
}


