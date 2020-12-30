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

#ifndef DefaultDevice_hpp
#define DefaultDevice_hpp

#include "IODevice.hpp"

class DefaultDevice final : public IODevice
{
private:
    DefaultDevice() = default;
    static const uint8_t value = 0x00;
    
public:
    DefaultDevice  (const DefaultDevice &) = delete;
    void operator= (const DefaultDevice &) = delete;
    
    template<typename T>
    static const std::shared_ptr<T> & getInstance()
    {
        static const std::shared_ptr<T> instance(new DefaultDevice);
        return instance;
    }
    
public:
    virtual uint8_t read(uint16_t) const override;
    virtual void write(uint16_t, uint8_t) override;
};

#endif /* DefaultDevice_hpp */
