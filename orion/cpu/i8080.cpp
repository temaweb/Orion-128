//
//  i8080.cpp
//  orion
//
//  Created by Артём Оконечников on 29.10.2020.
//

#include "i8080.hpp"
#include "Bus.hpp"

i8080::i8080() : reg { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }
{
    lookup =
    {
        // NAME      CYCLES    OPERATION         ADDRMOD
        // ---------------------------------------------------
        
        // 0x0 - 0xF
        
        { "NOP",     4,        &i8080::NOP,      &i8080::IMP },
        { "LXI",     10,       &i8080::LXIB,     &i8080::IMM },
        { "STAX",    7,        &i8080::STAXB,    &i8080::IMP },
        
        // 0x1 - 0xF
        
        { "XXX",     4,        &i8080::XXX,      &i8080::IMP },
        { "LXI",     10,       &i8080::LXID,     &i8080::IMM },
        { "STAX",    7,        &i8080::STAXD,    &i8080::IMP }
        
        
    };
}

void i8080::clock()
{
    if (cycles > 0)
    {
        // Set additional delay?
        cycles--;
        
        return;
    }
    
    // Read operation code
    op = read(pc);
    
    // Increment counter
    pc++;
    
    // Set min program cycles
    cycles = lookup[op].cycles;
    
    // Set address mode
    (this->*lookup[op].addrmod)();
    
    // Execute operation and add extra cycles
    cycles += (this->*lookup[op].operate)();
}

#pragma mark -

uint8_t i8080::read(uint16_t address)
{
    return bus -> read(address);
}

void i8080::write(uint16_t address, uint8_t data)
{
    bus -> write(address, data);
}

void i8080::connect(Bus * bus)
{
    this -> bus = bus;
}

#pragma mark -

void i8080::IMP()
{
    
}

void i8080::IND()
{
    address = a;
}

void i8080::DIR()
{
    uint16_t lo = read(pc);
    pc++;
    uint16_t hi = read(pc);
    pc++;
    
    address = (hi << 8) | lo;
}

void i8080::IMM()
{
    address = pc++;
}

void i8080::HLM()
{
    uint16_t lo = reg[L];
    uint16_t hi = reg[H];
    
    address = (hi << 8) | lo;
}

#pragma mark -

uint8_t i8080::XXX()
{
    return 0;
}

// Code: NOP
// Operation: No-operation
uint8_t i8080::NOP()
{
    return 0;
}

#pragma mark -
#pragma mark Move, Load, Store

// Code: MOV r1, r2
// Operation: (r2) → r1
// Description: Move register to register
uint8_t i8080::MOVRR()
{
    reg[(op & DDD) >> 3] = reg[op & SSS];
    return 0;
}

// Code: MOV M, r
// Operation: (r) → [(HL)]
// Description: Move register to memory
uint8_t i8080::MOVMR()
{
    auto src = reg[op & SSS];
    write(address, src);
    
    return 0;
}

// Code: MOV r, M
// Operation: [(HL)] → r
// Description: Move memory to register
uint8_t i8080::MOVRM()
{
    reg[(op & DDD) >> 3] = read(address);
    return 0;
}

// Code: MVI r, D8
// Operation: D8 → r
// Description: Move immediate register
uint8_t i8080::MVIR()
{
    reg[(op & DDD) >> 3] = read(address);
    return 0;
}

// Code: MVI M, D8
// Operation: D8 → [(HL)]
// Description: Move immediate memory
uint8_t i8080::MVIM()
{
    auto src = read(address);
    
    uint16_t lo = reg[L];
    uint16_t hi = reg[H];

    write((hi << 8) | lo, src);
    
    return 0;
}

// Code: LXI RP
// Operation: D16 → RP
// Description: Load immediate register pair B & C
uint8_t i8080::LXIB()
{
    reg[C] = read(address + 0);
    reg[B] = read(address + 1);
    
    pc++;
    
    return 0;
}

// Code: LXI RP
// Operation: D16 → RP
// Description: Load immediate register pair D & E
uint8_t i8080::LXID()
{
    reg[E] = read(address + 0);
    reg[D] = read(address + 1);
    
    pc++;
    
    return 0;
}

// Code: LXI RP
// Operation: D16 → RP
// Description: Load immediate register pair H & L
uint8_t i8080::LXIH()
{
    reg[L] = read(address + 0);
    reg[H] = read(address + 1);
    
    pc++;
    
    return 0;
}

// Code: STAX B
// Operation: (A) → [(RP)]
// Description: Store A indent
uint8_t i8080::STAXB()
{
    uint16_t lo = reg[C];
    uint16_t hi = reg[B];

    write((hi << 8) | lo, a);
    
    return 0;
}

// Code: STAX D
// Operation: (A) → [(RP)]
// Description: Store A indent
uint8_t i8080::STAXD()
{
    uint16_t lo = reg[E];
    uint16_t hi = reg[D];

    write((hi << 8) | lo, a);
    
    return 0;
}

// Code: LDAX B
// Operation: [(RP)] → A
// Description: Load A indirect
uint8_t i8080::LDAXB()
{
    uint16_t lo = reg[C];
    uint16_t hi = reg[B];

    a = read((hi << 8) | lo);
    
    return 0;
}

// Code: LDAX D
// Operation: [(RP)] → A
// Description: Load A indirect
uint8_t i8080::LDAXD()
{
    uint16_t lo = reg[E];
    uint16_t hi = reg[D];

    a = read((hi << 8) | lo);
    
    return 0;
}

// Code: STA A16
// Operation: (A) → [(A16)]
// Description: Store A direct
uint8_t i8080::STA()
{
    write(address, a);
    return 0;
}

// Code: LDA A16
// Operation: [(A16)] → A
// Description: Load A direct
uint8_t i8080::LDA()
{
    a = read(address);
    return 0;
}

// Code: SHLD A16
// Operation: (L) → [A16], (H) → [A16+1]
// Description: Store H & L direct
uint8_t i8080::SHLD()
{
    write(address + 0, reg[L]);
    write(address + 1, reg[H]);
    
    return 0;
}

// Code: LHLD A16
// Operation: [A16] → L, [A16+1] → H
// Description: Load H & L direct
uint8_t i8080::LHLD()
{
    reg[L] = read(address + 0);
    reg[H] = read(address + 1);
    
    return 0;
}

// Code: XCHG
// Operation: (HL) ↔ (DE)
// Description: Echange D & E, H & L registers
uint8_t i8080::XCHG()
{
    auto exchange = [&](uint8_t x, uint8_t y)
    {
        x ^= y;
        y ^= x;
        x ^= y;
    };
    
    exchange(reg[D], reg[H]);
    exchange(reg[E], reg[L]);
    
    return 0;
}
