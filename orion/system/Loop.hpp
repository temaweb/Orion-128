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

#ifndef Loop_hpp
#define Loop_hpp

#include "Cpu.hpp"
#include "Event.hpp"
#include "Broadcast.hpp"

class Loop
{
private:
    int lookup  = 0;
    
    volatile bool isRunning = true;
    
    std::shared_ptr<Cpu> cpu;
    Broadcast broadcast;
    
    void insert (const std::shared_ptr<Event> & event);
    
public:
    Loop(std::shared_ptr<Cpu> cpu) : cpu(cpu)
    { }

    void run ();
    void hold ();

    template<class T, class ...Args>
    void create (Args&& ...args)
    {
        insert(std::make_shared<T>(std::forward<Args>(args)...));
    }
};

#endif /* Loop_hpp */
