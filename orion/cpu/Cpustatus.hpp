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

class Cpustatus
{
private:
    
    uint8_t status = 0x02; // [S Z 0 AC 0 P 1 C]
    
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
            status |= flag;
        } else {
            status &= ~flag;
        }
    }
    
public:
    
    Cpustatus() {};
    ~Cpustatus() {};
    
public:
    
    Cpustatus& operator=(const uint8_t & st)
    {
        status = (st & 0xD7) | 0x02;
        return *this;
    }

    operator uint8_t ()
    {
        return status;
    }
    
public:

    void SetSign (bool flag)
    {
        SetFlag(S, flag);
    }
    
    void SetZero (bool flag)
    {
        SetFlag(Z, flag);
    }
    
    void SetAux (bool flag)
    {
        SetFlag(AC, flag);
    }
    
    void SetParity (bool flag)
    {
        SetFlag(P, flag);
    }
    
    void SetCarry (bool flag)
    {
        SetFlag(C, flag);
    }
    
public:
    
    void SetSign (uint16_t value)
    {
        SetSign((bool)(value & 0x0080));
    }
    
    void SetZero (uint16_t value)
    {
        SetZero((value & 0x00FF) == 0x0000);
    }
    
    void SetAux (uint16_t value)
    {
        SetAux((value & 0x010) != 0);
    }
    
    void SetParity (uint16_t value)
    {
        value &= 0x00FF;
        
        value ^= value >> 4;
        value ^= value >> 2;
        value ^= value >> 1;
        
        SetParity((bool)((~value) & 1));
    }
    
    void SetCarry (uint16_t value)
    {
        SetCarry((value & 0x100) != 0);
    }
    
    void InvertCarry()
    {
        status ^= C;
    }
    
public:
    
    void SetAllFlags (uint16_t value)
    {
        SetCarry    (value);
        SetAuxFlags (value);
    }
    
    void SetAuxFlags (uint16_t value)
    {
        SetAux      (value);
        SetDecFlags (value);
    }
    
    void SetDecFlags (uint16_t value)
    {
        SetSign    (value);
        SetZero    (value);
        SetParity  (value);
    }
    
public:
    
    uint8_t GetSign()
    {
        return (status & S) >> 7;
    }
    
    uint8_t GetZero()
    {
        return (status & Z) >> 6;
    }
    
    uint8_t GetAux()
    {
        return (status & AC) >> 4;
    }
    
    uint8_t GetParity()
    {
        return (status & P) >> 2;
    }
    
    uint8_t GetCarry()
    {
        return (status & C);
    }
};

#endif /* i8080Flags_hpp */
