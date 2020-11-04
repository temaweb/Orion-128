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
    
    uint8_t sr = 0x02;
    
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
    
    Status& operator=(const uint8_t & status)
    {
        sr = status;
        return *this;
    }
    
    Status& operator=(uint8_t&& status)
    {
        sr = status;
        return *this;
    }
    
    operator uint8_t() const
    {
        return sr;
    }
    
public:
    
    void SetZero (bool flag)
    {
        SetFlag(Z, flag);
    }
    
    void SetZero (uint16_t value)
    {
        SetZero((value & 0x00FF) == 0x0000);
    }
    
    void SetSign (uint16_t value)
    {
        SetFlag(S, value & 0x0080);
    }
    
    void SetAux (bool flag)
    {
        SetFlag(AC, flag);
    }
    
    void SetAux (uint16_t value)
    {
        SetAux(value > 0x000F);
    }
    
    void SetParity (uint16_t value)
    {
        value ^= value >> 8;
        value ^= value >> 4;
        value ^= value >> 2;
        value ^= value >> 1;
        
        SetFlag(P, (~value) & 1);
    }
    
    void SetCarry (bool flag)
    {
        SetFlag(C, flag);
    }
    
    void SetCarry (uint16_t value)
    {
        SetCarry(value > 0x00FF);
    }
    
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
    
    uint8_t GetCarry()
    {
        return (sr & C);
    }
    
    uint8_t GetZero()
    {
        return (sr & Z) >> 6;
    }
    
    uint8_t GetSign()
    {
        return (sr & S) >> 7;
    }
    
    uint8_t GetParity()
    {
        return (sr & P) >> 2;
    }
};

#endif /* i8080Flags_hpp */
