//
//  i8080.hpp
//  orion
//
//  Created by Артём Оконечников on 29.10.2020.
//

#ifndef i8080_hpp
#define i8080_hpp

#include <cstdint>
#include <string>
#include <vector>

#include "Status.hpp"
#include "IODevice.hpp"
#include "IO.hpp"

class Cpu
{
public:
    
    Cpu();
    ~Cpu() { };
    
private:
    
    uint8_t  registers[8];       // Registers
    uint8_t * regpairs[3];       // Pairs
    
    uint8_t  opcode  = 0x00;     // Operation code
    uint8_t  cycles  = 0x00;     // Cycle counter

    uint16_t stack   = 0x0000;   // Stack pointer
    uint16_t counter = 0x0000;   // Program counter
    
    uint16_t address = 0x0000;   // Current memory pointer
    uint64_t ticks   = 0x0L;     // Clock counter
    
    Status status;               // Status register

    friend void log(uint16_t pcl, Cpu * cpu);
    
private:
    
    enum
    {
        B, //  0x00 - B
        C, //  0x01 - C
        D, //  0x02 - D
        E, //  0x03 - E
        H, //  0x04 - H
        L, //  0x05 - L
        M, //  0x06 - M - Memory (Not use)
        A  //  0x07 - A - Accumulator
    };
    
    enum
    {
        BC, //  0x00 - B & C
        DE, //  0x01 - D & E
        HL, //  0x02 - H & L
    };
    
    uint8_t * readsrc();
    uint8_t * readdst();
    
    uint16_t readpair (uint8_t index);
    void writepair    (uint8_t index, uint16_t data);
    void mutatepair   (uint8_t index, std::function<void(uint16_t &)> mutator);
    
// Communication
private:
    
    std::shared_ptr<IO<uint16_t>> bus = std::make_shared<DefaultIO<uint16_t>>();
    std::shared_ptr<IO<uint8_t>>  io  = std::make_shared<DefaultIO<uint8_t>>();
    
    uint8_t read ();
    uint8_t read (uint16_t address);
    
    void write (uint8_t  data);
    void write (uint16_t address, uint8_t data);
    
private:
    
    void IMP(); // Implied
    void IMM(); // Immediate D8/D16
    void IND(); // Indirect
    void DIR(); // Direct
    void HLM(); // Direct HL
    
private:
    
    // Move, Load, Store
    
    uint8_t MOVRR ();
    uint8_t MOVMR ();
    uint8_t MOVRM ();
    uint8_t MVIR  ();
    uint8_t MVIM  ();
    uint8_t LXI   ();
    uint8_t LXISP ();
    uint8_t STAX  ();
    uint8_t LDAX  ();
    uint8_t STA   ();
    uint8_t LDA   ();
    uint8_t SHLD  ();
    uint8_t LHLD  ();
    uint8_t XCHG  ();
    
    
    // Stack operations
    
    uint8_t PUSHR ();
    uint8_t PUSH  ();
    uint8_t PUSH  (uint8_t hi, uint8_t lo);
    uint8_t POPR  ();
    uint8_t POP   ();
    uint8_t POP   (uint8_t & hi, uint8_t & lo);
    uint8_t XTHL  ();
    uint8_t SPHL  ();

    // Jump
    
    uint8_t JMP  ();
    uint8_t JMP  (uint8_t flag);
    uint8_t JMPN (uint8_t flag);
    uint8_t JC   ();
    uint8_t JNC  ();
    uint8_t JZ   ();
    uint8_t JNZ  ();
    uint8_t JP   ();
    uint8_t JM   ();
    uint8_t JPE  ();
    uint8_t JPO  ();
    uint8_t PCHL ();
    
    // Call
    
    uint8_t CALL ();
    uint8_t CALL (uint8_t flag);
    uint8_t CALN (uint8_t flag);
    
    uint8_t CC   ();
    uint8_t CNC  ();
    uint8_t CZ   ();
    uint8_t CNZ  ();
    uint8_t CP   ();
    uint8_t CM   ();
    uint8_t CPE  ();
    uint8_t CPO  ();
    
    // Return
    
    uint8_t RET  (uint8_t flag);
    uint8_t RETN (uint8_t flag);
    
    uint8_t RET  ();
    uint8_t RC   ();
    uint8_t RNC  ();
    uint8_t RZ   ();
    uint8_t RNZ  ();
    uint8_t RP   ();
    uint8_t RM   ();
    uint8_t RPE  ();
    uint8_t RPO  ();
    
    // Restart
    
    uint8_t RST  ();
    
    // Increment and decrement
    
    uint8_t INR  (uint16_t value);
    uint8_t INRR ();
    uint8_t INRM ();
    uint8_t DCR  (uint16_t value);
    uint8_t DCRR ();
    uint8_t DCRM ();
    uint8_t INX  ();
    uint8_t INXSP();
    uint8_t DCX  ();
    uint8_t DCXSP();
    
    // Add
    
    uint8_t ADD  (uint8_t value, uint8_t carry = 0x00);
    uint8_t ADC  (uint8_t value);
    
    uint8_t ADDR ();
    uint8_t ADDM ();
    uint8_t ADCR ();
    uint8_t ADCM ();
    uint8_t ADI  ();
    uint8_t ACI  ();
    uint8_t DAD  (uint16_t value);
    uint8_t DAD  ();
    uint8_t DADSP();
    
    // Substract
    
    uint8_t SUB  (uint8_t value, uint8_t carry = 0x00);
    uint8_t SBB  (uint8_t value);
    
    uint8_t SUBR ();
    uint8_t SUBM ();
    uint8_t SBBR ();
    uint8_t SBBM ();
    uint8_t SUI  ();
    uint8_t SBI  ();
    
    // Logical
    
    uint8_t ANA  (uint8_t value);
    uint8_t XRA  (uint8_t value);
    uint8_t ORA  (uint8_t value);
    uint8_t CMP  (uint8_t value);
    
    uint8_t ANAR ();
    uint8_t XRAR ();
    uint8_t ORAR ();
    uint8_t CMPR ();
    uint8_t ANAM ();
    uint8_t XRAM ();
    uint8_t ORAM ();
    uint8_t CMPM ();
    uint8_t ANI  ();
    uint8_t XRI  ();
    uint8_t ORI  ();
    uint8_t CPI  ();
    
    // Rotate
    
    uint8_t RLC  ();
    uint8_t RRC  ();
    uint8_t RAL  ();
    uint8_t RAR  ();
    
    // Special
    
    uint8_t CMA  ();
    uint8_t STC  ();
    uint8_t CMC  ();
    uint8_t DAA  ();
    
    // I/O
    
    uint8_t IN   ();
    uint8_t OUT  ();
    
    // Control
    
    uint8_t EI   ();
    uint8_t DI   ();
    uint8_t NOP  ();
    uint8_t HLT  ();

private:
    
    struct Command
    {
        // Operation name
        std::string name;
        
        // Operation cycles
        uint8_t cycles = 0x00;
        
        uint8_t (Cpu::*operate) (void) = nullptr;
        void    (Cpu::*addrmod) (void) = nullptr;
    };

    std::vector<Command> lookup;
    
public:
    
    void clock();
    void reset();

    void setCounter(uint16_t counter);
    
    void connect (std::shared_ptr<IO<uint16_t>> bus);
    void connect (std::shared_ptr<IO<uint8_t>>  io);
};

void log(uint16_t pcl, Cpu * cpu);

#endif /* i8080_hpp */
