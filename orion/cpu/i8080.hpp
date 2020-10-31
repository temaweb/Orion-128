//
//  i8080.hpp
//  orion
//
//  Created by Артём Оконечников on 29.10.2020.
//

#ifndef i8080_hpp
#define i8080_hpp

#include <stdio.h>
#include <cstdint>
#include <string>
#include <vector>

class Bus;

class i8080
{
public:
    
    i8080();
    ~i8080() { };
    
private:
    
    uint8_t  reg[6];            // Registers        (B C D E H L)
    
    uint8_t  a       = 0x00;    // Accumulator      (A)
    uint8_t  sr      = 0x00;    // Status register  (S Z - AC - P - C)
    
    uint8_t  op      = 0x00;    // Operation code
    uint8_t  cycles  = 0x00;    // Cycle counter

    
    uint16_t sp      = 0x0000;  // Stack pointer
    uint16_t pc      = 0x0000;  // Program counter
    
    uint16_t address = 0x0000;
    
private:
    
    enum
    {
        B,
        C,
        D,
        E,
        H,
        L,
        M, // Memory
        A  // Accumulator
    };
    
    enum
    {
        SSS = 0x07,
        DDD = 0x38
    };
    
    enum Flags
    {
        Sign    = (1 << 7), // S
        Zero    = (1 << 6), // Z
        Aux     = (1 << 4), // AC
        Parity  = (1 << 2), // P
        Carry   = (1 << 0)  // C
    };
    
// Bus communication
private:
    
    Bus * bus = nullptr;
    
    uint8_t read(uint16_t address);
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
    uint8_t LXIB  ();
    uint8_t LXID  ();
    uint8_t LXIH  ();
    uint8_t STAXB ();
    uint8_t STAXD ();
    uint8_t LDAXB ();
    uint8_t LDAXD ();
    uint8_t STA   ();
    uint8_t LDA   ();
    uint8_t SHLD  ();
    uint8_t LHLD  ();
    uint8_t XCHG  ();
    
    
    // Stack operations
    
    uint8_t PUSHB ();
    uint8_t PUSHD ();
    uint8_t PUSHH ();
    uint8_t PUSH  ();  // PSW
    uint8_t POPB  ();
    uint8_t POPD  ();
    uint8_t POPH  ();
    uint8_t POP   ();  // PSW
    uint8_t XTHL  ();
    uint8_t SPHL  ();
    uint8_t LXI   ();  // SP
    uint8_t INX   ();  // SP
    uint8_t DCX   ();  // SP

    // Jump
    
    uint8_t JMP  ();
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
    uint8_t CC   ();
    uint8_t CNC  ();
    uint8_t CZ   ();
    uint8_t CNZ  ();
    uint8_t CP   ();
    uint8_t CM   ();
    uint8_t CPE  ();
    uint8_t CPO  ();
    
    // Return
    
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
    
    uint8_t INRR ();
    uint8_t INRM ();
    uint8_t DCRR ();
    uint8_t DCRM ();
    uint8_t INXB ();
    uint8_t INXD ();
    uint8_t INXH ();
    uint8_t DCXB ();
    uint8_t DCXD ();
    uint8_t DCXH ();
    
    // Add
    
    uint8_t ADDR ();
    uint8_t ADDM ();
    uint8_t ADCR ();
    uint8_t ADCM ();
    uint8_t ADI  ();
    uint8_t ACI  ();
    uint8_t DADB ();
    uint8_t DADD ();
    uint8_t DADH ();
    uint8_t DAD  ();
    
    // Substract
    
    uint8_t SUBR ();
    uint8_t SUBM ();
    uint8_t SBBR ();
    uint8_t SBBM ();
    uint8_t SUI  ();
    uint8_t SBI  ();
    
    // Logical
    
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
    uint8_t XXX  ();
    
private:
    
    struct Command
    {
        std::string name;
        uint8_t cycles = 0x00;
        
        uint8_t (i8080::*operate) (void) = nullptr;
        void    (i8080::*addrmod) (void) = nullptr;
    };

    std::vector<Command> lookup;
    
public:
    
    void clock();
    void connect(Bus * bus);
};

#endif /* i8080_hpp */
