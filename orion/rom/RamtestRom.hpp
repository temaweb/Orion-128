//
//  TestRom.hpp
//  orion
//
//  Created by Артём Оконечников on 14.11.2020.
//

#ifndef TestRom_hpp
#define TestRom_hpp

#include <stdio.h>
#include "Rom.hpp"

class RamtestRom : public Rom
{
protected:
    
    virtual std::string getRom() override
    {
        return "RAM_TEST.BIN";
    }
};

#endif /* TestRom_hpp */
