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

#include <thread>
#include <functional>

#include "Cpuloop.hpp"

Cpuloop::Cpuloop(int frequency, std::shared_ptr<Cpu> cpu) : frequency(frequency), cpu(cpu)
{
    add(cpuloop,   &Cpuloop::estimateDelay);
    add(frequency, &Cpuloop::estimateFrequency);
}

void Cpuloop::run ()
{
    int counter = 0;
    
    while (isRunning)
    {
        counter++;
        cpu -> clock();
        
        if (counter != lookup)
            continue;
        
        for (auto & event : events) {
            event -> lookup(counter);
        }
        
        counter = 0;
    }
}

void Cpuloop::hold()
{
    isRunning = false;
}

void Cpuloop::estimateDelay(double elapsed, int ticks)
{
    auto expected = (1.0 / frequency) * ticks;
    
    if (elapsed >= expected)
        return;
        
    double sleep = expected - elapsed;
    
    // If previos iteration thread was sleep more that need
    // then current sleep time substract from this oversleep
    if ((oversleep -= sleep) >= 0)
        return;
    
    this -> delay();
}

void Cpuloop::delay()
{
    auto sleep = std::abs(oversleep);
    auto start = steady_clock::now();

    // Sleep current thread for overrun remainder
    std::this_thread::sleep_for(
       duration<double>(sleep)
    );

    // Count overrun if thread sleep more that need
    auto delay = Event::timepassed(start);
    if (delay > sleep)
    {
        oversleep = delay - sleep;
    }
}

void Cpuloop::estimateFrequency (double elapsed, int ticks)
{
    currFreq = ticks / elapsed;
}

double Cpuloop::getFrequency() const
{
    return currFreq;
}

void Cpuloop::add (int ticks, void (Cpuloop::*event)(double, int))
{
    add(ticks, [=] (double elapsed, int ticks) {
        (this->*event)(elapsed, ticks);
    });
}

void Cpuloop::add(int ticks, Event::action command)
{
    if (lookup == 0 || lookup > ticks)
        lookup = ticks;
    
    auto event = std::make_unique<Event>(ticks, command);
    events.push_back(std::move(event));
}
