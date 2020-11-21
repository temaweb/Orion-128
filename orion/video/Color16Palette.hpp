//
//  Color16Palette.hpp
//  orion
//
//  Created by Артём Оконечников on 21.11.2020.
//

#ifndef Color16Palette_hpp
#define Color16Palette_hpp

#include "Palette.hpp"

class Color16Palette : public Palette
{
private:
    
    // Orion memory format color for
    // background and foreground
    //
    // High 4 bits - background color
    // Low  4 bits - foregroubd color
    uint8_t color = 0x0000;
    
    
    // Orion 16 color palette
    constexpr static uint32_t palette[16] =
    {
        0x000000, // Black
        0x0000FF, // Blue
        0x008000, // Green
        0x30D5C8, // Turquoise
        0xFF0000, // Red
        0xC400AB, // Magenta
        0x964B00, // Brown
        0xD3D3D3, // Light gray
        0x000000, // Black
        0x00BFFF, // Light blue
        0x99ff99, // Light green
        0x24F2EF, // Light turquoise
        0xFFCBDB, // Pink
        0xD95CC9, // Light magenta
        0xFFFF00, // Yellow
        0xFFFFFF  // White
    };

private:
    
    Pixel getPixel(uint8_t code) const
    {
        auto color = palette[code];
        return Pixel(color);
    }
    
public:
    
    Color16Palette(uint8_t color) : color(color)
    { }
    
    Pixel getBackground() const override
    {
        return getPixel((color & 0xF0) >> 4);
    }
    
    Pixel getForeground() const override
    {
        return getPixel(color & 0x0F);
    }
};

#endif /* Color16Palette_hpp */
