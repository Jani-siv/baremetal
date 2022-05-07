#include <iostream>
#include "../include/memory.h"
#include "../include/cpu.h"
int main()
{
    core::memory sharedmemory;
    core::memory * ptr = &sharedmemory;
    cpu cpuA(ptr);
	std::cout<<"help needed"<<std::endl;    
    return 0;
}
