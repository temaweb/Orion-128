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

#include "i8080.hpp"

void log( uint16_t pcl, i8080 * cpu )
{
    using namespace std;

    cout << uppercase;

    cout << setfill(' ') << "0x" << setfill('0') << setw(4) << right << hex << unsigned(pcl);
    cout << setfill(' ') << " "  << setfill('0') << setw(2) << right << hex << unsigned(cpu -> opcode);

    if (cpu -> lookup[cpu ->opcode].addrmod == &i8080::DIR)
    {
        uint16_t lo = cpu ->read(pcl + 1);
        uint16_t hi = cpu ->read(pcl + 2);

        uint8_t value = cpu ->read((hi << 8) | lo);

        cout << setfill(' ') << " "  << setfill('0') << setw(2) << right << hex << unsigned(lo);
        cout << setfill(' ') << " "  << setfill('0') << setw(2) << right << hex << unsigned(hi);
        cout << setfill(' ') << " $" << setfill('0') << setw(2) << right << hex << unsigned(value);

        cout << setfill(' ') << setw(6);
    }
    else if (cpu ->lookup[cpu ->opcode].addrmod == &i8080::IMM)
    {
        uint8_t value = cpu ->read(pcl + 1);
        cout << setfill(' ') << " " << setfill('0') << setw(2) << right << hex << unsigned(value);
        cout << setfill(' ') << setw(13);
    }
    else
    {
        cout << setfill(' ') << setw(16);
    }

    cout << right << cpu ->lookup[cpu ->opcode].name;

    cout << "  A:"  << "0x" << setfill('0') << setw(2) << right << unsigned(cpu ->reg[cpu ->A]);
    cout << "  B:"  << "0x" << setfill('0') << setw(2) << right << unsigned(cpu ->reg[cpu ->B]);
    cout << "  C:"  << "0x" << setfill('0') << setw(2) << right << unsigned(cpu ->reg[cpu ->C]);
    cout << "  D:"  << "0x" << setfill('0') << setw(2) << right << unsigned(cpu ->reg[cpu ->D]);
    cout << "  E:"  << "0x" << setfill('0') << setw(2) << right << unsigned(cpu ->reg[cpu ->E]);
    cout << "  H:"  << "0x" << setfill('0') << setw(2) << right << unsigned(cpu ->reg[cpu ->H]);
    cout << "  L:"  << "0x" << setfill('0') << setw(2) << right << unsigned(cpu ->reg[cpu ->L]);


    cout << "  $"  << setfill('0') << setw(2) << right << unsigned(cpu ->read(cpu ->readpair(cpu ->BC)));
    cout << "  $"  << setfill('0') << setw(2) << right << unsigned(cpu ->read(cpu ->readpair(cpu ->DE)));
    cout << "  $"  << setfill('0') << setw(2) << right << unsigned(cpu ->read(cpu ->readpair(cpu ->HL)));

    cout << "  S="  << unsigned(cpu ->sr.GetSign());
    cout << "  Z="  << unsigned(cpu ->sr.GetZero());
    cout << "  AC=" << unsigned(cpu ->sr.GetAux());
    cout << "  P="  << unsigned(cpu ->sr.GetParity());
    cout << "  C="  << unsigned(cpu ->sr.GetCarry());

    cout << "  0x" << std::setfill('0') << std::setw(4) << std::right << unsigned(cpu ->sp);
    cout << endl;
}

#endif /* Logger_hpp */
