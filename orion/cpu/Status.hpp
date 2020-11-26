//
//  i8080Flags.hpp
//  orion
//
//  Created by Артём Оконечников on 01.11.2020.
//

#ifndef Status_hpp
#define Status_hpp

#include <stdio.h>
#include <cstdint>

class Status
{
private:
    
    // Default status
    static const uint8_t defaultState = 0x02;
    
    // CPU status flags
    // -----------------------------------
    // HI  7 - (S)  - Sign flag
    //     6 - (Z)  - Zero flag
    //     5 - (0)  - None / Always zero
    //     4 - (AC) - Auxiliary carry flag
    //     3 - (0)  - None / Always zero
    //     2 - (P)  - Parity flag
    //     1 - (1)  - None / Always set
    // LO  0 - (C)  - Carry flag
    
    uint8_t status = defaultState;
    
    enum Flags
    {
        S  = (1 << 7),
        Z  = (1 << 6),
        AC = (1 << 4),
        P  = (1 << 2),
        C  = (1 << 0)
    };

    void SetFlag(Flags flag, bool value);
  
public:
    
    Status& operator=(const uint8_t & status);
    operator uint8_t ();
    
public:

    void Reset();
    void InvertCarry();
    
    void SetSign   (bool flag);
    void SetSign   (uint16_t value);
    void SetZero   (bool flag);
    void SetZero   (uint16_t value);
    void SetAux    (bool flag);
    void SetAux    (uint16_t value);
    void SetParity (bool flag);
    void SetParity (uint16_t value);
    void SetCarry  (bool flag);
    void SetCarry  (uint16_t value);
    
    void SetAllFlags (uint16_t value);
    void SetAuxFlags (uint16_t value);
    void SetDecFlags (uint16_t value);
    
public:
    
    uint8_t GetSign();
    uint8_t GetZero();
    uint8_t GetAux();
    uint8_t GetParity();
    uint8_t GetCarry();
};

#endif /* Status_hpp */
