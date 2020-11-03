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
        S  = (1 << 7), // S
        Z  = (1 << 6), // Z
        AC = (1 << 4), // AC
        P  = (1 << 2), // P
        C  = (1 << 0)  // C
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
        SetFlag(Z, value == 0x00);
    }
    
    void SetFlagSign (uint16_t value)
    {
        SetFlag(S, value & 0x80);
    }
    
    void SetFlagAux (uint16_t value)
    {
        SetFlag(AC, value > 0xF);
    }
    
    void SetFlagParity (uint16_t value)
    {
        value ^= value >> 8;
        value ^= value >> 4;
        value ^= value >> 2;
        value ^= value >> 1;
        
        SetFlag(P, (~value) & 1);
    }
    
    void SetFlagCarry (uint16_t value)
    {
        SetFlag(C, value > 255);
    }
    
    void SetAllFlags (uint16_t value)
    {
        SetFlagSign   (value);
        SetFlagZero   (value);
        SetFlagAux    (value);
        SetFlagCarry  (value);
        SetFlagParity (value);
    }
    
    uint8_t GetCarryFlag()
    {
        return (sr & C);
    }
};

#endif /* i8080Flags_hpp */
