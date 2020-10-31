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
        { "INX",     5,        &i8080::INXB,     &i8080::IMP },
        { "INR",     5,        &i8080::INRR,     &i8080::IMP },
        { "DCR",     5,        &i8080::DCRR,     &i8080::IMP },
        { "MVI",     5,        &i8080::MVIR,     &i8080::IMM },
        { "RLC",     4,        &i8080::RLC,      &i8080::IMP },
        { "XXX",     1,        &i8080::XXX,      &i8080::IMP },
        { "DAD",     10,       &i8080::DADB,     &i8080::IMP },
        { "LDAX",    7,        &i8080::LDAXB,    &i8080::IND },
        { "DCX",     5,        &i8080::DCXB,     &i8080::IMP },
        { "INR",     5,        &i8080::INRR,     &i8080::IMP },
        { "DCR",     5,        &i8080::DCRR,     &i8080::IMP },
        { "MVI",     7,        &i8080::MVIR,     &i8080::IMM },
        { "RRC",     4,        &i8080::RRC,      &i8080::IMP },
        
        // 0x1 - 0xF
        
        { "XXX",     4,        &i8080::XXX,      &i8080::IMP },
        { "LXI",     10,       &i8080::LXID,     &i8080::IMM },
        { "STAX",    7,        &i8080::STAXD,    &i8080::IMP },
        { "INX",     5,        &i8080::INXD,     &i8080::IMP },
        { "INR",     5,        &i8080::INRR,     &i8080::IMP },
        { "DCR",     5,        &i8080::DCRR,     &i8080::IMP },
        { "MVI",     5,        &i8080::MVIR,     &i8080::IMM },
        { "RAL",     4,        &i8080::RAL,      &i8080::IMP },
        { "XXX",     1,        &i8080::XXX,      &i8080::IMP },
        { "DAD",     10,       &i8080::DADD,     &i8080::IMP },
        { "LDAX",    7,        &i8080::LDAXD,    &i8080::IND },
        { "DCX",     5,        &i8080::DCXD,     &i8080::IMP },
        { "INR",     5,        &i8080::INRR,     &i8080::IMP },
        { "DCR",     5,        &i8080::DCRR,     &i8080::IMP },
        { "MVI",     7,        &i8080::MVIR,     &i8080::IMM },
        { "RAR",     4,        &i8080::RAR,      &i8080::IMP },
        
        // 0x2 - 0xF
        
        { "XXX",     4,        &i8080::XXX,      &i8080::IMP },
        { "LXI",     10,       &i8080::LXIH,     &i8080::IMM },
        { "SHLD",    16,       &i8080::SHLD,     &i8080::DIR },
        { "INX",     5,        &i8080::INXH,     &i8080::IMP },
        { "INR",     5,        &i8080::INRR,     &i8080::IMP },
        { "DCR",     5,        &i8080::DCRR,     &i8080::IMP },
        { "MVI",     5,        &i8080::MVIR,     &i8080::IMM },
        { "DAA",     4,        &i8080::DAA,      &i8080::IMP },
        { "DAD",     10,       &i8080::DADH,     &i8080::IMP },
        { "LHLD",    16,       &i8080::LHLD,     &i8080::DIR },
        { "DCX",     5,        &i8080::DCXH,     &i8080::IMP },
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
        
        { "MOV",     5,        &i8080::MOVRR,     &i8080::IMP },
        { "MOV",     5,        &i8080::MOVRR,     &i8080::IMP },
        { "MOV",     5,        &i8080::MOVRR,     &i8080::IMP },
        { "MOV",     5,        &i8080::MOVRR,     &i8080::IMP },
        { "MOV",     5,        &i8080::MOVRR,     &i8080::IMP },
        { "MOV",     5,        &i8080::MOVRR,     &i8080::IMP },
        { "MOV",     7,        &i8080::MOVRM,     &i8080::HLM },
        { "MOV",     5,        &i8080::MOVRR,     &i8080::IMP },
        { "MOV",     5,        &i8080::MOVRR,     &i8080::IMP },
        { "MOV",     5,        &i8080::MOVRR,     &i8080::IMP },
        { "MOV",     5,        &i8080::MOVRR,     &i8080::IMP },
        { "MOV",     5,        &i8080::MOVRR,     &i8080::IMP },
        { "MOV",     5,        &i8080::MOVRR,     &i8080::IMP },
        { "MOV",     5,        &i8080::MOVRR,     &i8080::IMP },
        { "MOV",     7,        &i8080::MOVRM,     &i8080::HLM },
        { "MOV",     5,        &i8080::MOVRR,     &i8080::IMP },
        
        // 0x5 - 0xF
        
        { "MOV",     5,        &i8080::MOVRR,     &i8080::IMP },
        { "MOV",     5,        &i8080::MOVRR,     &i8080::IMP },
        { "MOV",     5,        &i8080::MOVRR,     &i8080::IMP },
        { "MOV",     5,        &i8080::MOVRR,     &i8080::IMP },
        { "MOV",     5,        &i8080::MOVRR,     &i8080::IMP },
        { "MOV",     5,        &i8080::MOVRR,     &i8080::IMP },
        { "MOV",     7,        &i8080::MOVRM,     &i8080::HLM },
        { "MOV",     5,        &i8080::MOVRR,     &i8080::IMP },
        { "MOV",     5,        &i8080::MOVRR,     &i8080::IMP },
        { "MOV",     5,        &i8080::MOVRR,     &i8080::IMP },
        { "MOV",     5,        &i8080::MOVRR,     &i8080::IMP },
        { "MOV",     5,        &i8080::MOVRR,     &i8080::IMP },
        { "MOV",     5,        &i8080::MOVRR,     &i8080::IMP },
        { "MOV",     5,        &i8080::MOVRR,     &i8080::IMP },
        { "MOV",     7,        &i8080::MOVRM,     &i8080::HLM },
        { "MOV",     5,        &i8080::MOVRR,     &i8080::IMP },
        
        // 0x6 - 0xF
        
        { "MOV",     5,        &i8080::MOVRR,      &i8080::IMP },
        { "MOV",     5,        &i8080::MOVRR,      &i8080::IMP },
        { "MOV",     5,        &i8080::MOVRR,      &i8080::IMP },
        { "MOV",     5,        &i8080::MOVRR,      &i8080::IMP },
        { "MOV",     5,        &i8080::MOVRR,      &i8080::IMP },
        { "MOV",     5,        &i8080::MOVRR,      &i8080::IMP },
        { "MOV",     7,        &i8080::MOVRM,      &i8080::HLM },
        { "MOV",     5,        &i8080::MOVRR,      &i8080::IMP },
        { "MOV",     5,        &i8080::MOVRR,      &i8080::IMP },
        { "MOV",     5,        &i8080::MOVRR,      &i8080::IMP },
        { "MOV",     5,        &i8080::MOVRR,      &i8080::IMP },
        { "MOV",     5,        &i8080::MOVRR,      &i8080::IMP },
        { "MOV",     5,        &i8080::MOVRR,      &i8080::IMP },
        { "MOV",     5,        &i8080::MOVRR,      &i8080::IMP },
        { "MOV",     7,        &i8080::MOVRM,      &i8080::HLM },
        { "MOV",     5,        &i8080::MOVRR,      &i8080::IMP },
        
        // 0x7 - 0xF
        
        { "MOV",     7,        &i8080::MOVMR,      &i8080::HLM },
        { "MOV",     7,        &i8080::MOVMR,      &i8080::HLM },
        { "MOV",     7,        &i8080::MOVMR,      &i8080::HLM },
        { "MOV",     7,        &i8080::MOVMR,      &i8080::HLM },
        { "MOV",     7,        &i8080::MOVMR,      &i8080::HLM },
        { "MOV",     7,        &i8080::MOVMR,      &i8080::HLM },
        { "MOV",     7,        &i8080::HLT,        &i8080::IMP },
        { "MOV",     7,        &i8080::MOVMR,      &i8080::HLM },
        { "MOV",     5,        &i8080::MOVRR,      &i8080::IMP },
        { "MOV",     5,        &i8080::MOVRR,      &i8080::IMP },
        { "MOV",     5,        &i8080::MOVRR,      &i8080::IMP },
        { "MOV",     5,        &i8080::MOVRR,      &i8080::IMP },
        { "MOV",     5,        &i8080::MOVRR,      &i8080::IMP },
        { "MOV",     5,        &i8080::MOVRR,      &i8080::IMP },
        { "MOV",     7,        &i8080::MOVRM,      &i8080::HLM },
        { "MOV",     5,        &i8080::MOVRR,      &i8080::IMP },
        
        // 0x8 - 0xF
        
        { "MOV",     5,        &i8080::MOVRR,      &i8080::IMP },
        { "MOV",     5,        &i8080::MOVRR,      &i8080::IMP },
        { "MOV",     5,        &i8080::MOVRR,      &i8080::IMP },
        { "MOV",     5,        &i8080::MOVRR,      &i8080::IMP },
        { "MOV",     5,        &i8080::MOVRR,      &i8080::IMP },
        { "MOV",     5,        &i8080::MOVRR,      &i8080::IMP },
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
uint8_t i8080::LXI   () { return 0; }  // SP
uint8_t i8080::INX   () { return 0; }  // SP
uint8_t i8080::DCX   () { return 0; }  // SP

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

uint8_t i8080::RET  () { return 0; }
uint8_t i8080::RC   () { return 0; }
uint8_t i8080::RNC  () { return 0; }
uint8_t i8080::RZ   () { return 0; }
uint8_t i8080::RNZ  () { return 0; }
uint8_t i8080::RP   () { return 0; }
uint8_t i8080::RM   () { return 0; }
uint8_t i8080::RPE  () { return 0; }
uint8_t i8080::RPO  () { return 0; }

#pragma mark -
#pragma mark Restart

uint8_t RST  ()
{
    return 0;
}

#pragma mark -
#pragma mark Increment and decrement

uint8_t i8080::INRR () { return 0; }
uint8_t i8080::INRM () { return 0; }
uint8_t i8080::DCRR () { return 0; }
uint8_t i8080::DCRM () { return 0; }
uint8_t i8080::INXB () { return 0; }
uint8_t i8080::INXD () { return 0; }
uint8_t i8080::INXH () { return 0; }
uint8_t i8080::DCXB () { return 0; }
uint8_t i8080::DCXD () { return 0; }
uint8_t i8080::DCXH () { return 0; }

#pragma mark -
#pragma mark Add

uint8_t i8080::ADDR () { return 0; }
uint8_t i8080::ADDM () { return 0; }
uint8_t i8080::ADCR () { return 0; }
uint8_t i8080::ADCM () { return 0; }
uint8_t i8080::ADI  () { return 0; }
uint8_t i8080::ACI  () { return 0; }
uint8_t i8080::DADB () { return 0; }
uint8_t i8080::DADD () { return 0; }
uint8_t i8080::DADH () { return 0; }
uint8_t i8080::DAD  () { return 0; }

#pragma mark -
#pragma mark Substract

uint8_t i8080::SUBR () { return 0; }
uint8_t i8080::SUBM () { return 0; }
uint8_t i8080::SBBR () { return 0; }
uint8_t i8080::SBBM () { return 0; }
uint8_t i8080::SUI  () { return 0; }
uint8_t i8080::SBI  () { return 0; }

#pragma mark -
#pragma mark Logical

uint8_t i8080::ANAR () { return 0; }
uint8_t i8080::XRAR () { return 0; }
uint8_t i8080::ORAR () { return 0; }
uint8_t i8080::CMPR () { return 0; }
uint8_t i8080::ANAM () { return 0; }
uint8_t i8080::XRAM () { return 0; }
uint8_t i8080::ORAM () { return 0; }
uint8_t i8080::CMPM () { return 0; }
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
