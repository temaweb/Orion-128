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

#ifndef FreqEvent_hpp
#define FreqEvent_hpp

#include "Orion.hpp"
#include "Event.hpp"

class FreqEvent : public Event
{
private:
    int frequency = 0;
    int & actual;
    
public:
    FreqEvent(int frequency, int & actual) : frequency(frequency), actual(actual)
    { }
    
    virtual int getLimit() override;
    virtual void execute(double elapsed, int ticks) override;
};

#endif /* FreqEvent_hpp */
