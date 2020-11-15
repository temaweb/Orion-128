//
//  Rom.hpp
//  orion
//
//  Created by Артём Оконечников on 14.11.2020.
//

#ifndef Rom_hpp
#define Rom_hpp

#include <stdio.h>
#include <fstream>

#include "Bus.hpp"

class Rom
{
private:
    
    // ROM files directory
    static const std::string dir;
    
    // Orion ROM borders
    static const uint16_t begin = 0xF800;
    static const uint16_t end   = 0xFFFF;
    
    std::ifstream open();
    
protected:
    
    // Returns ROM file from dir specified
    virtual std::string getRom() = 0;
    
public:
    
    virtual void load(std::shared_ptr<Bus> bus);
    
    // Returns memoty offset where ROM loaded
    virtual uint16_t getOffset() const
    {
        return begin;
    }
};

#endif /* Rom_hpp */
