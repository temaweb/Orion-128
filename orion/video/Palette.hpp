//
//  Palette.hpp
//  orion
//
//  Created by Артём Оконечников on 19.11.2020.
//

#ifndef Palette_h
#define Palette_h

#include <cstdint>
#include "Pixel.hpp"

class Palette
{
public:
    
    virtual Pixel getBackground() const = 0;
    virtual Pixel getForeground() const = 0;
};

#endif /* Palette_h */
