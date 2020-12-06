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

#ifndef DelayEvent_hpp
#define DelayEvent_hpp

#define ORION_DELAY_CYCLES 10000

#include "Event.hpp"

class DelayEvent : public Event
{
private:
    double oversleep = 0.0;
    int frequency = 0;

    void delay();
    
public:
    DelayEvent(int frequency) : frequency(frequency)
    { }
    
    virtual int getLimit() override;
    virtual void execute(double elapsed, int ticks) override;
};

#endif /* DelayEvent_hpp */
