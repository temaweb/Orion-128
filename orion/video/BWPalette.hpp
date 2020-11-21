//
//  BWPalette.hpp
//  orion
//
//  Created by Артём Оконечников on 21.11.2020.
//

#ifndef BWPalette_hpp
#define BWPalette_hpp

#include "Palette.hpp"

class BWPalette : public Palette
{
private:
    
    static const uint32_t black = 0x000000;
    static const uint32_t white = 0xFFFFFF;
    
public:
    
    Pixel getBackground() const override
    {
        return Pixel(black);
    }
    
    Pixel getForeground() const override
    {
        return Pixel(white);
    }
};

#endif /* BWPalette_hpp */
