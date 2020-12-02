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

#include "Loop.hpp"

void Loop::run ()
{
    int ticks = 0;
    
    while (isRunning)
    {
        ticks++;
        cpu -> clock();
        
        if (ticks < lookup)
            continue;
        
        broadcast(ticks);
        ticks = 0;
    }
}

void Loop::hold()
{
    isRunning = false;
}

void Loop::insert(const std::shared_ptr<Event> & event)
{
    auto limit = event -> getLimit();
    
    if (lookup == 0 || lookup > limit)
        lookup = limit;

    broadcast += event;
}
