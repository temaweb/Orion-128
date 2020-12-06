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

#ifndef GenericRenderer_hpp
#define GenericRenderer_hpp

#include "Renderer.hpp"

template<class T>
class GenericRenderer : public Renderer
{
private:
    std::shared_ptr<T> palette = std::make_shared<T>();
    
public:
    virtual std::shared_ptr<Palette> getPalette(Buffer *, uint16_t) const override
    {
        return palette;
    }
};

#endif /* GenericRenderer_hpp */
