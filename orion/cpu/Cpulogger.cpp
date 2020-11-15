//
//  Logger.hpp
//  orion
//
//  Created by Артём Оконечников on 11.11.2020.
//

#ifndef Logger_hpp
#define Logger_hpp

#include <stdio.h>
#include <cstdint>
#include <iomanip>
#include <iostream>

#include "Cpu.hpp"

template<class T>
void print(int width, std::string prefix, T value)
{
    using namespace std;
    
    cout << setfill(' ') << prefix
         << setfill('0') << setw(width) << right << hex << unsigned(value);
}

void printDivider(int width)
{
    using namespace std;
    
    cout << setfill(' ') << setw(width);
}

void log(uint16_t counter, Cpu * cpu)
{
    using namespace std;

    auto opcode  = cpu -> opcode;
    auto addrmod = cpu -> lookup[opcode].addrmod;
    
    cout << uppercase;

    print(4, "0x", counter);
    print(2,  " ", opcode);

    if (addrmod == &Cpu::DIR)
    {
        auto lo = cpu -> read(counter + 1);
        auto hi = cpu -> read(counter + 2);

        auto value = cpu -> read((hi << 8) | lo);

        print(2, " ",  lo);
        print(2, " ",  hi);
        print(2, " $", value);

        printDivider(6);
    }
    else if (addrmod == &Cpu::IMM)
    {
        auto value = cpu -> read(counter + 1);
        
        print(2, " ", value);
        printDivider(13);
    }
    else
    {
        printDivider(16);
    }

    cout << right << cpu -> lookup[opcode].name;

    print(2, " A:", cpu -> registers[cpu -> A]);
    print(2, " B:", cpu -> registers[cpu -> B]);
    print(2, " C:", cpu -> registers[cpu -> C]);
    print(2, " D:", cpu -> registers[cpu -> D]);
    print(2, " E:", cpu -> registers[cpu -> E]);
    print(2, " H:", cpu -> registers[cpu -> H]);
    print(2, " L:", cpu -> registers[cpu -> L]);

    auto printReg = [&](uint8_t index)
    {
        auto address = cpu -> readpair(index);
        auto value   = cpu -> read(address);
        
        print(2, " $", value);
    };
    
    printReg(cpu -> BC);
    printReg(cpu -> DE);
    printReg(cpu -> HL);

    cout << "  S="  << unsigned(cpu ->status.GetSign());
    cout << "  Z="  << unsigned(cpu ->status.GetZero());
    cout << "  AC=" << unsigned(cpu ->status.GetAux());
    cout << "  P="  << unsigned(cpu ->status.GetParity());
    cout << "  C="  << unsigned(cpu ->status.GetCarry());

    print(4, "  0x", cpu -> stack);
    cout << endl;
}

#endif /* Logger_hpp */
