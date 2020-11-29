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

#ifndef Cpuloop_hpp
#define Cpuloop_hpp

#include <chrono>
#include <vector>
#include <functional>

#include "Cpu.hpp"
#include "Event.hpp"

class Cpuloop
{
private:
    
    // Estimate cpu delay after @cpuloop cycles
    static const int cpuloop = 10000;

    int    frequency     = 0;
    double oversleep     = 0.0;
    double loopFrequency = 0.0;
    
    volatile bool isRunning = true;
    
    std::shared_ptr<Cpu> cpu;
    std::vector<std::unique_ptr<Event>> events;

    void delay ();
    void estimateDelay     (double elapsed, int ticks);
    void estimateFrequency (double elapsed, int ticks);
    
    void add (int ticks, void (Cpuloop::*event)(double, int));
    
public:
    Cpuloop(int frequency, std::shared_ptr<Cpu> cpu);
    
    double getFrequency() const;
    
    void run ();
    void hold ();
    
    void add (int ticks, Event::action event);
};

#endif /* Cpuloop_hpp */
