//
//  main.cpp
//  orion
//
//  Created by Артём Оконечников on 24.10.2020.
//

#include <cstdint>
#include <fstream>

#include "Bus.hpp"
#include "Cpu.hpp"

#define OFFSET 0x0100

int main(int argc, const char * argv[])
{
    
    std::cout << (65535 - (65535 % 9)) << std::endl;
//    std::shared_ptr<IODevice> bus;
//    Cpu cpu;
//
//    std::ifstream file("exerciser/8080EXM.com", std::ios::in | std::ios::binary);
//    uint16_t offset = OFFSET;
//
//    bus -> write(0x0000, 0xD3);
//    bus -> write(0x0001, 0x00);
//
//    bus -> write(0x0005, 0xD3);
//    bus -> write(0x0006, 0x01);
//    bus -> write(0x0007, 0xC9);
//
//    char buffer = 0x00;
//    while (!file.eof())
//    {
//        file.read(&buffer, 1);
//        bus -> write(offset++, buffer);
//    }
//
//    file.close();
//
//    cpu.connect(bus);
//    cpu.setCounter(OFFSET);
//
//    while (true)
//    {
//        cpu.clock();
//    }
//
//    return 0;
}
