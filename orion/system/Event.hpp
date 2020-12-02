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

#ifndef Event_hpp
#define Event_hpp

#include <chrono>
#include <functional>

using namespace std::chrono;

class Event
{
private:
    using time = steady_clock::time_point;
    time start = steady_clock::now();
    
    int ticks = 0;
    void call ();

protected:
    static double timepassed(time start);
    
public:
    virtual ~Event() = default;
    
    void lookup (short counter);
    
    virtual int getLimit() = 0;
    virtual void execute(double elapsed, int ticks) = 0;
};

#endif /* Event_hpp */
