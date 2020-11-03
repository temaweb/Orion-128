//
//  i8080Flags.hpp
//  orion
//
//  Created by Артём Оконечников on 01.11.2020.
//

#ifndef i8080Flags_hpp
#define i8080Flags_hpp

#include <stdio.h>
#include <cstdint>

class Status
{
private:
    
    uint8_t sr = 0x00;
    
    enum Flags
    {
        Sign    = (1 << 7), // S
        Zero    = (1 << 6), // Z
        Aux     = (1 << 4), // AC
        Parity  = (1 << 2), // P
        Carry   = (1 << 0)  // C
    };
    
    void SetFlag(Flags flag, bool value)
    {
        if (value) {
            sr |= flag;
        } else {
            sr &= ~flag;
        }
    }
    
public:
    Status() {};
    ~Status() {};
    
public:
    
    void SetFlagZero (uint16_t value)
    {
        SetFlag(Zero, value == 0x00);
    }
    
    void SetFlagSign (uint16_t value)
    {
        SetFlag(Sign, value & 0x80);
    }
    
    void SetFlagAux (uint16_t value)
    {
        SetFlag(Aux, value > 0xF);
    }
    
    void SetFlagParity (uint16_t value)
    {
        value ^= value >> 8;
        value ^= value >> 4;
        value ^= value >> 2;
        value ^= value >> 1;
        
        SetFlag(Parity, (~value) & 1);
    }
    
    void SetFlagCarry (uint16_t value)
    {
        SetFlag(Carry, value > 255);
    }
};

#endif /* i8080Flags_hpp */
