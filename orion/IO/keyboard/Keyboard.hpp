//
//  Keyboard.hpp
//  orion
//
//  Created by Артём Оконечников on 15.11.2020.
//

#ifndef Keyboard_hpp
#define Keyboard_hpp

#include <stdio.h>
#include <Carbon/Carbon.h>

#include "IODevice.hpp"
#include "Bus.hpp"

class Keyboard : public IODevice
{
private:
    
    uint8_t key  = 0x00;
    uint8_t mask = 0x00;
    
    uint8_t keys[8];
    
    static const short None = -1;
    
    const short matrix[8][8] =
    {
        { kVK_Home,   kVK_ANSI_KeypadClear, kVK_Escape,         kVK_F1,               kVK_F2,             kVK_F3,                kVK_F4,          kVK_F5         },
        { kVK_Tab ,   None,                 kVK_Return,         kVK_Delete,           kVK_LeftArrow,      kVK_UpArrow,           kVK_RightArrow,  kVK_DownArrow  },
        { kVK_ANSI_0, kVK_ANSI_1,           kVK_ANSI_2,         kVK_ANSI_3,           kVK_ANSI_4,         kVK_ANSI_5,            kVK_ANSI_6,      kVK_ANSI_7     },
        { kVK_ANSI_8, kVK_ANSI_9,           None,               kVK_ANSI_Semicolon,   kVK_ANSI_Comma,     kVK_ANSI_Minus,        kVK_ANSI_Period, kVK_ANSI_Slash },
        { None,       kVK_ANSI_A,           kVK_ANSI_B,         kVK_ANSI_C,           kVK_ANSI_D,         kVK_ANSI_E,            kVK_ANSI_F,      kVK_ANSI_G     },
        { kVK_ANSI_H, kVK_ANSI_I,           kVK_ANSI_J,         kVK_ANSI_K,           kVK_ANSI_L,         kVK_ANSI_M,            kVK_ANSI_N,      kVK_ANSI_O     },
        { kVK_ANSI_P, kVK_ANSI_Q,           kVK_ANSI_R,         kVK_ANSI_S,           kVK_ANSI_T,         kVK_ANSI_U,            kVK_ANSI_V,      kVK_ANSI_W     },
        { kVK_ANSI_X, kVK_ANSI_Y,           kVK_ANSI_Z,         kVK_ANSI_LeftBracket, kVK_ANSI_Backslash, kVK_ANSI_RightBracket, None,            kVK_Space      }
    };
    
public:
    Keyboard();
    
    // Address belong to ports space
    virtual bool isAccept(uint16_t address) const override;
    
    // I/O
    virtual uint8_t read (const uint16_t address) const override;
    virtual void   write (const uint16_t address, uint8_t data) override;
    
public:
    void keyevent(unsigned short code, bool isPressed);
};

#endif /* Keyboard_hpp */
