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

#include "IOStorage.hpp"

std::shared_ptr<IODevice> IOStorage::defaultDevice() const
{
    return DefaultDevice::getInstance();
}

void IOStorage::insertR(std::shared_ptr<RDevice> device)
{
    insert(rdevices, device);
}

void IOStorage::insertW(std::shared_ptr<WDevice> device)
{
    insert(wdevices, device);
}

void IOStorage::insertRW(std::shared_ptr<IODevice> device)
{
    insertR(std::static_pointer_cast<RDevice>(device));
    insertW(std::static_pointer_cast<WDevice>(device));
}

std::shared_ptr<RDevice> IOStorage::getRDevice(uint16_t address) const
{
    return getDevice(address, rdevices);
}

std::shared_ptr<WDevice> IOStorage::getWDevice(uint16_t address) const
{
    return getDevice(address, wdevices);
}
