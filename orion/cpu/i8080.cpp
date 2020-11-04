//
//  i8080.cpp
//  orion
//
//  Created by Артём Оконечников on 29.10.2020.
//

#include <iostream>

#include "i8080.hpp"
#include "Bus.hpp"

i8080::i8080() : reg { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }
{
    pairs[BC] = reg + B;
    pairs[DE] = reg + D;
    pairs[HL] = reg + H;
    pairs[SP] = (uint8_t *) &sp;
    
    lookup =
    {
        // NAME      CYCLES    OPERATION         ADDRMOD
        // ---------------------------------------------------
        
        // 0x0 - 0xF
        
        { "NOP",     4,        &i8080::NOP,      &i8080::IMP },
        { "LXI",     10,       &i8080::LXI,      &i8080::IMM },
        { "STAX",    7,        &i8080::STAX,     &i8080::IMP },
        { "INX",     5,        &i8080::INX,      &i8080::IMP },
        { "INR",     5,        &i8080::INRR,     &i8080::IMP },
        { "DCR",     5,        &i8080::DCRR,     &i8080::IMP },
        { "MVI",     5,        &i8080::MVIR,     &i8080::IMM },
        { "RLC",     4,        &i8080::RLC,      &i8080::IMP },
        { "XXX",     1,        &i8080::XXX,      &i8080::IMP },
        { "DAD",     10,       &i8080::DAD,      &i8080::IMP },
        { "LDAX",    7,        &i8080::LDAX,     &i8080::IND },
        { "DCX",     5,        &i8080::DCX,      &i8080::IMP },
        { "INR",     5,        &i8080::INRR,     &i8080::IMP },
        { "DCR",     5,        &i8080::DCRR,     &i8080::IMP },
        { "MVI",     7,        &i8080::MVIR,     &i8080::IMM },
        { "RRC",     4,        &i8080::RRC,      &i8080::IMP },
        
        // 0x1 - 0xF
        
        { "XXX",     4,        &i8080::XXX,      &i8080::IMP },
        { "LXI",     10,       &i8080::LXI,      &i8080::IMM },
        { "STAX",    7,        &i8080::STAX,     &i8080::IMP },
        { "INX",     5,        &i8080::INX,      &i8080::IMP },
        { "INR",     5,        &i8080::INRR,     &i8080::IMP },
        { "DCR",     5,        &i8080::DCRR,     &i8080::IMP },
        { "MVI",     5,        &i8080::MVIR,     &i8080::IMM },
        { "RAL",     4,        &i8080::RAL,      &i8080::IMP },
        { "XXX",     1,        &i8080::XXX,      &i8080::IMP },
        { "DAD",     10,       &i8080::DAD,      &i8080::IMP },
        { "LDAX",    7,        &i8080::LDAX,     &i8080::IND },
        { "DCX",     5,        &i8080::DCX,      &i8080::IMP },
        { "INR",     5,        &i8080::INRR,     &i8080::IMP },
        { "DCR",     5,        &i8080::DCRR,     &i8080::IMP },
        { "MVI",     7,        &i8080::MVIR,     &i8080::IMM },
        { "RAR",     4,        &i8080::RAR,      &i8080::IMP },
        
        // 0x2 - 0xF
        
        { "XXX",     4,        &i8080::XXX,      &i8080::IMP },
        { "LXI",     10,       &i8080::LXI,      &i8080::IMM },
        { "SHLD",    16,       &i8080::SHLD,     &i8080::DIR },
        { "INX",     5,        &i8080::INX,      &i8080::IMP },
        { "INR",     5,        &i8080::INRR,     &i8080::IMP },
        { "DCR",     5,        &i8080::DCRR,     &i8080::IMP },
        { "MVI",     5,        &i8080::MVIR,     &i8080::IMM },
        { "DAA",     4,        &i8080::DAA,      &i8080::IMP },
        { "XXX",     4,        &i8080::XXX,      &i8080::IMP },
        { "DAD",     10,       &i8080::DAD,      &i8080::IMP },
        { "LHLD",    16,       &i8080::LHLD,     &i8080::DIR },
        { "DCX",     5,        &i8080::DCX,      &i8080::IMP },
        { "INR",     5,        &i8080::INRR,     &i8080::IMP },
        { "DCR",     5,        &i8080::DCRR,     &i8080::IMP },
        { "MVI",     7,        &i8080::MVIR,     &i8080::IMM },
        { "CMA",     4,        &i8080::CMA,      &i8080::IMP },
        
        // 0x3 - 0xF
        
        { "XXX",     4,        &i8080::XXX,      &i8080::IMP },
        { "LXI",     10,       &i8080::LXI,      &i8080::IMM },
        { "STA",     13,       &i8080::STA,      &i8080::DIR },
        { "INX",     5,        &i8080::INX,      &i8080::IMP },
        { "INR",     10,       &i8080::INRM,     &i8080::HLM },
        { "DCR",     10,       &i8080::DCRM,     &i8080::HLM },
        { "MVI",     10,       &i8080::MVIM,     &i8080::IMM },
        { "STC",     4,        &i8080::STC,      &i8080::IMP },
        { "XXX",     1,        &i8080::XXX,      &i8080::IMP },
        { "DAD",     10,       &i8080::DAD,      &i8080::IMP },
        { "LDA",     16,       &i8080::LDA,      &i8080::DIR },
        { "DCX",     13,       &i8080::DCX,      &i8080::IMP },
        { "INR",     5,        &i8080::INRR,     &i8080::IMP },
        { "DCR",     5,        &i8080::DCRR,     &i8080::IMP },
        { "MVI",     7,        &i8080::MVIR,     &i8080::IMM },
        { "CMC",     4,        &i8080::CMC,      &i8080::IMP },
        
        // 0x4 - 0xF
        
        { "MOV",     5,        &i8080::MOVRR,    &i8080::IMP },
        { "MOV",     5,        &i8080::MOVRR,    &i8080::IMP },
        { "MOV",     5,        &i8080::MOVRR,    &i8080::IMP },
        { "MOV",     5,        &i8080::MOVRR,    &i8080::IMP },
        { "MOV",     5,        &i8080::MOVRR,    &i8080::IMP },
        { "MOV",     5,        &i8080::MOVRR,    &i8080::IMP },
        { "MOV",     7,        &i8080::MOVRM,    &i8080::HLM },
        { "MOV",     5,        &i8080::MOVRR,    &i8080::IMP },
        { "MOV",     5,        &i8080::MOVRR,    &i8080::IMP },
        { "MOV",     5,        &i8080::MOVRR,    &i8080::IMP },
        { "MOV",     5,        &i8080::MOVRR,    &i8080::IMP },
        { "MOV",     5,        &i8080::MOVRR,    &i8080::IMP },
        { "MOV",     5,        &i8080::MOVRR,    &i8080::IMP },
        { "MOV",     5,        &i8080::MOVRR,    &i8080::IMP },
        { "MOV",     7,        &i8080::MOVRM,    &i8080::HLM },
        { "MOV",     5,        &i8080::MOVRR,    &i8080::IMP },
        
        // 0x5 - 0xF
        
        { "MOV",     5,        &i8080::MOVRR,    &i8080::IMP },
        { "MOV",     5,        &i8080::MOVRR,    &i8080::IMP },
        { "MOV",     5,        &i8080::MOVRR,    &i8080::IMP },
        { "MOV",     5,        &i8080::MOVRR,    &i8080::IMP },
        { "MOV",     5,        &i8080::MOVRR,    &i8080::IMP },
        { "MOV",     5,        &i8080::MOVRR,    &i8080::IMP },
        { "MOV",     7,        &i8080::MOVRM,    &i8080::HLM },
        { "MOV",     5,        &i8080::MOVRR,    &i8080::IMP },
        { "MOV",     5,        &i8080::MOVRR,    &i8080::IMP },
        { "MOV",     5,        &i8080::MOVRR,    &i8080::IMP },
        { "MOV",     5,        &i8080::MOVRR,    &i8080::IMP },
        { "MOV",     5,        &i8080::MOVRR,    &i8080::IMP },
        { "MOV",     5,        &i8080::MOVRR,    &i8080::IMP },
        { "MOV",     5,        &i8080::MOVRR,    &i8080::IMP },
        { "MOV",     7,        &i8080::MOVRM,    &i8080::HLM },
        { "MOV",     5,        &i8080::MOVRR,    &i8080::IMP },
        
        // 0x6 - 0xF
        
        { "MOV",     5,        &i8080::MOVRR,    &i8080::IMP },
        { "MOV",     5,        &i8080::MOVRR,    &i8080::IMP },
        { "MOV",     5,        &i8080::MOVRR,    &i8080::IMP },
        { "MOV",     5,        &i8080::MOVRR,    &i8080::IMP },
        { "MOV",     5,        &i8080::MOVRR,    &i8080::IMP },
        { "MOV",     5,        &i8080::MOVRR,    &i8080::IMP },
        { "MOV",     7,        &i8080::MOVRM,    &i8080::HLM },
        { "MOV",     5,        &i8080::MOVRR,    &i8080::IMP },
        { "MOV",     5,        &i8080::MOVRR,    &i8080::IMP },
        { "MOV",     5,        &i8080::MOVRR,    &i8080::IMP },
        { "MOV",     5,        &i8080::MOVRR,    &i8080::IMP },
        { "MOV",     5,        &i8080::MOVRR,    &i8080::IMP },
        { "MOV",     5,        &i8080::MOVRR,    &i8080::IMP },
        { "MOV",     5,        &i8080::MOVRR,    &i8080::IMP },
        { "MOV",     7,        &i8080::MOVRM,    &i8080::HLM },
        { "MOV",     5,        &i8080::MOVRR,    &i8080::IMP },
        
        // 0x7 - 0xF
        
        { "MOV",     7,        &i8080::MOVMR,    &i8080::HLM },
        { "MOV",     7,        &i8080::MOVMR,    &i8080::HLM },
        { "MOV",     7,        &i8080::MOVMR,    &i8080::HLM },
        { "MOV",     7,        &i8080::MOVMR,    &i8080::HLM },
        { "MOV",     7,        &i8080::MOVMR,    &i8080::HLM },
        { "MOV",     7,        &i8080::MOVMR,    &i8080::HLM },
        { "MOV",     7,        &i8080::HLT,      &i8080::IMP },
        { "MOV",     7,        &i8080::MOVMR,    &i8080::HLM },
        { "MOV",     5,        &i8080::MOVRR,    &i8080::IMP },
        { "MOV",     5,        &i8080::MOVRR,    &i8080::IMP },
        { "MOV",     5,        &i8080::MOVRR,    &i8080::IMP },
        { "MOV",     5,        &i8080::MOVRR,    &i8080::IMP },
        { "MOV",     5,        &i8080::MOVRR,    &i8080::IMP },
        { "MOV",     5,        &i8080::MOVRR,    &i8080::IMP },
        { "MOV",     7,        &i8080::MOVRM,    &i8080::HLM },
        { "MOV",     5,        &i8080::MOVRR,    &i8080::IMP },
        
        // 0x8 - 0xF
        
        { "ADD",     4,        &i8080::ADDR,     &i8080::IMP },
        { "ADD",     4,        &i8080::ADDR,     &i8080::IMP },
        { "ADD",     4,        &i8080::ADDR,     &i8080::IMP },
        { "ADD",     4,        &i8080::ADDR,     &i8080::IMP },
        { "ADD",     4,        &i8080::ADDR,     &i8080::IMP },
        { "ADD",     4,        &i8080::ADDR,     &i8080::IMP },
        { "ADD",     7,        &i8080::ADDM,     &i8080::HLM },
        { "ADD",     4,        &i8080::ADDR,     &i8080::IMP },
        { "ADC",     4,        &i8080::ADCR,     &i8080::IMP },
        { "ADC",     4,        &i8080::ADCR,     &i8080::IMP },
        { "ADC",     4,        &i8080::ADCR,     &i8080::IMP },
        { "ADC",     4,        &i8080::ADCR,     &i8080::IMP },
        { "ADC",     4,        &i8080::ADCR,     &i8080::IMP },
        { "ADC",     4,        &i8080::ADCR,     &i8080::IMP },
        { "ADC",     7,        &i8080::ADCM,     &i8080::HLM },
        { "ADC",     4,        &i8080::ADCR,     &i8080::IMP },
        
        // 0x9 - 0xF
        
        { "SUB",     4,        &i8080::SUBR,     &i8080::IMP },
        { "SUB",     4,        &i8080::SUBR,     &i8080::IMP },
        { "SUB",     4,        &i8080::SUBR,     &i8080::IMP },
        { "SUB",     4,        &i8080::SUBR,     &i8080::IMP },
        { "SUB",     4,        &i8080::SUBR,     &i8080::IMP },
        { "SUB",     4,        &i8080::SUBR,     &i8080::IMP },
        { "SUB",     7,        &i8080::SUBM,     &i8080::HLM },
        { "SUB",     4,        &i8080::SUBR,     &i8080::IMP },
        { "SBB",     4,        &i8080::SBBR,     &i8080::IMP },
        { "SBB",     4,        &i8080::SBBR,     &i8080::IMP },
        { "SBB",     4,        &i8080::SBBR,     &i8080::IMP },
        { "SBB",     4,        &i8080::SBBR,     &i8080::IMP },
        { "SBB",     4,        &i8080::SBBR,     &i8080::IMP },
        { "SBB",     4,        &i8080::SBBR,     &i8080::IMP },
        { "SBB",     7,        &i8080::SBBM,     &i8080::HLM },
        { "SBB",     4,        &i8080::SBBR,     &i8080::IMP },
        
        // 0xA - 0xF
        
        { "ANA",     4,        &i8080::ANAR,     &i8080::IMP },
        { "ANA",     4,        &i8080::ANAR,     &i8080::IMP },
        { "ANA",     4,        &i8080::ANAR,     &i8080::IMP },
        { "ANA",     4,        &i8080::ANAR,     &i8080::IMP },
        { "ANA",     4,        &i8080::ANAR,     &i8080::IMP },
        { "ANA",     4,        &i8080::ANAR,     &i8080::IMP },
        { "ANA",     7,        &i8080::ANAM,     &i8080::HLM },
        { "ANA",     4,        &i8080::ANAR,     &i8080::IMP },
        { "XRA",     4,        &i8080::XRAR,     &i8080::IMP },
        { "XRA",     4,        &i8080::XRAR,     &i8080::IMP },
        { "XRA",     4,        &i8080::XRAR,     &i8080::IMP },
        { "XRA",     4,        &i8080::XRAR,     &i8080::IMP },
        { "XRA",     4,        &i8080::XRAR,     &i8080::IMP },
        { "XRA",     4,        &i8080::XRAR,     &i8080::IMP },
        { "XRA",     7,        &i8080::XRAM,     &i8080::HLM },
        { "XRA",     4,        &i8080::XRAR,     &i8080::IMP },
        
        // 0xB - 0xF
        
        { "ORA",     4,        &i8080::ORAR,     &i8080::IMP },
        { "ORA",     4,        &i8080::ORAR,     &i8080::IMP },
        { "ORA",     4,        &i8080::ORAR,     &i8080::IMP },
        { "ORA",     4,        &i8080::ORAR,     &i8080::IMP },
        { "ORA",     4,        &i8080::ORAR,     &i8080::IMP },
        { "ORA",     4,        &i8080::ORAR,     &i8080::IMP },
        { "ORA",     7,        &i8080::ORAM,     &i8080::HLM },
        { "ORA",     4,        &i8080::ORAR,     &i8080::IMP },
        { "CMP",     4,        &i8080::CMPR,     &i8080::IMP },
        { "CMP",     4,        &i8080::CMPR,     &i8080::IMP },
        { "CMP",     4,        &i8080::CMPR,     &i8080::IMP },
        { "CMP",     4,        &i8080::CMPR,     &i8080::IMP },
        { "CMP",     4,        &i8080::CMPR,     &i8080::IMP },
        { "CMP",     4,        &i8080::CMPR,     &i8080::IMP },
        { "CMP",     7,        &i8080::CMPM,     &i8080::HLM },
        { "CMP",     4,        &i8080::CMPR,     &i8080::IMP },
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
    
    // Increment program counter
    pc++;
    
    // Set min program cycles
    cycles = lookup[op].cycles;
    
    // Set address mode
    (this->*lookup[op].addrmod)();
    
    // Execute operation and add extra cycles
    cycles += (this->*lookup[op].operate)();
    
    std::bitset<8> x(op);
    std::cout << lookup[op].name << " " << x << std::endl;
}

void i8080::execute(int clock)
{
    for (int i=0; i < clock; i++)
    {
        this -> clock();
    }
}

#pragma mark -
#pragma mark Pairs

// Read source register
uint8_t * i8080::readsrc()
{
    return & reg[op & 0x07];
}

// Read destination register
uint8_t * i8080::readdst()
{
    return & reg[(op & 0x38) >> 3];
}

// Read registry pair as uint16_t
uint16_t i8080::readpair(const uint8_t & index)
{
    auto pair = pairs[index];
    
    uint16_t hi = *(pair + 0);
    uint16_t lo = *(pair + 1);

    return (hi << 8) | lo;
}

// Write uint16_t to registry pair
void i8080::writepair(const uint8_t & index, const uint16_t & data)
{
    *(pairs[index] + 0) = (data >> 8) & 0xFF;
    *(pairs[index] + 1) = data & 0xFF;
}

// Mutate registry pair
void i8080::mutatepair(const uint8_t & index, std::function<void(uint16_t &)> mutator)
{
    uint16_t pair = readpair(index);
    mutator(pair);
    writepair(index, pair);
}

#pragma mark -
#pragma mark Bus communication

uint8_t i8080::read()
{
    return read(address);
}

uint8_t i8080::read(uint16_t address)
{
    return bus -> read(address);
}

void i8080::write(uint8_t data)
{
    write(address, data);
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
#pragma mark Addressing modes

// No set address pointer
void i8080::IMP()
{
    // ~
}

// Set address pointer to accumulator
void i8080::IND()
{
    address = reg[A];
}

// Set address pointer to A16
void i8080::DIR()
{
    uint16_t lo = read(pc);
    pc++;
    uint16_t hi = read(pc);
    pc++;
    
    address = (hi << 8) | lo;
}

// Set address pointer to D8
void i8080::IMM()
{
    address = pc++;
}

// Set address pointer to H & L registry pair
void i8080::HLM()
{
    uint16_t lo = reg[L];
    uint16_t hi = reg[H];
    
    address = (hi << 8) | lo;
}

#pragma mark -
#pragma mark Move, Load, Store

// Code: MOV r1, r2
// Operation: (r2) → r1
// Description: Move register to register
uint8_t i8080::MOVRR()
{
    *readdst() = *readsrc();
    return 0;
}

// Code: MOV M, r
// Operation: (r) → [(HL)]
// Description: Move register to memory
uint8_t i8080::MOVMR()
{
    auto value = *readsrc();
    write(value);
    
    return 0;
}

// Code: MOV r, M
// Operation: [(HL)] → r
// Description: Move memory to register
uint8_t i8080::MOVRM()
{
    *readdst() = read();
    return 0;
}

// Code: MVI r, D8
// Operation: D8 → r
// Description: Move immediate register
uint8_t i8080::MVIR()
{
    return MOVRM();
}

// Code: MVI M, D8
// Operation: D8 → [(HL)]
// Description: Move immediate memory
uint8_t i8080::MVIM()
{
    auto value = read();
    
    uint16_t lo = reg[L];
    uint16_t hi = reg[H];

    write((hi << 8) | lo, value);
    
    return 0;
}

// Code: LXI RP
// Operation: D16 → RP
// Description: Load immediate register pair B & C
uint8_t i8080::LXI()
{
    auto index = (op & 0x30) >> 4;
    auto pair  = pairs[index];
    
    *(pair + 0) = read(address + 1); // HI
    *(pair + 1) = read(address + 0); // LO
    
    pc++;
    
    return 0;
}

// Code: STAX B
// Operation: (A) → [(RP)]
// Description: Store A indent
uint8_t i8080::STAX()
{
    auto pair = (op & (1 << 5)) >> 5;
    auto data = readpair(pair);

    write(data, reg[A]);
    
    return 0;
}

// Code: LDAX D
// Operation: [(RP)] → A
// Description: Load A indirect
uint8_t i8080::LDAX()
{
    auto pair = (op & (1 << 5)) >> 5;
    auto data = readpair(pair);
    
    reg[A] = read(data);
    
    return 0;
}

// Code: STA A16
// Operation: (A) → [(A16)]
// Description: Store A direct
uint8_t i8080::STA()
{
    write(reg[A]);
    return 0;
}

// Code: LDA A16
// Operation: [(A16)] → A
// Description: Load A direct
uint8_t i8080::LDA()
{
    reg[A] = read();
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
    auto exchange = [](uint8_t & x, uint8_t & y)
    {
        x ^= y;
        y ^= x;
        x ^= y;
    };
    
    exchange(reg[D], reg[H]);
    exchange(reg[E], reg[L]);
    
    return 0;
}

#pragma mark -
#pragma mark Stack operations

uint8_t i8080::PUSHB () { return 0; }
uint8_t i8080::PUSHD () { return 0; }
uint8_t i8080::PUSHH () { return 0; }
uint8_t i8080::PUSH  () { return 0; }  // PSW
uint8_t i8080::POPB  () { return 0; }
uint8_t i8080::POPD  () { return 0; }
uint8_t i8080::POPH  () { return 0; }
uint8_t i8080::POP   () { return 0; }  // PSW
uint8_t i8080::XTHL  () { return 0; }
uint8_t i8080::SPHL  () { return 0; }

#pragma mark -
#pragma mark Jump

uint8_t i8080::JMP  () { return 0; }
uint8_t i8080::JC   () { return 0; }
uint8_t i8080::JNC  () { return 0; }
uint8_t i8080::JZ   () { return 0; }
uint8_t i8080::JNZ  () { return 0; }
uint8_t i8080::JP   () { return 0; }
uint8_t i8080::JM   () { return 0; }
uint8_t i8080::JPE  () { return 0; }
uint8_t i8080::JPO  () { return 0; }
uint8_t i8080::PCHL () { return 0; }

#pragma mark -
#pragma mark Call

uint8_t i8080::CALL () { return 0; }
uint8_t i8080::CC   () { return 0; }
uint8_t i8080::CNC  () { return 0; }
uint8_t i8080::CZ   () { return 0; }
uint8_t i8080::CNZ  () { return 0; }
uint8_t i8080::CP   () { return 0; }
uint8_t i8080::CM   () { return 0; }
uint8_t i8080::CPE  () { return 0; }
uint8_t i8080::CPO  () { return 0; }

#pragma mark -
#pragma mark Return

// Return if positive
uint8_t i8080::RET (uint8_t flag)
{
    if (flag == 0)
    {
        return 0;
    }
    
    RET();
    return 6;
}

// Return if negative
uint8_t i8080::RETN (uint8_t flag)
{
    return RET(!flag);
}

// Code: RET
// Operation: [(SP)] → PCL, [(SP)+1] → PCH
// Description: Return
// Flags: -
uint8_t i8080::RET  ()
{
    uint16_t lo = read(sp);
    sp++;
    uint16_t hi = read(sp);
    sp++;

    pc = (hi << 8) | lo;
    
    return 0;
}

// Code: RC
// Operation: [(SP)] → PCL, [(SP)+1] → PCH
// Description: Return if carry set
// Flags: -
uint8_t i8080::RC   ()
{
    auto flag = sr.GetCarry();
    return RET(flag);
}

// Code: RC
// Operation: [(SP)] → PCL, [(SP)+1] → PCH
// Description: Return if carry reset
// Flags: -
uint8_t i8080::RNC  ()
{
    auto flag = sr.GetCarry();
    return RETN(flag);
}

// Code: RZ
// Operation: [(SP)] → PCL, [(SP)+1] → PCH
// Description: Return if zero set
// Flags: -
uint8_t i8080::RZ   ()
{
    auto flag = sr.GetZero();
    return RET(flag);
}

// Code: RNZ
// Operation: [(SP)] → PCL, [(SP)+1] → PCH
// Description: Return if zero reset
// Flags: -
uint8_t i8080::RNZ  ()
{
    auto flag = sr.GetZero();
    return RETN(flag);
}

// Code: RM
// Operation: [(SP)] → PCL, [(SP)+1] → PCH
// Description: Return if minus
// Flags: -
uint8_t i8080::RM   ()
{
    auto flag = sr.GetSign();
    return RET(flag);
}

// Code: RP
// Operation: [(SP)] → PCL, [(SP)+1] → PCH
// Description: Return if plus
// Flags: -
uint8_t i8080::RP   ()
{
    auto flag = sr.GetSign();
    return RETN(flag);
}

// Code: RPE
// Operation: [(SP)] → PCL, [(SP)+1] → PCH
// Description: Return if parity even
// Flags: -
uint8_t i8080::RPE  ()
{
    auto flag = sr.GetParity();
    return RET(flag);
}

// Code: RPO
// Operation: [(SP)] → PCL, [(SP)+1] → PCH
// Description: Return if parity odd
// Flags: -
uint8_t i8080::RPO  ()
{
    auto flag = sr.GetParity();
    return RETN(flag);
}

#pragma mark -
#pragma mark Restart

uint8_t RST  ()
{
    return 0;
}

#pragma mark -
#pragma mark Increment and decrement

// Code: INR R
// Operation: (r) + 1 → r
// Description: Increment register
// Flags: S,Z,AC,P
uint8_t i8080::INRR ()
{
    uint16_t value = *readdst();
    *readdst() = ++value & 0x00FF;
    
    sr.SetAuxFlags(value);

    return 0;
}

// Code: INR M
// Operation: [(HL)] + 1 → [(HL)]
// Description: Increment memory
// Flags: S,Z,AC,P
uint8_t i8080::INRM ()
{
    uint16_t value = read();
    write(++value & 0x00FF);

    sr.SetAuxFlags(value);
    
    return 0;
}

// Code: DCR r
// Operation: (r) – 1 → r
// Description: Decrement register
// Flags: S,Z,AC,P
uint8_t i8080::DCRR ()
{
    uint16_t value = *readdst();
    *readdst() = --value & 0x00FF;
    
    sr.SetAuxFlags(value);
    
    return 0;
}

// Code: DCR M
// Operation: [(HL)] - 1 → [(HL)]
// Description: Decrement memory
// Flags: S,Z,AC,P
uint8_t i8080::DCRM ()
{
    uint16_t value = read();
    write(--value & 0x00FF);

    sr.SetAuxFlags(value);
    
    return 0;
}

// Code: INX RP
// Operation: (RP) + 1 → r
// Description: Increment registry pair
// Flags: -
uint8_t i8080::INX  ()
{
    mutatepair((op & 0x30) >> 4, [](uint16_t & pair) { pair++; });
    return 0;
}

// Code: DCX RP
// Operation: (RP) - 1 → r
// Description: Decrement registry pair
// Flags: -
uint8_t i8080::DCX  ()
{
    mutatepair((op & 0x30) >> 4, [](uint16_t & pair) { pair--; });
    return 0;
}

#pragma mark -
#pragma mark Add

uint8_t i8080::ADD(uint8_t data, uint8_t carry)
{
    uint16_t acc = reg[A];
    uint16_t tmp = acc + ((uint16_t) data + (uint16_t) carry);
    reg[A] = tmp & 0x00FF;
    
    sr.SetAllFlags(tmp);
    
    return 0;
}

uint8_t i8080::ADC(uint8_t data)
{
    auto carry = sr.GetCarry();
    return ADD (carry, data);
}

// Code: ADD r
// Operation: (A) + (r) → A
// Description: Add register to A
// Flags: S,Z,AC,P,C
uint8_t i8080::ADDR ()
{
    auto value = *readsrc();
    return ADD(value);
}

// Code: ADD M
// Operation: (A) + М → A
// Description: Add memory to A
// Flags: S,Z,AC,P,C
uint8_t i8080::ADDM ()
{
    auto value = read();
    return ADD(value);
}

// Code: ADC r
// Operation: (A) + (r) + C → A
// Description: Add register to A with carry
// Flags: S,Z,AC,P,C
uint8_t i8080::ADCR ()
{
    auto value = *readsrc();
    return ADC(value);
}

// Code: ADC M
// Operation: (A) + М + С → A
// Description: Add memory to A with carry
// Flags: S,Z,AC,P,C
uint8_t i8080::ADCM ()
{
    auto value = read();
    return ADC(value);
}

// Code: ADI D8
// Operation: (A) + D8 → A
// Description: Add immediate to A
// Flags: S,Z,AC,P,C
uint8_t i8080::ADI ()
{
    return ADDM(); // Address = D8
}

// Code: ACI D8
// Operation: (A) + D8 + C → A
// Description: Add immediate to A with carry
// Flags: S,Z,AC,P,C
uint8_t i8080::ACI  ()
{
    return ADCM(); // Address = D8
}

// Code: DAD rp
// Operation: (HL) + (RP) → HL
// Description: Add part to H & L
// Flags: C
uint8_t i8080::DAD  ()
{
    uint16_t rpdata = readpair((op & 0x30) >> 4);
    uint16_t hldata = readpair(HL);
    
    uint16_t tmp = rpdata + hldata;
    
    writepair(HL, tmp);
    sr.SetCarry(tmp);
    
    return 0;
}

#pragma mark -
#pragma mark Substract

uint8_t i8080::SUB(uint8_t data, uint8_t carry)
{
    uint16_t acc = reg[A];
    uint16_t tmp = acc - ((uint16_t) data - (uint16_t) carry);
    reg[A] = tmp & 0x00FF;
    
    sr.SetAllFlags(tmp);
    
    return 0;
}

uint8_t i8080::SBB(uint8_t data)
{
    auto carry = sr.GetCarry();
    return SUB (carry, data);
}

// Code: SUB r
// Operation: (A) - (r) → A
// Description: Substract register from A
// Flags: S,Z,AC,P,C
uint8_t i8080::SUBR ()
{
    auto value = *readsrc();
    return SUB(value);
}

// Code: SUB M
// Operation: (A) – М → A
// Description: Substract memory from A
// Flags: S,Z,AC,P,C
uint8_t i8080::SUBM ()
{
    auto value = read();
    return SUB(value);
}

// Code: SBB r
// Operation: (A) - (r) - C → A
// Description: Substract register from A with borrow
// Flags: S,Z,AC,P,C
uint8_t i8080::SBBR ()
{
    auto value = *readsrc();
    return SBB(value);
}

// Code: SBB M
// Operation: (A) – М - C → A
// Description: Substract memory from A with borrow
// Flags: S,Z,AC,P,C
uint8_t i8080::SBBM ()
{
    auto value = read();
    return SBB(value);
}

// Code: SUI D8
// Operation: (A) - D8 → A
// Description: Substract immediate from A
// Flags: S,Z,AC,P,C
uint8_t i8080::SUI  ()
{
    return SUBM(); // Address = D8
}

// Code: DBI D8
// Operation: (A) - D8 - C → A
// Description: Substract immediate from A with borrow
// Flags: S,Z,AC,P,C
uint8_t i8080::SBI  ()
{
    return SBBM (); // Address = D8
}

#pragma mark -
#pragma mark Logical

uint8_t i8080::ANA  (uint8_t data)
{
    reg[A] &= data;
    
    sr.SetDecFlags (reg[A]);
    sr.SetCarry    (0x00);
    
    return 0;
}

uint8_t i8080::XRA  (uint8_t data)
{
    reg[A] ^= data;
    
    sr.SetDecFlags (reg[A]);
    sr.SetAux      (0x00);
    sr.SetCarry    (0x00);
    
    return 0;
}

uint8_t i8080::ORA  (uint8_t data)
{
    reg[A] |= data;
    
    sr.SetDecFlags (reg[A]);
    sr.SetCarry    (0x00);
    
    return 0;
}

uint8_t i8080::CMP  (uint8_t value)
{
    uint16_t acc = reg[A];
    uint16_t tmp = acc - (uint16_t) value;
    
    sr.SetCarry  (acc < value);
    sr.SetZero   (acc == value);
    
    sr.SetAux    (tmp);
    sr.SetParity (tmp);
    sr.SetSign   (tmp);
    
    return 0;
}

// Code: ANA r
// Operation: (A) & (r) → A
// Description: And register with A
// Flags: S,Z,AC=*,P,C=0
uint8_t i8080::ANAR ()
{
    auto value = *readsrc();
    return ANA(value);
}

// Code: ANA M
// Operation: (A) & M → A
// Description: And memory with A
// Flags: S,Z,AC=*,P,C=0
uint8_t i8080::ANAM ()
{
    auto value = read();
    return ANA(value);
}

// Code: XRA r
// Operation: (A) ^ r → A
// Description: Exclusive or register with A
// Flags: S,Z,AC=0,P,C=0
uint8_t i8080::XRAR ()
{
    auto value = *readsrc();
    return XRA(value);
}

// Code: XRA M
// Operation: (A) ^ M → A
// Description: Exclusive or memory with A
// Flags: S,Z,AC=0,P,C=0
uint8_t i8080::XRAM ()
{
    auto value = read();
    return XRA(value);
}

// Code: ORA r
// Operation: (A) | r → A
// Description: Or register with A
// Flags: S,Z,AC,P,C=0
uint8_t i8080::ORAR ()
{
    auto value = *readsrc();
    return ORA(value);
}

// Code: ORA M
// Operation: (A) | М → A
// Description: Or memory with A
// Flags: S,Z,AC,P,C=0
uint8_t i8080::ORAM ()
{
    auto value = *readsrc();
    return ORA(value);
}

// Code: CMP r
// Operation: Compare
// Description: Comapre register with A
// Flags: S,Z,AC,P,C
uint8_t i8080::CMPR ()
{
    auto value = *readsrc();
    return CMP(value);
}

// Code: CMP M
// Operation: Compare
// Description: Comapre memory with A
// Flags: S,Z,AC,P,C
uint8_t i8080::CMPM ()
{
    auto value = read();
    return CMP(value);
}

uint8_t i8080::ANI  () { return 0; }
uint8_t i8080::XRI  () { return 0; }
uint8_t i8080::ORI  () { return 0; }
uint8_t i8080::CPI  () { return 0; }

#pragma mark -
#pragma mark Rotate

uint8_t i8080::RLC  () { return 0; }
uint8_t i8080::RRC  () { return 0; }
uint8_t i8080::RAL  () { return 0; }
uint8_t i8080::RAR  () { return 0; }

#pragma mark -
#pragma mark Special

uint8_t i8080::CMA  () { return 0; }
uint8_t i8080::STC  () { return 0; }
uint8_t i8080::CMC  () { return 0; }
uint8_t i8080::DAA  () { return 0; }

#pragma mark -
#pragma mark I/O

uint8_t i8080::IN   () { return 0; }
uint8_t i8080::OUT  () { return 0; }

#pragma mark -
#pragma mark Control

uint8_t i8080::EI   () { return 0; }
uint8_t i8080::DI   () { return 0; }
uint8_t i8080::HLT  () { return 0; }

// Code: NOP
// Operation: No-operation
uint8_t i8080::NOP()
{
    return 0;
}

uint8_t i8080::XXX()
{
    return 0;
}
