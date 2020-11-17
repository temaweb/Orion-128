//
//  OrionRom.hpp
//  orion
//
//  Created by Артём Оконечников on 14.11.2020.
//

#ifndef OrionRom_hpp
#define OrionRom_hpp

#include <stdio.h>
#include "Rom.hpp"

class MonitorRom : public Rom
{
protected:
    
    virtual std::string getRom() override
    {
        return "Orion128_M2.rom";
    }
};

#endif /* OrionRom_hpp */
