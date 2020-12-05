/*
 * This file is part of the Orion-128 distribution (https://github.com/temaweb/orion-128).
 * Copyright (c) 2020 Artem Okonechnikov.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 3.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef Color16Colorizer_hpp
#define Color16Colorizer_hpp

#include "Colorizer.hpp"
#include "Color16Palette.hpp"

class Color16Colorizer : public Colorizer
{
public:
    Color16Colorizer(std::shared_ptr<const VideoBuffer> buffer);
    
    virtual std::shared_ptr<Palette> getPalette(uint16_t address) const override;
};

#endif /* Color16Colorizer_hpp */
