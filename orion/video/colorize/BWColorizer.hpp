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

#ifndef BWColorizer_hpp
#define BWColorizer_hpp

#include "Colorizer.hpp"
#include "BWPalette.hpp"

class BWColorizer : public Colorizer
{
private:
    std::shared_ptr<Palette> bwpalette = std::make_shared<BWPalette>();
    
public:
    BWColorizer(std::shared_ptr<const VideoBuffer> buffer);
    
    virtual std::shared_ptr<Palette> getPalette(uint16_t) const override;
};

#endif /* BWColorizer_hpp */
