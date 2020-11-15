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
#include "Video.hpp"
#include "Cpu.hpp"

#define OFFSET 0x0100

int main(int argc, const char * argv[])
{
    Bus bus;
    Video video;
    Cpu cpu;
    
    std::ifstream file("/Users/temaweb/Desktop/Орион-128/Orion-128/orion/cpu/tests/8080EXM.com", std::ios::in | std::ios::binary);
    uint16_t offset = OFFSET;

    bus.write(0x0000, 0xD3);
    bus.write(0x0001, 0x00);

    bus.write(0x0005, 0xD3);
    bus.write(0x0006, 0x01);
    bus.write(0x0007, 0xC9);

    char buffer = 0x00;
    while (!file.eof())
    {
        file.read(&buffer, 1);
        bus.write(offset++, buffer);
    }

    file.close();

    // video.connect(&bus);
    cpu.connect(&bus);
    cpu.setCounter(OFFSET);
    
    while (true)
    {
        cpu.clock();
    }
    
    return 0;
}
