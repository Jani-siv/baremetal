#include <iostream>
#include "../include/memory.h"
#include "../include/cpu.h"
int main()
{
    memory sharedmemory;
    memory * ptr = &sharedmemory;
    cpu cpuA(ptr);
	std::cout<<"help needed"<<std::endl;    
    return 0;
}
