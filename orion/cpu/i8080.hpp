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
    
    uint8_t a = 0x00;       // Accumulator
    
    uint8_t reg[6];         // B C D E H L
    
    uint16_t sp = 0x0000;   // Stack pointer
    uint16_t pc = 0x0000;   // Program counter
  
    uint8_t  sr = 0x00;     // Status register
    
    uint8_t  op     = 0x00; // Operation code
    uint8_t  cycles = 0x00; // Cycle counter

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
    
    uint8_t XXX();
    uint8_t NOP();
    
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
    
    uint8_t PUSH  ();   // PSW
    
    uint8_t POPB  ();
    uint8_t POPD  ();
    uint8_t POPH  ();
    
    uint8_t POP   ();   // PSW
    
    uint8_t XTHL  ();
    uint8_t SPHL  ();
    
    uint8_t LXI   ();  // SP
    uint8_t INX   ();  // SP
    uint8_t DCX   ();  // SP
    
    // Jump
    
    
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
