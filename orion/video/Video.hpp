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
#include <array>
#include <shared_mutex>

#include "Memory.hpp"
#include "Palette.hpp"
#include "BWPalette.hpp"
#include "Color16Palette.hpp"

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
    
    typedef std::array<std::array<Pixel, width>, height> frame;
    typedef std::array<Pixel, width> line;
    
    std::array<uint16_t, 12 * 1024> frameBuffer;
    std::array<uint16_t, 12 * 1024> colorBuffer;
    
    static const BWPalette bwpalette;
    mutable std::shared_mutex _mutex;
    
    bool _isChanged = true;
    
    enum ColorMode
    {
        MONO    = 0,  // B/W color
        BLANK   = 1,  // No image
        COLOR4  = 2,  // 4 color palette
        COLOR16 = 3   // 16 color palettex
    };

    ColorMode colorMode = MONO;
    
private:
    std::shared_ptr<const Memory> memory = nullptr;

    line getLine(uint8_t row) const;
    
    void colorisebw (line & line, size_t size, uint8_t data) const;
    void colorise16 (line & line, size_t size, uint8_t data, uint16_t address) const;
    void colorise   (line & line, size_t size, uint8_t data, const Palette & palette) const;
    
public:
    
    // Return one frame with resolution 384 x 256 pixels
    // Each pixel has b/w color in RGB hex-format.
    std::array<std::array<Pixel, width>, height> output() const;
    
    void createFrame();
    
    // Connect memory bus
    void connect(std::shared_ptr<const Memory> bus);
    
    // Set current color palette
    void switchColorMode(uint8_t data);
    
    // Set current color palette
    void switchScreenMode(uint8_t data);
    
    void markChanged();
    bool isChanged();
    
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
