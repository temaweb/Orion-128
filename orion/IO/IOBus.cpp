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

#include <map>
#include "IOBus.hpp"

uint8_t IOBus::read(uint16_t address) const
{
    const auto & device = getDevice<RDevice>(address, rdevices);
    auto space  = device -> getSpace();
    
    // Return local adress
    auto direct = space.getDirect(address);
    
    // Execute device read/write operation
    return device -> read(direct);
}

void IOBus::write(uint16_t address, uint8_t data)
{
    const auto & device = getDevice<WDevice>(address, wdevices);
    auto space  = device -> getSpace();

    // Return local adress
    auto direct = space.getDirect(address);

    // Execute device read/write operation
    return device -> write(direct, data);
}

void IOBus::insertR(std::shared_ptr<RDevice> device)
{
    insert(rdevices, device);
}

void IOBus::insertW(std::shared_ptr<WDevice> device)
{
    insert(wdevices, device);
}

void IOBus::insertRW(std::shared_ptr<IODevice> device)
{
    insertR(std::static_pointer_cast<RDevice>(device));
    insertW(std::static_pointer_cast<WDevice>(device));
}
