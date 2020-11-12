//
//  i8080.cpp
//  orion
//
//  Created by Артём Оконечников on 29.10.2020.
//

#include "i8080.hpp"
#include "Bus.hpp"

#include <iostream>
#include <iomanip>

#define LOGTEST

i8080::i8080() : reg { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }
{
    pairs[BC] = reg + B;
    pairs[DE] = reg + D;
    pairs[HL] = reg + H;
    
    lookup =
    {
        // NAME      CYCLES    OPERATION         ADDRMOD
        // ---------------------------------------------------
        
        // 0x0 - 0xF
        
        { "NOP",     4,        &i8080::NOP,      &i8080::IMP },
        { "LXI",     10,       &i8080::LXI,      &i8080::DIR },
        { "STAX",    7,        &i8080::STAX,     &i8080::IMP },
        { "INX",     5,        &i8080::INX,      &i8080::IMP },
        { "INR",     5,        &i8080::INRR,     &i8080::IMP },
        { "DCR",     5,        &i8080::DCRR,     &i8080::IMP },
        { "MVI",     7,        &i8080::MVIR,     &i8080::IMM },
        { "RLC",     4,        &i8080::RLC,      &i8080::IMP },
        { "NOP",     4,        &i8080::NOP,      &i8080::IMP },
        { "DAD",     10,       &i8080::DAD,      &i8080::IMP },
        { "LDAX",    7,        &i8080::LDAX,     &i8080::IND },
        { "DCX",     5,        &i8080::DCX,      &i8080::IMP },
        { "INR",     5,        &i8080::INRR,     &i8080::IMP },
        { "DCR",     5,        &i8080::DCRR,     &i8080::IMP },
        { "MVI",     7,        &i8080::MVIR,     &i8080::IMM },
        { "RRC",     4,        &i8080::RRC,      &i8080::IMP },
        
        // 0x1 - 0xF
        
        { "NOP",     4,        &i8080::NOP,      &i8080::IMP },
        { "LXI",     10,       &i8080::LXI,      &i8080::DIR },
        { "STAX",    7,        &i8080::STAX,     &i8080::IMP },
        { "INX",     5,        &i8080::INX,      &i8080::IMP },
        { "INR",     5,        &i8080::INRR,     &i8080::IMP },
        { "DCR",     5,        &i8080::DCRR,     &i8080::IMP },
        { "MVI",     7,        &i8080::MVIR,     &i8080::IMM },
        { "RAL",     4,        &i8080::RAL,      &i8080::IMP },
        { "NOP",     4,        &i8080::NOP,      &i8080::IMP },
        { "DAD",     10,       &i8080::DAD,      &i8080::IMP },
        { "LDAX",    7,        &i8080::LDAX,     &i8080::IND },
        { "DCX",     5,        &i8080::DCX,      &i8080::IMP },
        { "INR",     5,        &i8080::INRR,     &i8080::IMP },
        { "DCR",     5,        &i8080::DCRR,     &i8080::IMP },
        { "MVI",     7,        &i8080::MVIR,     &i8080::IMM },
        { "RAR",     4,        &i8080::RAR,      &i8080::IMP },
        
        // 0x2 - 0xF
        
        { "NOP",     4,        &i8080::NOP,      &i8080::IMP },
        { "LXI",     10,       &i8080::LXI,      &i8080::DIR },
        { "SHLD",    16,       &i8080::SHLD,     &i8080::DIR },
        { "INX",     5,        &i8080::INX,      &i8080::IMP },
        { "INR",     5,        &i8080::INRR,     &i8080::IMP },
        { "DCR",     5,        &i8080::DCRR,     &i8080::IMP },
        { "MVI",     7,        &i8080::MVIR,     &i8080::IMM },
        { "DAA",     4,        &i8080::DAA,      &i8080::IMP },
        { "NOP",     4,        &i8080::NOP,      &i8080::IMP },
        { "DAD",     10,       &i8080::DAD,      &i8080::IMP },
        { "LHLD",    16,       &i8080::LHLD,     &i8080::DIR },
        { "DCX",     5,        &i8080::DCX,      &i8080::IMP },
        { "INR",     5,        &i8080::INRR,     &i8080::IMP },
        { "DCR",     5,        &i8080::DCRR,     &i8080::IMP },
        { "MVI",     7,        &i8080::MVIR,     &i8080::IMM },
        { "CMA",     4,        &i8080::CMA,      &i8080::IMP },
        
        // 0x3 - 0xF
        
        { "NOP",     4,        &i8080::NOP,      &i8080::IMP },
        { "LXI",     10,       &i8080::LXISP,    &i8080::DIR },
        { "STA",     13,       &i8080::STA,      &i8080::DIR },
        { "INX",     5,        &i8080::INXSP,    &i8080::IMP },
        { "INR",     10,       &i8080::INRM,     &i8080::HLM },
        { "DCR",     10,       &i8080::DCRM,     &i8080::HLM },
        { "MVI",     10,       &i8080::MVIM,     &i8080::IMM },
        { "STC",     4,        &i8080::STC,      &i8080::IMP },
        { "NOP",     4,        &i8080::NOP,      &i8080::IMP },
        { "DAD",     10,       &i8080::DADSP,    &i8080::IMP },
        { "LDA",     13,       &i8080::LDA,      &i8080::DIR },
        { "DCX",     5,        &i8080::DCXSP,    &i8080::IMP },
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
        { "HLT",     4,        &i8080::HLT,      &i8080::IMP },
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
        
        // 0xC - 0xF
        
        { "RNZ",     5,        &i8080::RNZ,      &i8080::IMP },
        { "POP",    10,        &i8080::POPR,     &i8080::IMP },
        { "JNZ",    10,        &i8080::JNZ,      &i8080::DIR },
        { "JMP",    10,        &i8080::JMP,      &i8080::DIR },
        { "CNZ",    11,        &i8080::CNZ,      &i8080::DIR },
        { "PUSH",   11,        &i8080::PUSHR,    &i8080::IMP },
        { "ADI",     7,        &i8080::ADI,      &i8080::IMM },
        { "RST",    11,        &i8080::RST,      &i8080::IMP },
        { "RZ",     5,         &i8080::RZ,       &i8080::IMP },
        { "RET",    10,        &i8080::RET,      &i8080::IMP },
        { "JZ",     10,        &i8080::JZ,       &i8080::DIR },
        { "JMP",    10,        &i8080::JMP,      &i8080::DIR }, // <~ JMP undocumented?
        { "CZ",     11,        &i8080::CZ,       &i8080::DIR },
        { "CALL",   17,        &i8080::CALL,     &i8080::DIR },
        { "ACI",     7,        &i8080::ACI,      &i8080::IMM },
        { "RST",    11,        &i8080::RST,      &i8080::IMP },
        
        // 0xD - 0xF
        
        { "RNC",     5,        &i8080::RNC,      &i8080::IMP },
        { "POP",    10,        &i8080::POPR,     &i8080::IMP },
        { "JNC",    10,        &i8080::JNC,      &i8080::DIR },
        { "OUT",    10,        &i8080::OUT,      &i8080::IMM },
        { "CNC",    11,        &i8080::CNC,      &i8080::DIR },
        { "PUSH",   11,        &i8080::PUSHR,    &i8080::IMP },
        { "SUI",     7,        &i8080::SUI,      &i8080::IMM },
        { "RST",    11,        &i8080::RST,      &i8080::IMP },
        { "RC",     5,         &i8080::RC,       &i8080::IMP },
        { "RET",    10,        &i8080::RET,      &i8080::IMP }, // <~ RET undocumented?
        { "JC",     10,        &i8080::JC,       &i8080::DIR },
        { "IN",     10,        &i8080::IN,       &i8080::IMM },
        { "CC",     11,        &i8080::CC,       &i8080::DIR },
        { "CALL",   17,        &i8080::CALL,     &i8080::DIR }, // <~ CALL undocumented?
        { "SBI",     7,        &i8080::SBI,      &i8080::IMM },
        { "RST",    11,        &i8080::RST,      &i8080::IMP },
        
        // 0xE - 0xF
        
        { "RPO",     5,        &i8080::RPO,      &i8080::IMP },
        { "POP",    10,        &i8080::POPR,     &i8080::IMP },
        { "JPO",    10,        &i8080::JPO,      &i8080::DIR },
        { "XTHL",   18,        &i8080::XTHL,     &i8080::IMP },
        { "CPO",    11,        &i8080::CPO,      &i8080::DIR },
        { "PUSH",   11,        &i8080::PUSHR,    &i8080::IMP },
        { "ANI",     7,        &i8080::ANI,      &i8080::IMM },
        { "RST",    11,        &i8080::RST,      &i8080::IMP },
        { "RPE",     5,        &i8080::RPE,      &i8080::IMP },
        { "PCHL",    5,        &i8080::PCHL,     &i8080::IMP },
        { "JPE",    10,        &i8080::JPE,      &i8080::DIR },
        { "XCHG",    4,        &i8080::XCHG,     &i8080::IMP },
        { "CPE",    11,        &i8080::CPE,      &i8080::DIR },
        { "CALL",   17,        &i8080::CALL,     &i8080::DIR }, // <~ CALL undocumented?
        { "XDI",     7,        &i8080::XRI,      &i8080::IMM },
        { "RST",    11,        &i8080::RST,      &i8080::IMP },
        
        // 0xF - 0xF
        
        { "RP",      5,        &i8080::RP,       &i8080::IMP },
        { "POP",    10,        &i8080::POP,      &i8080::IMP },
        { "JP",     10,        &i8080::JP,       &i8080::DIR },
        { "DI",      4,        &i8080::DI,       &i8080::IMP },
        { "CP",     11,        &i8080::CP,       &i8080::DIR },
        { "PUSH",   11,        &i8080::PUSH,     &i8080::IMP },
        { "ORI",     7,        &i8080::ORI,      &i8080::IMM },
        { "RST",    11,        &i8080::RST,      &i8080::IMP },
        { "RM",      5,        &i8080::RM,       &i8080::IMP },
        { "SPHL",    5,        &i8080::SPHL,     &i8080::IMP },
        { "JM",     10,        &i8080::JM,       &i8080::DIR },
        { "EI",      4,        &i8080::EI,       &i8080::IMP },
        { "CM",     11,        &i8080::CM,       &i8080::DIR },
        { "CALL",   17,        &i8080::CALL,     &i8080::DIR }, // <~ CALL undocumented?
        { "CPI",     7,        &i8080::CPI,      &i8080::IMM },
        { "RST",    11,        &i8080::RST,      &i8080::IMP }
    };
}

void i8080::clock()
{
    ticks++;

    if (cycles > 0)
    {
        // Set additional delay?
        cycles--;

        return;
    }

#ifndef LOGTEST
    uint16_t pcl = pc;
#endif
    
    // Read operation code
    opcode = read(pc);
    
    // Increment program counter
    pc++;
    
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

void i8080::setCounter(uint16_t counter)
{
    pc = counter;
}

#pragma mark -
#pragma mark Pairs

// Read source register
uint8_t * i8080::readsrc()
{
    return & reg[opcode & 0x07];
}

// Read destination register
uint8_t * i8080::readdst()
{
    return & reg[(opcode & 0x38) >> 3];
}

// Read registry pair as uint16_t
uint16_t i8080::readpair(uint8_t index)
{
    auto pair = pairs[index];
    
    uint16_t hi = *(pair + 0);
    uint16_t lo = *(pair + 1);

    return (hi << 8) | lo;
}

// Write uint16_t to registry pair
void i8080::writepair(uint8_t index, uint16_t data)
{
    *(pairs[index] + 0) = (data >> 8) & 0xFF;
    *(pairs[index] + 1) = data & 0xFF;
}

// Mutate registry pair
void i8080::mutatepair(uint8_t index, std::function<void(uint16_t &)> mutator)
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
    address = 0x00;
}

// Set address pointer to accumulator
void i8080::IND()
{
    address = reg[A];
}

// Set address pointer to A16
void i8080::DIR()
{
    uint16_t lo = read(pc++);
    uint16_t hi = read(pc++);
    
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
    writepair((opcode & 0x30) >> 4, address);
    return 0;
}

// Code: LXI SP
// Operation: D16 → SP
// Description: Load immediate SP
uint8_t i8080::LXISP()
{
    sp = address;
    return 0;
}

// Code: STAX B
// Operation: (A) → [(RP)]
// Description: Store A indent
uint8_t i8080::STAX()
{
    auto pair = (opcode & 0x10) >> 4;
    auto data = readpair(pair);

    write(data, reg[A]);
    
    return 0;
}

// Code: LDAX D
// Operation: [(RP)] → A
// Description: Load A indirect
uint8_t i8080::LDAX()
{
    auto pair = (opcode & 0x10) >> 4;
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

// Code: PUSH
// Operation: A → [(SP) - 1], (SR) → [(SP) - 2]
// Description: Push program status word on stack
// Flags: -
uint8_t i8080::PUSH  (uint8_t hi, uint8_t lo)
{
    write(--sp, hi);
    write(--sp, lo);
    
    return 0;
}

// Code: POP
// Operation: [(SP)] → L, [(SP) + 1] → H
// Description: Pop register pair off stack
// Flags: -
uint8_t i8080::POP   (uint8_t & hi, uint8_t & lo)
{
    lo = read(sp++);
    hi = read(sp++);
    
    return 0;
}

// Code: PUSH rp
// Operation: (RPH) → [(SP) - 1], (RPL) → [(SP)- 2]
// Description: Push register pair on stack
// Flags: -
uint8_t i8080::PUSHR ()
{
    auto pair = pairs[(opcode & 0x30) >> 4];
    
    return PUSH(
        *(pair + 0),
        *(pair + 1)
    );
}

// Code: PUSH PSW
// Operation: A → [(SP) - 1], (SR) → [(SP) - 2]
// Description: Push program status word on stack
// Flags: -
uint8_t i8080::PUSH  ()
{
    return PUSH(reg[A], sr);
}

// Code: POP rp
// Operation: [(SP)] → RPL, [(SP) + 1] → RPH
// Description: Pop register pair off stack
// Flags: -
uint8_t i8080::POPR  ()
{
    auto pair = pairs[(opcode & 0x30) >> 4];
    
    return POP(
       *(pair + 0),
       *(pair + 1)
   );
}

// Code: POP PSW
// Operation: [(SP)] → A, [(SP) + 1] → SR
// Description: Pop register pair off stack
// Flags: -
uint8_t i8080::POP   ()
{
    uint8_t status = sr;
    uint8_t cycles = POP(reg[A], status);
    
    sr = status;
    
    return cycles;
}

// Code: XTHL
// Operation: [(SP)] ↔ (L), [(SP) + 1] ↔ (H)
// Description: Exchange top of stack, H & L
// Flags: -
uint8_t i8080::XTHL  ()
{
    uint8_t hi = 0x00;
    uint8_t lo = 0x00;
    
    POP(hi, lo);
    PUSH(reg[H], reg[L]);
    
    reg[H] = hi;
    reg[L] = lo;
    
    return 0;
}

// Code: SPHL
// Operation: (HL) → (SP)
// Description: H & L to stack pointer
// Flags: -
uint8_t i8080::SPHL  ()
{
    sp = readpair(HL);
    return 0;
}

#pragma mark -
#pragma mark Jump

uint8_t i8080::JMP (uint8_t flag)
{
    if (flag == 0)
    {
        return 0;
    }
    
    return JMP();
}

uint8_t i8080::JMPN (uint8_t flag)
{
    return JMP(!flag);
}

// Code: JMP
// Operation: [A16] → PC
// Description: Jump unconditional
// Flags: -
uint8_t i8080::JMP  ()
{
    pc = address;
    return 0;
}

// Code: JC
// Operation: [A16] → PC
// Description: Jump on carry
// Flags: -
uint8_t i8080::JC   ()
{
    auto flag = sr.GetCarry();
    return JMP(flag);
}

// Code: JNC
// Operation: [A16] → PC
// Description: Jump on no carry
// Flags: -
uint8_t i8080::JNC  ()
{
    auto flag = sr.GetCarry();
    return JMPN(flag);
}

// Code: JZ
// Operation: [A16] → PC
// Description: Jump on zero
// Flags: -
uint8_t i8080::JZ   ()
{
    auto flag = sr.GetZero();
    return JMP(flag);
}

// Code: JNZ
// Operation: [A16] → PC
// Description: Jump on no zero
// Flags: -
uint8_t i8080::JNZ  ()
{
    auto flag = sr.GetZero();
    return JMPN(flag);
}

// Code: JP
// Operation: [A16] → PC
// Description: Jump on positive
// Flags: -
uint8_t i8080::JP   ()
{
    auto flag = sr.GetSign();
    return JMPN(flag);
}

// Code: JM
// Operation: [A16] → PC
// Description: Jump on minus
// Flags: -
uint8_t i8080::JM   ()
{
    auto flag = sr.GetSign();
    return JMP(flag);
}

// Code: JPE
// Operation: [A16] → PC
// Description: Jump on parity even
// Flags: -
uint8_t i8080::JPE  ()
{
    auto flag = sr.GetParity();
    return JMP(flag);
}

// Code: JPO
// Operation: [A16] → PC
// Description: Jump on parity odd
// Flags: -
uint8_t i8080::JPO  ()
{
    auto flag = sr.GetParity();
    return JMPN(flag);
}

// Code: PCHL
// Operation: (H) → PCH, (L) → PCL
// Description: H & L to program counter
// Flags: -
uint8_t i8080::PCHL ()
{
    pc = readpair(HL);
    return 0;
}

#pragma mark -
#pragma mark Call

uint8_t i8080::CALL (uint8_t flag)
{
    if (flag == 0)
    {
        return 0;
    }
    
    CALL();
    return 6;
}

uint8_t i8080::CALN (uint8_t flag)
{
    return CALL(!flag);
}

// Code: CALL 
// Operation: (PCH) → [(SP)-1], (PCL) → [(SP)-2], A16 → PC
// Description: Call unconditional
// Flags: -
uint8_t i8080::CALL ()
{
    PUSH((pc >> 8) & 0xFF, pc & 0xFF);
    pc = address;
    
    return 0;
}

// Code: CC
// Operation: (PCH) → [(SP)-1], (PCL) → [(SP)-2], A16 → PC
// Description: Call on carry
// Flags: -
uint8_t i8080::CC   ()
{
    auto flag = sr.GetCarry();
    return CALL(flag);
}

// Code: CNC
// Operation: (PCH) → [(SP)-1], (PCL) → [(SP)-2], A16 → PC
// Description: Call on no carry
// Flags: -
uint8_t i8080::CNC  ()
{
    auto flag = sr.GetCarry();
    return CALN(flag);
}

// Code: CZ
// Operation: (PCH) → [(SP)-1], (PCL) → [(SP)-2], A16 → PC
// Description: Call on zero
// Flags: -
uint8_t i8080::CZ   ()
{
    auto flag = sr.GetZero();
    return CALL(flag);
}

// Code: CNZ
// Operation: (PCH) → [(SP)-1], (PCL) → [(SP)-2], A16 → PC
// Description: Call on no zero
// Flags: -
uint8_t i8080::CNZ  ()
{
    auto flag = sr.GetZero();
    return CALN(flag);
}

// Code: CP
// Operation: (PCH) → [(SP)-1], (PCL) → [(SP)-2], A16 → PC
// Description: Call on positive
// Flags: -
uint8_t i8080::CP   ()
{
    auto flag = sr.GetSign();
    return CALN(flag);
}

// Code: CM
// Operation: (PCH) → [(SP)-1], (PCL) → [(SP)-2], A16 → PC
// Description: Call on minus
// Flags: -
uint8_t i8080::CM   ()
{
    auto flag = sr.GetSign();
    return CALL(flag);
}

// Code: CPE
// Operation: (PCH) → [(SP)-1], (PCL) → [(SP)-2], A16 → PC
// Description: Call on parity even
// Flags: -
uint8_t i8080::CPE  ()
{
    auto flag = sr.GetParity();
    return CALL(flag);
}

// Code: CPO
// Operation: (PCH) → [(SP)-1], (PCL) → [(SP)-2], A16 → PC
// Description: Call on parity odd
// Flags: -
uint8_t i8080::CPO  ()
{
    auto flag = sr.GetParity();
    return CALN(flag);
}

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
    uint8_t lo = 0x00;
    uint8_t hi = 0x00;
    
    POP(hi, lo);

    pc = ((uint16_t) hi << 8) | lo;
    
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

// Code: RST
// Operation: (PCH) → [(SP)-1], (PCL) → [(SP)-2], 0000 0000 00NN N000 → PC
// Description: Restart
uint8_t i8080::RST  ()
{
    auto hi = (pc >> 8) & 0xFF;
    auto lo = pc & 0x00FF;
    
    PUSH(hi, lo);
    
    pc = (uint16_t) opcode & 0x38;
    
    return 0;
}

#pragma mark -
#pragma mark Increment and decrement


// Code: INR R
// Operation: (r) + 1 → r
// Description: Increment register
// Flags: S,Z,AC,P
uint8_t i8080::INR (uint16_t value)
{
    *readdst() = ++value & 0x00FF;
    
    sr.SetDecFlags(value);
    sr.SetAux((value & 0x000F) == 0);
    
    return 0;
}

// Code: INR R
// Operation: (r) + 1 → r
// Description: Increment register
// Flags: S,Z,AC,P
uint8_t i8080::INRR ()
{
    uint16_t value = *readdst();
    return INR(value);
}

// Code: INR M
// Operation: [(HL)] + 1 → [(HL)]
// Description: Increment memory
// Flags: S,Z,AC,P
uint8_t i8080::INRM ()
{
    uint16_t value = read();
    write(++value);
    
    sr.SetDecFlags(value);
    sr.SetAux((value & 0x000F) == 0x0000);
    
    return 0;
}

// Code: DCR r
// Operation: (r) – 1 → r
// Description: Decrement register
// Flags: S,Z,AC,P
uint8_t i8080::DCR (uint16_t value)
{
    *readdst() = --value & 0x00FF;
    
    sr.SetDecFlags(value);
    sr.SetAux((value & 0x000F) != 0x000F);
    
    return 0;
}

// Code: DCR r
// Operation: (r) – 1 → r
// Description: Decrement register
// Flags: S,Z,AC,P
uint8_t i8080::DCRR ()
{
    uint16_t value = *readdst();
    return DCR(value);
}

// Code: DCR M
// Operation: [(HL)] - 1 → [(HL)]
// Description: Decrement memory
// Flags: S,Z,AC,P
uint8_t i8080::DCRM ()
{
    uint16_t value = read();
    write(--value);
    
    sr.SetDecFlags(value);
    sr.SetAux((value & 0x000F) != 0x000F);
    
    return 0;
}

// Code: INX RP
// Operation: (RP) + 1 → r
// Description: Increment registry pair
// Flags: -
uint8_t i8080::INX  ()
{
    mutatepair((opcode & 0x30) >> 4, [](uint16_t & pair) { pair++; });
    return 0;
}

// Code: INX SP
// Operation: (RP) + 1 → r
// Description: Increment registry pair
// Flags: -
uint8_t i8080::INXSP  ()
{
    sp++;
    return 0;
}

// Code: DCX RP
// Operation: (RP) - 1 → r
// Description: Decrement registry pair
// Flags: -
uint8_t i8080::DCX  ()
{
    mutatepair((opcode & 0x30) >> 4, [](uint16_t & pair) { pair--; });
    return 0;
}

// Code: DCX SP
// Operation: (RP) - 1 → r
// Description: Decrement SP
// Flags: -
uint8_t i8080::DCXSP  ()
{
    sp--;
    return 0;
}

#pragma mark -
#pragma mark Add

uint8_t i8080::ADD(uint8_t value, uint8_t carry)
{
    uint16_t acc = reg[A];
    uint16_t tmp = acc + value + carry;
    reg[A] = tmp & 0x00FF;
    
    sr.SetDecFlags(tmp);
    
    uint16_t hc = tmp ^ acc ^ value;

    sr.SetAux   ((bool) (hc & (1 << 4)));
    sr.SetCarry ((bool) (hc & (1 << 8))); // Not usual
    
    return 0;
}

uint8_t i8080::ADC(uint8_t data)
{
    auto carry = sr.GetCarry();
    return ADD (data, carry);
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
    return ADDM();
}

// Code: ACI D8
// Operation: (A) + D8 + C → A
// Description: Add immediate to A with carry
// Flags: S,Z,AC,P,C
uint8_t i8080::ACI  ()
{
    return ADCM();
}

// Code: DAD rp
// Operation: (HL) + (RP) → HL
// Description: Add part to H & L
// Flags: C
uint8_t i8080::DAD  (uint16_t value)
{
    uint32_t hl  = readpair(HL);
    uint32_t tmp = (uint32_t) value + hl;
    writepair(HL, tmp & 0xFFFF);
    
    sr.SetCarry((bool)(tmp & 0x10000L));
    
    return 0;
}

// Code: DAD rp
// Operation: (HL) + (RP) → HL
// Description: Add part to H & L
// Flags: C
uint8_t i8080::DAD  ()
{
    uint16_t rpdata = readpair((opcode & 0x30) >> 4);
    return DAD(rpdata);
}

// Code: DAD SP
// Operation: (HL) + (SP) → HL
// Description: Add part to H & L
// Flags: C
uint8_t i8080::DADSP  ()
{
    return DAD(sp);
}

#pragma mark -
#pragma mark Substract

uint8_t i8080::SUB(uint8_t data, uint8_t carry)
{
    ADD(~data, !carry);
    sr.InvertCarry();
    
    return 0;
}

uint8_t i8080::SBB(uint8_t data)
{
    auto carry = sr.GetCarry();
    return SUB (data, carry);
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
    return SUBM();
}

// Code: DBI D8
// Operation: (A) - D8 - C → A
// Description: Substract immediate from A with borrow
// Flags: S,Z,AC,P,C
uint8_t i8080::SBI  ()
{
    return SBBM ();
}

#pragma mark -
#pragma mark Logical

uint8_t i8080::ANA  (uint8_t data)
{
    sr.SetAux(((reg[A] | data) & 0x08) != 0);
    
    reg[A] &= data;
    
    sr.SetDecFlags (reg[A]);
    sr.SetCarry    (false);
    
    return 0;
}

uint8_t i8080::XRA  (uint8_t data)
{
    reg[A] ^= data;
    
    sr.SetDecFlags (reg[A]);
    sr.SetCarry    (false);
    sr.SetAux      (false);
    
    return 0;
}

uint8_t i8080::ORA  (uint8_t data)
{
    reg[A] |= data;
    
    sr.SetDecFlags (reg[A]);
    sr.SetCarry    (false);
    sr.SetAux      (false);
    
    return 0;
}

uint8_t i8080::CMP (uint8_t value)
{
    uint16_t acc = reg[A];
    uint16_t tmp = acc - value;
    
    sr.SetAllFlags(tmp);
    sr.SetAux((bool)(~(acc ^ tmp ^ value) & 0x10));
    
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
    auto value = read();
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

// Code: ANI 
// Operation: (A) & D8 → A
// Description: And immediate with A
// Flags: S,Z,AC=*,P,C=0
uint8_t i8080::ANI  ()
{
    auto value = read();
    return ANA(value);
}

// Code: XRI
// Operation: (A) ^ D8 → A
// Description: Exclusive or immediate with A
// Flags: S,Z,AC=0,P,C=0
uint8_t i8080::XRI  ()
{
    uint8_t value = read();
    return XRA(value);
}

// Code: ORI
// Operation: (A) | D8 → A
// Description: Or immediate with A
// Flags: S,Z,AC=0,P,C=0
uint8_t i8080::ORI  ()
{
    uint8_t value = read();
    return ORA(value);
}

// Code: CPI
// Operation: Compare
// Description: Compare immediate with A
// Flags: S,Z,AC,P,C
uint8_t i8080::CPI  ()
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
uint8_t i8080::RLC  ()
{
    uint8_t carry = (reg[A] & 0x80) >> 7;
    reg[A] = (reg[A] << 1) | carry;
    
    sr.SetCarry((bool) carry);
    
    return 0;
}

// Code: RRC
// Operation: A7 → A0, A0 → C
// Description: Rotate A right
// Flags: C
uint8_t i8080::RRC  ()
{
    uint8_t carry = reg[A] & 0x01;
    reg[A] = (reg[A] >> 1) | (carry << 7);
    
    sr.SetCarry((bool) carry);
    
    return 0;
}

// Code: RAL
// Operation: A7 → C, C → A0
// Description: Rotate A left through carry
// Flags: C
uint8_t i8080::RAL  ()
{
    uint8_t carry = (reg[A] & 0x80) >> 7;
    reg[A] = (reg[A] << 1) | sr.GetCarry();
    
    sr.SetCarry((bool) carry);
    
    return 0;
}

// Code: RAL
// Operation: A7 → C, C → A0
// Description: Rotate A left through carry
// Flags: C
uint8_t i8080::RAR  ()
{
    uint8_t carry = reg[A] & 0x01;
    reg[A] = (reg[A] >> 1) | (sr.GetCarry() << 7);
    
    sr.SetCarry((bool) carry);
    
    return 0;
}

#pragma mark -
#pragma mark Special

// Code: CMA
// Operation: ~(A)
// Description: Complement A
// Flags: -
uint8_t i8080::CMA  ()
{
    reg[A] = ~reg[A];
    return 0;
}

// Code: STC
// Operation: C = 1
// Description: Set carry
// Flags: C
uint8_t i8080::STC  ()
{
    sr.SetCarry(true);
    return 0;
}

// Code: CMC
// Operation: ~(C)
// Description: Complement carry
// Flags: C
uint8_t i8080::CMC  ()
{
    sr.InvertCarry();
    return 0;
}

// Code: DAA
// Description: Decimal adjust A
// Flags: S,Z,AC,P,C
uint8_t i8080::DAA  ()
{
    uint8_t acc = reg[A];
    uint8_t add = 0x00;
    uint8_t crr = 0x00;
    
    if (sr.GetAux() || (acc & 0x0F) > 0x09)
    {
        add = 0x06;
    }

    if (sr.GetCarry()
        ||  (acc >> 4) >  0x09
        || ((acc >> 4) >= 0x09 && (acc & 0x0F) > 0x09))
    {
        add |= 0x60;
        crr  = 0x01;
    }
    
    ADD(add);
    sr.SetCarry((bool) crr);
    
    return 0;
}

#pragma mark -
#pragma mark I/O

// Code: IN
// Operation: Input
// Flags: -
uint8_t i8080::IN   ()
{
    return (reg[A] = 0x00);
}

// Code: OUT
// Operation: Output
// Flags: -
uint8_t i8080::OUT  ()
{
    
#ifdef LOGTEST
    if (bus -> read(pc) == 0x00)
    {
        std::cout << std::endl;
        exit(0);

        return 0;
    }

    if (reg[C] == 0x09)
    {
        for (uint16_t i = readpair(DE); bus -> read(i) != '$'; i += 1) {
            std::cout << bus -> read(i);
        }
    }

    if (reg[C] == 0x02) {
        std::cout << reg[E];
    }
#endif
    
    return 0;
}

#pragma mark -
#pragma mark Control

// Code: EI
// Operation: Enable interrup
// Flags: INTE
uint8_t i8080::EI   ()
{
    return 0;
}

// Code: DI
// Operation: Disable interrup
// Flags: DI
uint8_t i8080::DI   ()
{
    return 0;
}

// Code: HLT
// Operation: Halt
uint8_t i8080::HLT  ()
{
    return 0;
}

// Code: NOP
// Operation: No-operation
uint8_t i8080::NOP()
{
    return 0;
}
