//
//  main.cpp
//  orion
//
//  Created by Артём Оконечников on 24.10.2020.
//

#include <iostream>
#include <cstdint>
#include <fstream>
#include <thread>
#include <chrono>

#include "Bus.hpp"
#include "i8080.hpp"

int main(int argc, const char * argv[])
{
    Bus bus;
    i8080 cpu;

    std::ifstream file("/Users/temaweb/Desktop/Орион-128/Orion-128/orion/cpu/tests/CPUTEST.COM", std::ios::in | std::ios::binary);
    char buffer = 0x00;
    uint16_t offset = 0x0100;

    bus.write(5, 0xC9);

    while (!file.eof())
    {
        file.read(&buffer, 1);
        bus.write(offset++, buffer);
    }

    file.close();

    cpu.connect(&bus);
    cpu.debug();

    return 0;
}
