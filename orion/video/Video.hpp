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

class Memory;

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
    
    enum Palette
    {
        MONO    = 0,  // B/W color
        BLANK   = 1,  // No image
        COLOR4  = 2,  // 4 color palette
        COLOR16 = 3   // 16 color palette
    };
    
    uint32_t color16[16] =
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
    
    Palette palette = MONO;
    
private:
    std::shared_ptr<const Memory> bus = nullptr;

    std::vector<Pixel> getLine(uint8_t row);
    
    void colorisebw (std::vector<Pixel> & line, const uint8_t & data);
    void colorise16 (std::vector<Pixel> & line, const uint8_t & data, const uint16_t & address);
    
public:
    
    // Return one frame with resolution 384 x 256 pixels
    // Each pixel has b/w color in RGB hex-format.
    std::vector<std::vector<Pixel>> output();
    
    // Connect memory bus
    void connect(std::shared_ptr<const Memory> bus);
    
    // Set current color palette
    void setPalette(uint8_t data);
    
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
