//
//  Video.hpp
//  orion
//
//  Created by Артём Оконечников on 11.11.2020.
//

#ifndef Video_hpp
#define Video_hpp

#include <stdio.h>
#include <vector>

class Bus;

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

struct Resolution
{
    const int width;
    const int height;
};

class Video
{
private:
    
    static const int width  = 384;         // H points
    static const int height = 256;         // V points

    static const uint16_t begin = 0x0C000; // Start vidio memory
    static const uint16_t end   = 0x0EFFF; // End video memory
    
private:
    std::shared_ptr<const Bus> bus = nullptr;

    std::vector<Pixel> getLine(uint8_t row);
    void explore(std::vector<Pixel> & line, uint8_t data);
    
public:
    
    // Return one frame with resolution 384 x 256 pixels
    // Each pixel has b/w color in RGB hex-format.
    std::vector<std::vector<Pixel>> output();
    
    // Connect memory bus
    void connect(std::shared_ptr<const Bus> bus);
    
    // Return video resolution
    Resolution getResolution() const
    {
        return
        {
            width,
            height
        };
    }
};

#endif /* Video_hpp */
