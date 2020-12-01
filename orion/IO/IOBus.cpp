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

#include "IOBus.hpp"

IOBus::IOBus()
{
    rstorage = std::make_unique<IORStorage>();
    wstorage = std::make_unique<IOWStorage>();
}

uint8_t IOBus::read(uint16_t address) const
{
    return rstorage -> read(address);
}

void IOBus::write(uint16_t address, uint8_t data)
{
    return wstorage -> write(address, data);
}

void IOBus::insertR(std::shared_ptr<RDevice> device)
{
    rstorage -> addDevice(device);
}

void IOBus::insertW(std::shared_ptr<WDevice> device)
{
    wstorage -> addDevice(device);
}

void IOBus::insertRW(std::shared_ptr<IODevice> device)
{
    insertR(std::static_pointer_cast<RDevice>(device));
    insertW(std::static_pointer_cast<WDevice>(device));
}
