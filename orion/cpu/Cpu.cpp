//
//  i8080.cpp
//  orion
//
//  Created by Артём Оконечников on 29.10.2020.
//

#include "Cpu.hpp"
#include "Bus.hpp"

#include <iostream>
#include <iomanip>

#define LOGTEST

Cpu::Cpu() : registers { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }
{
    regpairs[BC] = registers + B;
    regpairs[DE] = registers + D;
    regpairs[HL] = registers + H;
    
    lookup =
    {
        // NAME      CYCLES    OPERATION         ADDRMOD
        // ---------------------------------------------------
        
        // 0x0 - 0xF
        
        { "NOP",     4,        &Cpu::NOP,      &Cpu::IMP },
        { "LXI",     10,       &Cpu::LXI,      &Cpu::DIR },
        { "STAX",    7,        &Cpu::STAX,     &Cpu::IMP },
        { "INX",     5,        &Cpu::INX,      &Cpu::IMP },
        { "INR",     5,        &Cpu::INRR,     &Cpu::IMP },
        { "DCR",     5,        &Cpu::DCRR,     &Cpu::IMP },
        { "MVI",     7,        &Cpu::MVIR,     &Cpu::IMM },
        { "RLC",     4,        &Cpu::RLC,      &Cpu::IMP },
        { "NOP",     4,        &Cpu::NOP,      &Cpu::IMP },
        { "DAD",     10,       &Cpu::DAD,      &Cpu::IMP },
        { "LDAX",    7,        &Cpu::LDAX,     &Cpu::IND },
        { "DCX",     5,        &Cpu::DCX,      &Cpu::IMP },
        { "INR",     5,        &Cpu::INRR,     &Cpu::IMP },
        { "DCR",     5,        &Cpu::DCRR,     &Cpu::IMP },
        { "MVI",     7,        &Cpu::MVIR,     &Cpu::IMM },
        { "RRC",     4,        &Cpu::RRC,      &Cpu::IMP },
        
        // 0x1 - 0xF
        
        { "NOP",     4,        &Cpu::NOP,      &Cpu::IMP },
        { "LXI",     10,       &Cpu::LXI,      &Cpu::DIR },
        { "STAX",    7,        &Cpu::STAX,     &Cpu::IMP },
        { "INX",     5,        &Cpu::INX,      &Cpu::IMP },
        { "INR",     5,        &Cpu::INRR,     &Cpu::IMP },
        { "DCR",     5,        &Cpu::DCRR,     &Cpu::IMP },
        { "MVI",     7,        &Cpu::MVIR,     &Cpu::IMM },
        { "RAL",     4,        &Cpu::RAL,      &Cpu::IMP },
        { "NOP",     4,        &Cpu::NOP,      &Cpu::IMP },
        { "DAD",     10,       &Cpu::DAD,      &Cpu::IMP },
        { "LDAX",    7,        &Cpu::LDAX,     &Cpu::IND },
        { "DCX",     5,        &Cpu::DCX,      &Cpu::IMP },
        { "INR",     5,        &Cpu::INRR,     &Cpu::IMP },
        { "DCR",     5,        &Cpu::DCRR,     &Cpu::IMP },
        { "MVI",     7,        &Cpu::MVIR,     &Cpu::IMM },
        { "RAR",     4,        &Cpu::RAR,      &Cpu::IMP },
        
        // 0x2 - 0xF
        
        { "NOP",     4,        &Cpu::NOP,      &Cpu::IMP },
        { "LXI",     10,       &Cpu::LXI,      &Cpu::DIR },
        { "SHLD",    16,       &Cpu::SHLD,     &Cpu::DIR },
        { "INX",     5,        &Cpu::INX,      &Cpu::IMP },
        { "INR",     5,        &Cpu::INRR,     &Cpu::IMP },
        { "DCR",     5,        &Cpu::DCRR,     &Cpu::IMP },
        { "MVI",     7,        &Cpu::MVIR,     &Cpu::IMM },
        { "DAA",     4,        &Cpu::DAA,      &Cpu::IMP },
        { "NOP",     4,        &Cpu::NOP,      &Cpu::IMP },
        { "DAD",     10,       &Cpu::DAD,      &Cpu::IMP },
        { "LHLD",    16,       &Cpu::LHLD,     &Cpu::DIR },
        { "DCX",     5,        &Cpu::DCX,      &Cpu::IMP },
        { "INR",     5,        &Cpu::INRR,     &Cpu::IMP },
        { "DCR",     5,        &Cpu::DCRR,     &Cpu::IMP },
        { "MVI",     7,        &Cpu::MVIR,     &Cpu::IMM },
        { "CMA",     4,        &Cpu::CMA,      &Cpu::IMP },
        
        // 0x3 - 0xF
        
        { "NOP",     4,        &Cpu::NOP,      &Cpu::IMP },
        { "LXI",     10,       &Cpu::LXISP,    &Cpu::DIR },
        { "STA",     13,       &Cpu::STA,      &Cpu::DIR },
        { "INX",     5,        &Cpu::INXSP,    &Cpu::IMP },
        { "INR",     10,       &Cpu::INRM,     &Cpu::HLM },
        { "DCR",     10,       &Cpu::DCRM,     &Cpu::HLM },
        { "MVI",     10,       &Cpu::MVIM,     &Cpu::IMM },
        { "STC",     4,        &Cpu::STC,      &Cpu::IMP },
        { "NOP",     4,        &Cpu::NOP,      &Cpu::IMP },
        { "DAD",     10,       &Cpu::DADSP,    &Cpu::IMP },
        { "LDA",     13,       &Cpu::LDA,      &Cpu::DIR },
        { "DCX",     5,        &Cpu::DCXSP,    &Cpu::IMP },
        { "INR",     5,        &Cpu::INRR,     &Cpu::IMP },
        { "DCR",     5,        &Cpu::DCRR,     &Cpu::IMP },
        { "MVI",     7,        &Cpu::MVIR,     &Cpu::IMM },
        { "CMC",     4,        &Cpu::CMC,      &Cpu::IMP },
        
        // 0x4 - 0xF
        
        { "MOV",     5,        &Cpu::MOVRR,    &Cpu::IMP },
        { "MOV",     5,        &Cpu::MOVRR,    &Cpu::IMP },
        { "MOV",     5,        &Cpu::MOVRR,    &Cpu::IMP },
        { "MOV",     5,        &Cpu::MOVRR,    &Cpu::IMP },
        { "MOV",     5,        &Cpu::MOVRR,    &Cpu::IMP },
        { "MOV",     5,        &Cpu::MOVRR,    &Cpu::IMP },
        { "MOV",     7,        &Cpu::MOVRM,    &Cpu::HLM },
        { "MOV",     5,        &Cpu::MOVRR,    &Cpu::IMP },
        { "MOV",     5,        &Cpu::MOVRR,    &Cpu::IMP },
        { "MOV",     5,        &Cpu::MOVRR,    &Cpu::IMP },
        { "MOV",     5,        &Cpu::MOVRR,    &Cpu::IMP },
        { "MOV",     5,        &Cpu::MOVRR,    &Cpu::IMP },
        { "MOV",     5,        &Cpu::MOVRR,    &Cpu::IMP },
        { "MOV",     5,        &Cpu::MOVRR,    &Cpu::IMP },
        { "MOV",     7,        &Cpu::MOVRM,    &Cpu::HLM },
        { "MOV",     5,        &Cpu::MOVRR,    &Cpu::IMP },
        
        // 0x5 - 0xF
        
        { "MOV",     5,        &Cpu::MOVRR,    &Cpu::IMP },
        { "MOV",     5,        &Cpu::MOVRR,    &Cpu::IMP },
        { "MOV",     5,        &Cpu::MOVRR,    &Cpu::IMP },
        { "MOV",     5,        &Cpu::MOVRR,    &Cpu::IMP },
        { "MOV",     5,        &Cpu::MOVRR,    &Cpu::IMP },
        { "MOV",     5,        &Cpu::MOVRR,    &Cpu::IMP },
        { "MOV",     7,        &Cpu::MOVRM,    &Cpu::HLM },
        { "MOV",     5,        &Cpu::MOVRR,    &Cpu::IMP },
        { "MOV",     5,        &Cpu::MOVRR,    &Cpu::IMP },
        { "MOV",     5,        &Cpu::MOVRR,    &Cpu::IMP },
        { "MOV",     5,        &Cpu::MOVRR,    &Cpu::IMP },
        { "MOV",     5,        &Cpu::MOVRR,    &Cpu::IMP },
        { "MOV",     5,        &Cpu::MOVRR,    &Cpu::IMP },
        { "MOV",     5,        &Cpu::MOVRR,    &Cpu::IMP },
        { "MOV",     7,        &Cpu::MOVRM,    &Cpu::HLM },
        { "MOV",     5,        &Cpu::MOVRR,    &Cpu::IMP },
        
        // 0x6 - 0xF
        
        { "MOV",     5,        &Cpu::MOVRR,    &Cpu::IMP },
        { "MOV",     5,        &Cpu::MOVRR,    &Cpu::IMP },
        { "MOV",     5,        &Cpu::MOVRR,    &Cpu::IMP },
        { "MOV",     5,        &Cpu::MOVRR,    &Cpu::IMP },
        { "MOV",     5,        &Cpu::MOVRR,    &Cpu::IMP },
        { "MOV",     5,        &Cpu::MOVRR,    &Cpu::IMP },
        { "MOV",     7,        &Cpu::MOVRM,    &Cpu::HLM },
        { "MOV",     5,        &Cpu::MOVRR,    &Cpu::IMP },
        { "MOV",     5,        &Cpu::MOVRR,    &Cpu::IMP },
        { "MOV",     5,        &Cpu::MOVRR,    &Cpu::IMP },
        { "MOV",     5,        &Cpu::MOVRR,    &Cpu::IMP },
        { "MOV",     5,        &Cpu::MOVRR,    &Cpu::IMP },
        { "MOV",     5,        &Cpu::MOVRR,    &Cpu::IMP },
        { "MOV",     5,        &Cpu::MOVRR,    &Cpu::IMP },
        { "MOV",     7,        &Cpu::MOVRM,    &Cpu::HLM },
        { "MOV",     5,        &Cpu::MOVRR,    &Cpu::IMP },
        
        // 0x7 - 0xF
        
        { "MOV",     7,        &Cpu::MOVMR,    &Cpu::HLM },
        { "MOV",     7,        &Cpu::MOVMR,    &Cpu::HLM },
        { "MOV",     7,        &Cpu::MOVMR,    &Cpu::HLM },
        { "MOV",     7,        &Cpu::MOVMR,    &Cpu::HLM },
        { "MOV",     7,        &Cpu::MOVMR,    &Cpu::HLM },
        { "MOV",     7,        &Cpu::MOVMR,    &Cpu::HLM },
        { "HLT",     4,        &Cpu::HLT,      &Cpu::IMP },
        { "MOV",     7,        &Cpu::MOVMR,    &Cpu::HLM },
        { "MOV",     5,        &Cpu::MOVRR,    &Cpu::IMP },
        { "MOV",     5,        &Cpu::MOVRR,    &Cpu::IMP },
        { "MOV",     5,        &Cpu::MOVRR,    &Cpu::IMP },
        { "MOV",     5,        &Cpu::MOVRR,    &Cpu::IMP },
        { "MOV",     5,        &Cpu::MOVRR,    &Cpu::IMP },
        { "MOV",     5,        &Cpu::MOVRR,    &Cpu::IMP },
        { "MOV",     7,        &Cpu::MOVRM,    &Cpu::HLM },
        { "MOV",     5,        &Cpu::MOVRR,    &Cpu::IMP },
        
        // 0x8 - 0xF
        
        { "ADD",     4,        &Cpu::ADDR,     &Cpu::IMP },
        { "ADD",     4,        &Cpu::ADDR,     &Cpu::IMP },
        { "ADD",     4,        &Cpu::ADDR,     &Cpu::IMP },
        { "ADD",     4,        &Cpu::ADDR,     &Cpu::IMP },
        { "ADD",     4,        &Cpu::ADDR,     &Cpu::IMP },
        { "ADD",     4,        &Cpu::ADDR,     &Cpu::IMP },
        { "ADD",     7,        &Cpu::ADDM,     &Cpu::HLM },
        { "ADD",     4,        &Cpu::ADDR,     &Cpu::IMP },
        { "ADC",     4,        &Cpu::ADCR,     &Cpu::IMP },
        { "ADC",     4,        &Cpu::ADCR,     &Cpu::IMP },
        { "ADC",     4,        &Cpu::ADCR,     &Cpu::IMP },
        { "ADC",     4,        &Cpu::ADCR,     &Cpu::IMP },
        { "ADC",     4,        &Cpu::ADCR,     &Cpu::IMP },
        { "ADC",     4,        &Cpu::ADCR,     &Cpu::IMP },
        { "ADC",     7,        &Cpu::ADCM,     &Cpu::HLM },
        { "ADC",     4,        &Cpu::ADCR,     &Cpu::IMP },
        
        // 0x9 - 0xF
        
        { "SUB",     4,        &Cpu::SUBR,     &Cpu::IMP },
        { "SUB",     4,        &Cpu::SUBR,     &Cpu::IMP },
        { "SUB",     4,        &Cpu::SUBR,     &Cpu::IMP },
        { "SUB",     4,        &Cpu::SUBR,     &Cpu::IMP },
        { "SUB",     4,        &Cpu::SUBR,     &Cpu::IMP },
        { "SUB",     4,        &Cpu::SUBR,     &Cpu::IMP },
        { "SUB",     7,        &Cpu::SUBM,     &Cpu::HLM },
        { "SUB",     4,        &Cpu::SUBR,     &Cpu::IMP },
        { "SBB",     4,        &Cpu::SBBR,     &Cpu::IMP },
        { "SBB",     4,        &Cpu::SBBR,     &Cpu::IMP },
        { "SBB",     4,        &Cpu::SBBR,     &Cpu::IMP },
        { "SBB",     4,        &Cpu::SBBR,     &Cpu::IMP },
        { "SBB",     4,        &Cpu::SBBR,     &Cpu::IMP },
        { "SBB",     4,        &Cpu::SBBR,     &Cpu::IMP },
        { "SBB",     7,        &Cpu::SBBM,     &Cpu::HLM },
        { "SBB",     4,        &Cpu::SBBR,     &Cpu::IMP },
        
        // 0xA - 0xF
        
        { "ANA",     4,        &Cpu::ANAR,     &Cpu::IMP },
        { "ANA",     4,        &Cpu::ANAR,     &Cpu::IMP },
        { "ANA",     4,        &Cpu::ANAR,     &Cpu::IMP },
        { "ANA",     4,        &Cpu::ANAR,     &Cpu::IMP },
        { "ANA",     4,        &Cpu::ANAR,     &Cpu::IMP },
        { "ANA",     4,        &Cpu::ANAR,     &Cpu::IMP },
        { "ANA",     7,        &Cpu::ANAM,     &Cpu::HLM },
        { "ANA",     4,        &Cpu::ANAR,     &Cpu::IMP },
        { "XRA",     4,        &Cpu::XRAR,     &Cpu::IMP },
        { "XRA",     4,        &Cpu::XRAR,     &Cpu::IMP },
        { "XRA",     4,        &Cpu::XRAR,     &Cpu::IMP },
        { "XRA",     4,        &Cpu::XRAR,     &Cpu::IMP },
        { "XRA",     4,        &Cpu::XRAR,     &Cpu::IMP },
        { "XRA",     4,        &Cpu::XRAR,     &Cpu::IMP },
        { "XRA",     7,        &Cpu::XRAM,     &Cpu::HLM },
        { "XRA",     4,        &Cpu::XRAR,     &Cpu::IMP },
        
        // 0xB - 0xF
        
        { "ORA",     4,        &Cpu::ORAR,     &Cpu::IMP },
        { "ORA",     4,        &Cpu::ORAR,     &Cpu::IMP },
        { "ORA",     4,        &Cpu::ORAR,     &Cpu::IMP },
        { "ORA",     4,        &Cpu::ORAR,     &Cpu::IMP },
        { "ORA",     4,        &Cpu::ORAR,     &Cpu::IMP },
        { "ORA",     4,        &Cpu::ORAR,     &Cpu::IMP },
        { "ORA",     7,        &Cpu::ORAM,     &Cpu::HLM },
        { "ORA",     4,        &Cpu::ORAR,     &Cpu::IMP },
        { "CMP",     4,        &Cpu::CMPR,     &Cpu::IMP },
        { "CMP",     4,        &Cpu::CMPR,     &Cpu::IMP },
        { "CMP",     4,        &Cpu::CMPR,     &Cpu::IMP },
        { "CMP",     4,        &Cpu::CMPR,     &Cpu::IMP },
        { "CMP",     4,        &Cpu::CMPR,     &Cpu::IMP },
        { "CMP",     4,        &Cpu::CMPR,     &Cpu::IMP },
        { "CMP",     7,        &Cpu::CMPM,     &Cpu::HLM },
        { "CMP",     4,        &Cpu::CMPR,     &Cpu::IMP },
        
        // 0xC - 0xF
        
        { "RNZ",     5,        &Cpu::RNZ,      &Cpu::IMP },
        { "POP",    10,        &Cpu::POPR,     &Cpu::IMP },
        { "JNZ",    10,        &Cpu::JNZ,      &Cpu::DIR },
        { "JMP",    10,        &Cpu::JMP,      &Cpu::DIR },
        { "CNZ",    11,        &Cpu::CNZ,      &Cpu::DIR },
        { "PUSH",   11,        &Cpu::PUSHR,    &Cpu::IMP },
        { "ADI",     7,        &Cpu::ADI,      &Cpu::IMM },
        { "RST",    11,        &Cpu::RST,      &Cpu::IMP },
        { "RZ",      5,        &Cpu::RZ,       &Cpu::IMP },
        { "RET",    10,        &Cpu::RET,      &Cpu::IMP },
        { "JZ",     10,        &Cpu::JZ,       &Cpu::DIR },
        { "JMP",    10,        &Cpu::JMP,      &Cpu::DIR }, // <~ JMP undocumented?
        { "CZ",     11,        &Cpu::CZ,       &Cpu::DIR },
        { "CALL",   17,        &Cpu::CALL,     &Cpu::DIR },
        { "ACI",     7,        &Cpu::ACI,      &Cpu::IMM },
        { "RST",    11,        &Cpu::RST,      &Cpu::IMP },
        
        // 0xD - 0xF
        
        { "RNC",     5,        &Cpu::RNC,      &Cpu::IMP },
        { "POP",    10,        &Cpu::POPR,     &Cpu::IMP },
        { "JNC",    10,        &Cpu::JNC,      &Cpu::DIR },
        { "OUT",    10,        &Cpu::OUT,      &Cpu::IMM },
        { "CNC",    11,        &Cpu::CNC,      &Cpu::DIR },
        { "PUSH",   11,        &Cpu::PUSHR,    &Cpu::IMP },
        { "SUI",     7,        &Cpu::SUI,      &Cpu::IMM },
        { "RST",    11,        &Cpu::RST,      &Cpu::IMP },
        { "RC",      5,        &Cpu::RC,       &Cpu::IMP },
        { "RET",    10,        &Cpu::RET,      &Cpu::IMP }, // <~ RET undocumented?
        { "JC",     10,        &Cpu::JC,       &Cpu::DIR },
        { "IN",     10,        &Cpu::IN,       &Cpu::IMM },
        { "CC",     11,        &Cpu::CC,       &Cpu::DIR },
        { "CALL",   17,        &Cpu::CALL,     &Cpu::DIR }, // <~ CALL undocumented?
        { "SBI",     7,        &Cpu::SBI,      &Cpu::IMM },
        { "RST",    11,        &Cpu::RST,      &Cpu::IMP },
        
        // 0xE - 0xF
        
        { "RPO",     5,        &Cpu::RPO,      &Cpu::IMP },
        { "POP",    10,        &Cpu::POPR,     &Cpu::IMP },
        { "JPO",    10,        &Cpu::JPO,      &Cpu::DIR },
        { "XTHL",   18,        &Cpu::XTHL,     &Cpu::IMP },
        { "CPO",    11,        &Cpu::CPO,      &Cpu::DIR },
        { "PUSH",   11,        &Cpu::PUSHR,    &Cpu::IMP },
        { "ANI",     7,        &Cpu::ANI,      &Cpu::IMM },
        { "RST",    11,        &Cpu::RST,      &Cpu::IMP },
        { "RPE",     5,        &Cpu::RPE,      &Cpu::IMP },
        { "PCHL",    5,        &Cpu::PCHL,     &Cpu::IMP },
        { "JPE",    10,        &Cpu::JPE,      &Cpu::DIR },
        { "XCHG",    4,        &Cpu::XCHG,     &Cpu::IMP },
        { "CPE",    11,        &Cpu::CPE,      &Cpu::DIR },
        { "CALL",   17,        &Cpu::CALL,     &Cpu::DIR }, // <~ CALL undocumented?
        { "XDI",     7,        &Cpu::XRI,      &Cpu::IMM },
        { "RST",    11,        &Cpu::RST,      &Cpu::IMP },
        
        // 0xF - 0xF
        
        { "RP",      5,        &Cpu::RP,       &Cpu::IMP },
        { "POP",    10,        &Cpu::POP,      &Cpu::IMP },
        { "JP",     10,        &Cpu::JP,       &Cpu::DIR },
        { "DI",      4,        &Cpu::DI,       &Cpu::IMP },
        { "CP",     11,        &Cpu::CP,       &Cpu::DIR },
        { "PUSH",   11,        &Cpu::PUSH,     &Cpu::IMP },
        { "ORI",     7,        &Cpu::ORI,      &Cpu::IMM },
        { "RST",    11,        &Cpu::RST,      &Cpu::IMP },
        { "RM",      5,        &Cpu::RM,       &Cpu::IMP },
        { "SPHL",    5,        &Cpu::SPHL,     &Cpu::IMP },
        { "JM",     10,        &Cpu::JM,       &Cpu::DIR },
        { "EI",      4,        &Cpu::EI,       &Cpu::IMP },
        { "CM",     11,        &Cpu::CM,       &Cpu::DIR },
        { "CALL",   17,        &Cpu::CALL,     &Cpu::DIR }, // <~ CALL undocumented?
        { "CPI",     7,        &Cpu::CPI,      &Cpu::IMM },
        { "RST",    11,        &Cpu::RST,      &Cpu::IMP }
    };
}

void Cpu::clock()
{
    ticks++;

    if (cycles > 0)
    {
        // Set additional delay?
        cycles--;

        return;
    }

#ifndef LOGTEST
    uint16_t pcl = counter;
#endif
    
    // Read operation code
    opcode = read(counter);
    
    // Increment program counter
    counter++;
    
    // Set min program cycles
    cycles = lookup[opcode].cycles;
    
    // Set address mode
    (this->*lookup[opcode].addrmod)();
    
    // Execute operation and add extra cycles
    cycles += (this->*lookup[opcode].operate)();
    
#ifndef LOGTEST
    ::log(pcl, this);
#endif
}

void Cpu::setCounter(uint16_t counter)
{
    this -> counter = counter;
}

#pragma mark -
#pragma mark Pairs

// Read source register
uint8_t * Cpu::readsrc()
{
    return & registers[opcode & 0x07];
}

// Read destination register
uint8_t * Cpu::readdst()
{
    return & registers[(opcode & 0x38) >> 3];
}

// Read registry pair as uint16_t
uint16_t Cpu::readpair(uint8_t index)
{
    auto pair = regpairs[index];
    
    uint16_t hi = *(pair + 0);
    uint16_t lo = *(pair + 1);

    return (hi << 8) | lo;
}

// Write uint16_t to registry pair
void Cpu::writepair(uint8_t index, uint16_t data)
{
    *(regpairs[index] + 0) = (data >> 8) & 0xFF;
    *(regpairs[index] + 1) = data & 0xFF;
}

// Mutate registry pair
void Cpu::mutatepair(uint8_t index, std::function<void(uint16_t &)> mutator)
{
    uint16_t pair = readpair(index);
    mutator(pair);
    writepair(index, pair);
}

#pragma mark -
#pragma mark Bus communication

uint8_t Cpu::read()
{
    return read(address);
}

uint8_t Cpu::read(uint16_t address)
{
    return bus -> read(address);
}

void Cpu::write(uint8_t data)
{
    write(address, data);
}

void Cpu::write(uint16_t address, uint8_t data)
{
    bus -> write(address, data);
}

void Cpu::connect(std::shared_ptr<Bus> bus)
{
    this -> bus = bus;
}

#pragma mark -
#pragma mark Addressing modes

// No set address pointer
void Cpu::IMP()
{
    address = 0x00;
}

// Set address pointer to accumulator
void Cpu::IND()
{
    address = registers[A];
}

// Set address pointer to A16
void Cpu::DIR()
{
    uint16_t lo = read(counter++);
    uint16_t hi = read(counter++);
    
    address = (hi << 8) | lo;
}

// Set address pointer to D8
void Cpu::IMM()
{
    address = counter++;
}

// Set address pointer to H & L registry pair
void Cpu::HLM()
{
    uint16_t lo = registers[L];
    uint16_t hi = registers[H];
    
    address = (hi << 8) | lo;
}

#pragma mark -
#pragma mark Move, Load, Store

// Code: MOV r1, r2
// Operation: (r2) → r1
// Description: Move register to register
uint8_t Cpu::MOVRR()
{
    *readdst() = *readsrc();
    return 0;
}

// Code: MOV M, r
// Operation: (r) → [(HL)]
// Description: Move register to memory
uint8_t Cpu::MOVMR()
{
    auto value = *readsrc();
    write(value);
    
    return 0;
}

// Code: MOV r, M
// Operation: [(HL)] → r
// Description: Move memory to register
uint8_t Cpu::MOVRM()
{
    *readdst() = read();
    return 0;
}

// Code: MVI r, D8
// Operation: D8 → r
// Description: Move immediate register
uint8_t Cpu::MVIR()
{
    return MOVRM();
}

// Code: MVI M, D8
// Operation: D8 → [(HL)]
// Description: Move immediate memory
uint8_t Cpu::MVIM()
{
    auto value = read();
    
    uint16_t lo = registers[L];
    uint16_t hi = registers[H];

    write((hi << 8) | lo, value);
    
    return 0;
}

// Code: LXI RP
// Operation: D16 → RP
// Description: Load immediate register pair B & C
uint8_t Cpu::LXI()
{
    writepair((opcode & 0x30) >> 4, address);
    return 0;
}

// Code: LXI SP
// Operation: D16 → SP
// Description: Load immediate SP
uint8_t Cpu::LXISP()
{
    stack = address;
    return 0;
}

// Code: STAX B
// Operation: (A) → [(RP)]
// Description: Store A indent
uint8_t Cpu::STAX()
{
    auto pair = (opcode & 0x10) >> 4;
    auto data = readpair(pair);

    write(data, registers[A]);
    
    return 0;
}

// Code: LDAX D
// Operation: [(RP)] → A
// Description: Load A indirect
uint8_t Cpu::LDAX()
{
    auto pair = (opcode & 0x10) >> 4;
    auto data = readpair(pair);
    
    registers[A] = read(data);
    
    return 0;
}

// Code: STA A16
// Operation: (A) → [(A16)]
// Description: Store A direct
uint8_t Cpu::STA()
{
    write(registers[A]);
    return 0;
}

// Code: LDA A16
// Operation: [(A16)] → A
// Description: Load A direct
uint8_t Cpu::LDA()
{
    registers[A] = read();
    return 0;
}

// Code: SHLD A16
// Operation: (L) → [A16], (H) → [A16+1]
// Description: Store H & L direct
uint8_t Cpu::SHLD()
{
    write(address + 0, registers[L]);
    write(address + 1, registers[H]);
    
    return 0;
}

// Code: LHLD A16
// Operation: [A16] → L, [A16+1] → H
// Description: Load H & L direct
uint8_t Cpu::LHLD()
{
    registers[L] = read(address + 0);
    registers[H] = read(address + 1);
    
    return 0;
}

// Code: XCHG
// Operation: (HL) ↔ (DE)
// Description: Echange D & E, H & L registers
uint8_t Cpu::XCHG()
{
    auto exchange = [](uint8_t & x, uint8_t & y)
    {
        x ^= y;
        y ^= x;
        x ^= y;
    };
    
    exchange(registers[D], registers[H]);
    exchange(registers[E], registers[L]);
    
    return 0;
}

#pragma mark -
#pragma mark Stack operations

// Code: PUSH
// Operation: A → [(SP) - 1], (SR) → [(SP) - 2]
// Description: Push program status word on stack
// Flags: -
uint8_t Cpu::PUSH  (uint8_t hi, uint8_t lo)
{
    write(--stack, hi);
    write(--stack, lo);
    
    return 0;
}

// Code: POP
// Operation: [(SP)] → L, [(SP) + 1] → H
// Description: Pop register pair off stack
// Flags: -
uint8_t Cpu::POP   (uint8_t & hi, uint8_t & lo)
{
    lo = read(stack++);
    hi = read(stack++);
    
    return 0;
}

// Code: PUSH rp
// Operation: (RPH) → [(SP) - 1], (RPL) → [(SP)- 2]
// Description: Push register pair on stack
// Flags: -
uint8_t Cpu::PUSHR ()
{
    auto pair = regpairs[(opcode & 0x30) >> 4];
    
    return PUSH(
        *(pair + 0),
        *(pair + 1)
    );
}

// Code: PUSH PSW
// Operation: A → [(SP) - 1], (SR) → [(SP) - 2]
// Description: Push program status word on stack
// Flags: -
uint8_t Cpu::PUSH  ()
{
    return PUSH(registers[A], status);
}

// Code: POP rp
// Operation: [(SP)] → RPL, [(SP) + 1] → RPH
// Description: Pop register pair off stack
// Flags: -
uint8_t Cpu::POPR  ()
{
    auto pair = regpairs[(opcode & 0x30) >> 4];
    
    return POP(
       *(pair + 0),
       *(pair + 1)
   );
}

// Code: POP PSW
// Operation: [(SP)] → A, [(SP) + 1] → SR
// Description: Pop register pair off stack
// Flags: -
uint8_t Cpu::POP   ()
{
    uint8_t status = status;
    uint8_t cycles = POP(registers[A], status);
    
    status = status;
    
    return cycles;
}

// Code: XTHL
// Operation: [(SP)] ↔ (L), [(SP) + 1] ↔ (H)
// Description: Exchange top of stack, H & L
// Flags: -
uint8_t Cpu::XTHL  ()
{
    uint8_t hi = 0x00;
    uint8_t lo = 0x00;
    
    POP(hi, lo);
    PUSH(registers[H], registers[L]);
    
    registers[H] = hi;
    registers[L] = lo;
    
    return 0;
}

// Code: SPHL
// Operation: (HL) → (SP)
// Description: H & L to stack pointer
// Flags: -
uint8_t Cpu::SPHL  ()
{
    stack = readpair(HL);
    return 0;
}

#pragma mark -
#pragma mark Jump

uint8_t Cpu::JMP (uint8_t flag)
{
    if (flag == 0)
    {
        return 0;
    }
    
    return JMP();
}

uint8_t Cpu::JMPN (uint8_t flag)
{
    return JMP(!flag);
}

// Code: JMP
// Operation: [A16] → PC
// Description: Jump unconditional
// Flags: -
uint8_t Cpu::JMP  ()
{
    counter = address;
    return 0;
}

// Code: JC
// Operation: [A16] → PC
// Description: Jump on carry
// Flags: -
uint8_t Cpu::JC   ()
{
    auto flag = status.GetCarry();
    return JMP(flag);
}

// Code: JNC
// Operation: [A16] → PC
// Description: Jump on no carry
// Flags: -
uint8_t Cpu::JNC  ()
{
    auto flag = status.GetCarry();
    return JMPN(flag);
}

// Code: JZ
// Operation: [A16] → PC
// Description: Jump on zero
// Flags: -
uint8_t Cpu::JZ   ()
{
    auto flag = status.GetZero();
    return JMP(flag);
}

// Code: JNZ
// Operation: [A16] → PC
// Description: Jump on no zero
// Flags: -
uint8_t Cpu::JNZ  ()
{
    auto flag = status.GetZero();
    return JMPN(flag);
}

// Code: JP
// Operation: [A16] → PC
// Description: Jump on positive
// Flags: -
uint8_t Cpu::JP   ()
{
    auto flag = status.GetSign();
    return JMPN(flag);
}

// Code: JM
// Operation: [A16] → PC
// Description: Jump on minus
// Flags: -
uint8_t Cpu::JM   ()
{
    auto flag = status.GetSign();
    return JMP(flag);
}

// Code: JPE
// Operation: [A16] → PC
// Description: Jump on parity even
// Flags: -
uint8_t Cpu::JPE  ()
{
    auto flag = status.GetParity();
    return JMP(flag);
}

// Code: JPO
// Operation: [A16] → PC
// Description: Jump on parity odd
// Flags: -
uint8_t Cpu::JPO  ()
{
    auto flag = status.GetParity();
    return JMPN(flag);
}

// Code: PCHL
// Operation: (H) → PCH, (L) → PCL
// Description: H & L to program counter
// Flags: -
uint8_t Cpu::PCHL ()
{
    counter = readpair(HL);
    return 0;
}

#pragma mark -
#pragma mark Call

uint8_t Cpu::CALL (uint8_t flag)
{
    if (flag == 0)
    {
        return 0;
    }
    
    CALL();
    return 6;
}

uint8_t Cpu::CALN (uint8_t flag)
{
    return CALL(!flag);
}

// Code: CALL 
// Operation: (PCH) → [(SP)-1], (PCL) → [(SP)-2], A16 → PC
// Description: Call unconditional
// Flags: -
uint8_t Cpu::CALL ()
{
    PUSH((counter >> 8) & 0xFF, counter & 0xFF);
    counter = address;
    
    return 0;
}

// Code: CC
// Operation: (PCH) → [(SP)-1], (PCL) → [(SP)-2], A16 → PC
// Description: Call on carry
// Flags: -
uint8_t Cpu::CC   ()
{
    auto flag = status.GetCarry();
    return CALL(flag);
}

// Code: CNC
// Operation: (PCH) → [(SP)-1], (PCL) → [(SP)-2], A16 → PC
// Description: Call on no carry
// Flags: -
uint8_t Cpu::CNC  ()
{
    auto flag = status.GetCarry();
    return CALN(flag);
}

// Code: CZ
// Operation: (PCH) → [(SP)-1], (PCL) → [(SP)-2], A16 → PC
// Description: Call on zero
// Flags: -
uint8_t Cpu::CZ   ()
{
    auto flag = status.GetZero();
    return CALL(flag);
}

// Code: CNZ
// Operation: (PCH) → [(SP)-1], (PCL) → [(SP)-2], A16 → PC
// Description: Call on no zero
// Flags: -
uint8_t Cpu::CNZ  ()
{
    auto flag = status.GetZero();
    return CALN(flag);
}

// Code: CP
// Operation: (PCH) → [(SP)-1], (PCL) → [(SP)-2], A16 → PC
// Description: Call on positive
// Flags: -
uint8_t Cpu::CP   ()
{
    auto flag = status.GetSign();
    return CALN(flag);
}

// Code: CM
// Operation: (PCH) → [(SP)-1], (PCL) → [(SP)-2], A16 → PC
// Description: Call on minus
// Flags: -
uint8_t Cpu::CM   ()
{
    auto flag = status.GetSign();
    return CALL(flag);
}

// Code: CPE
// Operation: (PCH) → [(SP)-1], (PCL) → [(SP)-2], A16 → PC
// Description: Call on parity even
// Flags: -
uint8_t Cpu::CPE  ()
{
    auto flag = status.GetParity();
    return CALL(flag);
}

// Code: CPO
// Operation: (PCH) → [(SP)-1], (PCL) → [(SP)-2], A16 → PC
// Description: Call on parity odd
// Flags: -
uint8_t Cpu::CPO  ()
{
    auto flag = status.GetParity();
    return CALN(flag);
}

#pragma mark -
#pragma mark Return

// Return if positive
uint8_t Cpu::RET (uint8_t flag)
{
    if (flag == 0)
    {
        return 0;
    }
    
    RET();
    return 6;
}

// Return if negative
uint8_t Cpu::RETN (uint8_t flag)
{
    return RET(!flag);
}

// Code: RET
// Operation: [(SP)] → PCL, [(SP)+1] → PCH
// Description: Return
// Flags: -
uint8_t Cpu::RET  ()
{
    uint8_t lo = 0x00;
    uint8_t hi = 0x00;
    
    POP(hi, lo);

    counter = ((uint16_t) hi << 8) | lo;
    
    return 0;
}

// Code: RC
// Operation: [(SP)] → PCL, [(SP)+1] → PCH
// Description: Return if carry set
// Flags: -
uint8_t Cpu::RC   ()
{
    auto flag = status.GetCarry();
    return RET(flag);
}

// Code: RC
// Operation: [(SP)] → PCL, [(SP)+1] → PCH
// Description: Return if carry reset
// Flags: -
uint8_t Cpu::RNC  ()
{
    auto flag = status.GetCarry();
    return RETN(flag);
}

// Code: RZ
// Operation: [(SP)] → PCL, [(SP)+1] → PCH
// Description: Return if zero set
// Flags: -
uint8_t Cpu::RZ   ()
{
    auto flag = status.GetZero();
    return RET(flag);
}

// Code: RNZ
// Operation: [(SP)] → PCL, [(SP)+1] → PCH
// Description: Return if zero reset
// Flags: -
uint8_t Cpu::RNZ  ()
{
    auto flag = status.GetZero();
    return RETN(flag);
}

// Code: RM
// Operation: [(SP)] → PCL, [(SP)+1] → PCH
// Description: Return if minus
// Flags: -
uint8_t Cpu::RM   ()
{
    auto flag = status.GetSign();
    return RET(flag);
}

// Code: RP
// Operation: [(SP)] → PCL, [(SP)+1] → PCH
// Description: Return if plus
// Flags: -
uint8_t Cpu::RP   ()
{
    auto flag = status.GetSign();
    return RETN(flag);
}

// Code: RPE
// Operation: [(SP)] → PCL, [(SP)+1] → PCH
// Description: Return if parity even
// Flags: -
uint8_t Cpu::RPE  ()
{
    auto flag = status.GetParity();
    return RET(flag);
}

// Code: RPO
// Operation: [(SP)] → PCL, [(SP)+1] → PCH
// Description: Return if parity odd
// Flags: -
uint8_t Cpu::RPO  ()
{
    auto flag = status.GetParity();
    return RETN(flag);
}

#pragma mark -
#pragma mark Restart

// Code: RST
// Operation: (PCH) → [(SP)-1], (PCL) → [(SP)-2], 0000 0000 00NN N000 → PC
// Description: Restart
uint8_t Cpu::RST  ()
{
    auto hi = (counter >> 8) & 0xFF;
    auto lo = counter & 0x00FF;
    
    PUSH(hi, lo);
    
    counter = (uint16_t) opcode & 0x38;
    
    return 0;
}

#pragma mark -
#pragma mark Increment and decrement


// Code: INR R
// Operation: (r) + 1 → r
// Description: Increment register
// Flags: S,Z,AC,P
uint8_t Cpu::INR (uint16_t value)
{
    *readdst() = ++value & 0x00FF;
    
    status.SetDecFlags(value);
    status.SetAux((value & 0x000F) == 0);
    
    return 0;
}

// Code: INR R
// Operation: (r) + 1 → r
// Description: Increment register
// Flags: S,Z,AC,P
uint8_t Cpu::INRR ()
{
    uint16_t value = *readdst();
    return INR(value);
}

// Code: INR M
// Operation: [(HL)] + 1 → [(HL)]
// Description: Increment memory
// Flags: S,Z,AC,P
uint8_t Cpu::INRM ()
{
    uint16_t value = read();
    write(++value);
    
    status.SetDecFlags(value);
    status.SetAux((value & 0x000F) == 0x0000);
    
    return 0;
}

// Code: DCR r
// Operation: (r) – 1 → r
// Description: Decrement register
// Flags: S,Z,AC,P
uint8_t Cpu::DCR (uint16_t value)
{
    *readdst() = --value & 0x00FF;
    
    status.SetDecFlags(value);
    status.SetAux((value & 0x000F) != 0x000F);
    
    return 0;
}

// Code: DCR r
// Operation: (r) – 1 → r
// Description: Decrement register
// Flags: S,Z,AC,P
uint8_t Cpu::DCRR ()
{
    uint16_t value = *readdst();
    return DCR(value);
}

// Code: DCR M
// Operation: [(HL)] - 1 → [(HL)]
// Description: Decrement memory
// Flags: S,Z,AC,P
uint8_t Cpu::DCRM ()
{
    uint16_t value = read();
    write(--value);
    
    status.SetDecFlags(value);
    status.SetAux((value & 0x000F) != 0x000F);
    
    return 0;
}

// Code: INX RP
// Operation: (RP) + 1 → r
// Description: Increment registry pair
// Flags: -
uint8_t Cpu::INX  ()
{
    mutatepair((opcode & 0x30) >> 4, [](uint16_t & pair) { pair++; });
    return 0;
}

// Code: INX SP
// Operation: (RP) + 1 → r
// Description: Increment registry pair
// Flags: -
uint8_t Cpu::INXSP  ()
{
    stack++;
    return 0;
}

// Code: DCX RP
// Operation: (RP) - 1 → r
// Description: Decrement registry pair
// Flags: -
uint8_t Cpu::DCX  ()
{
    mutatepair((opcode & 0x30) >> 4, [](uint16_t & pair) { pair--; });
    return 0;
}

// Code: DCX SP
// Operation: (RP) - 1 → r
// Description: Decrement SP
// Flags: -
uint8_t Cpu::DCXSP  ()
{
    stack--;
    return 0;
}

#pragma mark -
#pragma mark Add

uint8_t Cpu::ADD(uint8_t value, uint8_t carry)
{
    uint16_t acc = registers[A];
    uint16_t tmp = acc + value + carry;
    registers[A] = tmp & 0x00FF;
    
    status.SetDecFlags(tmp);
    
    uint16_t hc = tmp ^ acc ^ value;

    status.SetAux   ((bool) (hc & (1 << 4)));
    status.SetCarry ((bool) (hc & (1 << 8))); // Not usual
    
    return 0;
}

uint8_t Cpu::ADC(uint8_t data)
{
    auto carry = status.GetCarry();
    return ADD (data, carry);
}

// Code: ADD r
// Operation: (A) + (r) → A
// Description: Add register to A
// Flags: S,Z,AC,P,C
uint8_t Cpu::ADDR ()
{
    auto value = *readsrc();
    return ADD(value);
}

// Code: ADD M
// Operation: (A) + М → A
// Description: Add memory to A
// Flags: S,Z,AC,P,C
uint8_t Cpu::ADDM ()
{
    auto value = read();
    return ADD(value);
}

// Code: ADC r
// Operation: (A) + (r) + C → A
// Description: Add register to A with carry
// Flags: S,Z,AC,P,C
uint8_t Cpu::ADCR ()
{
    auto value = *readsrc();
    return ADC(value);
}

// Code: ADC M
// Operation: (A) + М + С → A
// Description: Add memory to A with carry
// Flags: S,Z,AC,P,C
uint8_t Cpu::ADCM ()
{
    auto value = read();
    return ADC(value);
}

// Code: ADI D8
// Operation: (A) + D8 → A
// Description: Add immediate to A
// Flags: S,Z,AC,P,C
uint8_t Cpu::ADI ()
{
    return ADDM();
}

// Code: ACI D8
// Operation: (A) + D8 + C → A
// Description: Add immediate to A with carry
// Flags: S,Z,AC,P,C
uint8_t Cpu::ACI  ()
{
    return ADCM();
}

// Code: DAD rp
// Operation: (HL) + (RP) → HL
// Description: Add part to H & L
// Flags: C
uint8_t Cpu::DAD  (uint16_t value)
{
    uint32_t hl  = readpair(HL);
    uint32_t tmp = (uint32_t) value + hl;
    writepair(HL, tmp & 0xFFFF);
    
    status.SetCarry((bool)(tmp & 0x10000L));
    
    return 0;
}

// Code: DAD rp
// Operation: (HL) + (RP) → HL
// Description: Add part to H & L
// Flags: C
uint8_t Cpu::DAD  ()
{
    uint16_t rpdata = readpair((opcode & 0x30) >> 4);
    return DAD(rpdata);
}

// Code: DAD SP
// Operation: (HL) + (SP) → HL
// Description: Add part to H & L
// Flags: C
uint8_t Cpu::DADSP  ()
{
    return DAD(stack);
}

#pragma mark -
#pragma mark Substract

uint8_t Cpu::SUB(uint8_t data, uint8_t carry)
{
    ADD(~data, !carry);
    status.InvertCarry();
    
    return 0;
}

uint8_t Cpu::SBB(uint8_t data)
{
    auto carry = status.GetCarry();
    return SUB (data, carry);
}

// Code: SUB r
// Operation: (A) - (r) → A
// Description: Substract register from A
// Flags: S,Z,AC,P,C
uint8_t Cpu::SUBR ()
{
    auto value = *readsrc();
    return SUB(value);
}

// Code: SUB M
// Operation: (A) – М → A
// Description: Substract memory from A
// Flags: S,Z,AC,P,C
uint8_t Cpu::SUBM ()
{
    auto value = read();
    return SUB(value);
}

// Code: SBB r
// Operation: (A) - (r) - C → A
// Description: Substract register from A with borrow
// Flags: S,Z,AC,P,C
uint8_t Cpu::SBBR ()
{
    auto value = *readsrc();
    return SBB(value);
}

// Code: SBB M
// Operation: (A) – М - C → A
// Description: Substract memory from A with borrow
// Flags: S,Z,AC,P,C
uint8_t Cpu::SBBM ()
{
    auto value = read();
    return SBB(value);
}

// Code: SUI D8
// Operation: (A) - D8 → A
// Description: Substract immediate from A
// Flags: S,Z,AC,P,C
uint8_t Cpu::SUI  ()
{
    return SUBM();
}

// Code: DBI D8
// Operation: (A) - D8 - C → A
// Description: Substract immediate from A with borrow
// Flags: S,Z,AC,P,C
uint8_t Cpu::SBI  ()
{
    return SBBM ();
}

#pragma mark -
#pragma mark Logical

uint8_t Cpu::ANA  (uint8_t data)
{
    status.SetAux(((registers[A] | data) & 0x08) != 0);
    
    registers[A] &= data;
    
    status.SetDecFlags (registers[A]);
    status.SetCarry    (false);
    
    return 0;
}

uint8_t Cpu::XRA  (uint8_t data)
{
    registers[A] ^= data;
    
    status.SetDecFlags (registers[A]);
    status.SetCarry    (false);
    status.SetAux      (false);
    
    return 0;
}

uint8_t Cpu::ORA  (uint8_t data)
{
    registers[A] |= data;
    
    status.SetDecFlags (registers[A]);
    status.SetCarry    (false);
    status.SetAux      (false);
    
    return 0;
}

uint8_t Cpu::CMP (uint8_t value)
{
    uint16_t acc = registers[A];
    uint16_t tmp = acc - value;
    
    status.SetAllFlags(tmp);
    status.SetAux((bool)(~(acc ^ tmp ^ value) & 0x10));
    
    return 0;
}

// Code: ANA r
// Operation: (A) & (r) → A
// Description: And register with A
// Flags: S,Z,AC=*,P,C=0
uint8_t Cpu::ANAR ()
{
    auto value = *readsrc();
    return ANA(value);
}

// Code: ANA M
// Operation: (A) & M → A
// Description: And memory with A
// Flags: S,Z,AC=*,P,C=0
uint8_t Cpu::ANAM ()
{
    auto value = read();
    return ANA(value);
}

// Code: XRA r
// Operation: (A) ^ r → A
// Description: Exclusive or register with A
// Flags: S,Z,AC=0,P,C=0
uint8_t Cpu::XRAR ()
{
    auto value = *readsrc();
    return XRA(value);
}

// Code: XRA M
// Operation: (A) ^ M → A
// Description: Exclusive or memory with A
// Flags: S,Z,AC=0,P,C=0
uint8_t Cpu::XRAM ()
{
    auto value = read();
    return XRA(value);
}

// Code: ORA r
// Operation: (A) | r → A
// Description: Or register with A
// Flags: S,Z,AC,P,C=0
uint8_t Cpu::ORAR ()
{
    auto value = *readsrc();
    return ORA(value);
}

// Code: ORA M
// Operation: (A) | М → A
// Description: Or memory with A
// Flags: S,Z,AC,P,C=0
uint8_t Cpu::ORAM ()
{
    auto value = read();
    return ORA(value);
}

// Code: CMP r
// Operation: Compare
// Description: Comapre register with A
// Flags: S,Z,AC,P,C
uint8_t Cpu::CMPR ()
{
    auto value = *readsrc();
    return CMP(value);
}

// Code: CMP M
// Operation: Compare
// Description: Comapre memory with A
// Flags: S,Z,AC,P,C
uint8_t Cpu::CMPM ()
{
    auto value = read();
    return CMP(value);
}

// Code: ANI 
// Operation: (A) & D8 → A
// Description: And immediate with A
// Flags: S,Z,AC=*,P,C=0
uint8_t Cpu::ANI  ()
{
    auto value = read();
    return ANA(value);
}

// Code: XRI
// Operation: (A) ^ D8 → A
// Description: Exclusive or immediate with A
// Flags: S,Z,AC=0,P,C=0
uint8_t Cpu::XRI  ()
{
    uint8_t value = read();
    return XRA(value);
}

// Code: ORI
// Operation: (A) | D8 → A
// Description: Or immediate with A
// Flags: S,Z,AC=0,P,C=0
uint8_t Cpu::ORI  ()
{
    uint8_t value = read();
    return ORA(value);
}

// Code: CPI
// Operation: Compare
// Description: Compare immediate with A
// Flags: S,Z,AC,P,C
uint8_t Cpu::CPI  ()
{
    uint8_t value = read();
    return CMP(value);
}

#pragma mark -
#pragma mark Rotate

// Code: RLC
// Operation: C ← A7, A0 ← A7
// Description: Rotate A left
// Flags: C
uint8_t Cpu::RLC  ()
{
    uint8_t carry = (registers[A] & 0x80) >> 7;
    registers[A] = (registers[A] << 1) | carry;
    
    status.SetCarry((bool) carry);
    
    return 0;
}

// Code: RRC
// Operation: A7 → A0, A0 → C
// Description: Rotate A right
// Flags: C
uint8_t Cpu::RRC  ()
{
    uint8_t carry = registers[A] & 0x01;
    registers[A] = (registers[A] >> 1) | (carry << 7);
    
    status.SetCarry((bool) carry);
    
    return 0;
}

// Code: RAL
// Operation: A7 → C, C → A0
// Description: Rotate A left through carry
// Flags: C
uint8_t Cpu::RAL  ()
{
    uint8_t carry = (registers[A] & 0x80) >> 7;
    registers[A] = (registers[A] << 1) | status.GetCarry();
    
    status.SetCarry((bool) carry);
    
    return 0;
}

// Code: RAL
// Operation: A7 → C, C → A0
// Description: Rotate A left through carry
// Flags: C
uint8_t Cpu::RAR  ()
{
    uint8_t carry = registers[A] & 0x01;
    registers[A] = (registers[A] >> 1) | (status.GetCarry() << 7);
    
    status.SetCarry((bool) carry);
    
    return 0;
}

#pragma mark -
#pragma mark Special

// Code: CMA
// Operation: ~(A)
// Description: Complement A
// Flags: -
uint8_t Cpu::CMA  ()
{
    registers[A] = ~registers[A];
    return 0;
}

// Code: STC
// Operation: C = 1
// Description: Set carry
// Flags: C
uint8_t Cpu::STC  ()
{
    status.SetCarry(true);
    return 0;
}

// Code: CMC
// Operation: ~(C)
// Description: Complement carry
// Flags: C
uint8_t Cpu::CMC  ()
{
    status.InvertCarry();
    return 0;
}

// Code: DAA
// Description: Decimal adjust A
// Flags: S,Z,AC,P,C
uint8_t Cpu::DAA  ()
{
    uint8_t acc = registers[A];
    uint8_t add = 0x00;
    uint8_t crr = 0x00;
    
    if (status.GetAux() || (acc & 0x0F) > 0x09)
    {
        add = 0x06;
    }

    if (status.GetCarry()
        ||  (acc >> 4) >  0x09
        || ((acc >> 4) >= 0x09 && (acc & 0x0F) > 0x09))
    {
        add |= 0x60;
        crr  = 0x01;
    }
    
    ADD(add);
    status.SetCarry((bool) crr);
    
    return 0;
}

#pragma mark -
#pragma mark I/O

// Code: IN
// Operation: Input
// Flags: -
uint8_t Cpu::IN   ()
{
    return (registers[A] = 0x00);
}

// Code: OUT
// Operation: Output
// Flags: -
uint8_t Cpu::OUT  ()
{
    
#ifdef LOGTEST
    if (bus -> read(counter) == 0x00)
    {
        std::cout << std::endl;
        exit(0);

        return 0;
    }

    if (registers[C] == 0x09)
    {
        for (uint16_t i = readpair(DE); bus -> read(i) != '$'; i += 1) {
            std::cout << bus -> read(i);
        }
    }

    if (registers[C] == 0x02) {
        std::cout << registers[E];
    }
#endif
    
    return 0;
}

#pragma mark -
#pragma mark Control

// Code: EI
// Operation: Enable interrup
// Flags: INTE
uint8_t Cpu::EI   ()
{
    return 0;
}

// Code: DI
// Operation: Disable interrup
// Flags: DI
uint8_t Cpu::DI   ()
{
    return 0;
}

// Code: HLT
// Operation: Halt
uint8_t Cpu::HLT  ()
{
    return 0;
}

// Code: NOP
// Operation: No-operation
uint8_t Cpu::NOP()
{
    return 0;
}
