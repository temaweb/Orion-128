//
//  Pixel.hpp
//  orion
//
//  Created by Артём Оконечников on 19.11.2020.
//

#ifndef Pixel_h
#define Pixel_h

class Pixel
{
private:
    uint32_t color = 0x000000;
    
public:

    Pixel(uint32_t color) : color(color) {  }
    
    float getRed() {
        return (float) ((color & 0xFF0000) >> 16) / 255.0;
    }
    
    float getGreen() {
        return (float) ((color & 0x00FF00) >> 8) / 255.0;
    }
    
    float getBlue() {
        return (float) (color & 0x0000FF) / 255.0;
    }
};

#endif /* Pixel_h */
