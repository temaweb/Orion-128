//
//  Video.hpp
//  orion
//
//  Created by Артём Оконечников on 11.11.2020.
//

#ifndef Video_hpp
#define Video_hpp

#include <array>
#include <shared_mutex>

#include "VideoRam.hpp"
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
    
    typedef std::array<std::array<Pixel, width>, height> frame;
    typedef std::array<Pixel, width> line;
    
    static const BWPalette bwpalette;
    
    enum ColorMode
    {
        MONO    = 0,  // B/W color
        BLANK   = 1,  // No image
        COLOR4  = 2,  // 4 color palette
        COLOR16 = 3   // 16 color palettex
    }
    colorMode;
    
    VideoRam::buffer frameBuffer {};
    VideoRam::buffer colorBuffer {};
    
    mutable std::shared_mutex _mutex;
    
private:
    std::shared_ptr<const VideoRam> memory = nullptr;

    line getLine(uint8_t row) const;
    
    void colorisebw (line & line, size_t size, uint8_t data) const;
    void colorise16 (line & line, size_t size, uint8_t data, uint16_t address) const;
    void colorise   (line & line, size_t size, uint8_t data, const Palette & palette) const;
    
public:
    
    // Return one frame with resolution 384 x 256 pixels
    // Each pixel has b/w color in RGB hex-format.
    std::array<std::array<Pixel, width>, height> output() const;

    // Connect memory bus
    void connect(std::shared_ptr<const VideoRam> memory);

    void updateBuffers ();
    void setColorMode  (uint8_t mode);
    
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
