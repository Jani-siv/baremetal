#include "../include/cpu.h"
#include <iostream>
#include <vector>
#include <string>

void runAllTests()
{
    std::cout<<"hello"<<std::endl;
}

int main(int argc, char *argv[])
{
    cpu cpuA;
    std::vector<std::string> arguments(argv, argv + argc);

for (std::string arg : arguments)
{
    if (arg == "-all")
    {
        runAllTests();        
    }
}
return 0;
}
