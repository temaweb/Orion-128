//
//  Pixel.hpp
//  orion
//
//  Created by Артём Оконечников on 19.11.2020.
//

#ifndef Pixel_h
#define Pixel_h

struct Pixel
{
    const uint32_t color;

    Pixel() : Pixel(0x000000)
    { }
    
    Pixel(uint32_t color) : color(color)
    { }
    
    Pixel(const Pixel & pixel) : Pixel(pixel.color)
    { }
    
    float getRed() const
    {
        return (float) ((color & 0xFF0000) >> 16) / 255.0;
    }
    
    float getGreen() const
    {
        return (float) ((color & 0x00FF00) >> 8) / 255.0;
    }
    
    float getBlue() const
    {
        return (float) (color & 0x0000FF) / 255.0;
    }
    
    Pixel& operator=(const Pixel & pixel)
    {
        return *new(this) Pixel(pixel);
    }
};

#endif /* Pixel_h */
