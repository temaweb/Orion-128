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

#ifndef IOBus_hpp
#define IOBus_hpp

#include "IO.hpp"
#include "IODevice.hpp"
#include "IOStorage.hpp"

class IOBus : public IOStorage, public IODevice, public IO<uint16_t>
{
private:
    
    template<class T>
    // Alias for return device function like as getWDevice or getRDevice
    using factory = std::function<std::shared_ptr<T>(const IOBus &, uint16_t)>;
    
    template<class T, class D>
    // Alias for device operation like as read or write
    using operation = std::function<T(std::shared_ptr<D>, uint16_t)>;
    
private:
    
    // Execute read/write device action with address
    // in device local space
    //
    // Example:
    //
    // If device space is 0x0A00 - 0x0AFF and incoming address is 0x0A0F
    // then device funciton will be call with 0x000F
    template<class T, class D>
    T localCall (uint16_t address, factory<D> getDevice, operation<T, D> operation) const
    {
        auto device = getDevice(*this, address);
        auto space  = device -> getSpace();
        
        // Return local adress
        auto direct = space.getDirect(address);
        
        // Execute device read/write operation
        return operation(device, direct);
    }
    
public:
    
    virtual uint8_t read(uint16_t address) const override;
    virtual void write(uint16_t address, uint8_t data) override;
};

#endif /* IOBus_hpp */
