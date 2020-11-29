//
//  Eventloop.cpp
//  Orion
//
//  Created by Артём Оконечников on 29.11.2020.
//

#include "Cpuloop.hpp"

#include <thread>
#include <functional>

using namespace std::chrono;

Cpuloop::Cpuloop(int frequency, std::shared_ptr<Cpu> cpu) : frequency(frequency), cpu(cpu)
{
    addevent(std::make_shared<Event<Cpuloop>>(10000,     &Cpuloop::delay, *this));
    addevent(std::make_shared<Event<Cpuloop>>(frequency, &Cpuloop::rate,  *this));
}

void Cpuloop::run ()
{
    while (isRunning)
    {
        cpu -> clock();
        
        for (auto & event : events) {
            event -> lookup();
        }
    }
}

void Cpuloop::hold()
{
    isRunning = false;
}

void Cpuloop::rate (double elapsed, int limit)
{
    frequency = limit / elapsed;
}

void Cpuloop::delay(double elapsed, int limit)
{
    auto expected = (1.0 / frequency) * limit;
    
    if (elapsed >= expected)
        return;
        
    double sleep = expected - elapsed;
    
    // If previos iteration thread was sleep more that need
    // then current sleep time substract from this oversleep
    if ((oversleep -= sleep) >= 0)
        return;
    
    this -> sleep();
}

void Cpuloop::sleep()
{
    auto sleep = std::abs(oversleep);
    auto start = steady_clock::now();

    // Sleep current thread for overrun remainder
    std::this_thread::sleep_for(
       duration<double>(sleep)
    );

    // Count overrun if thread sleep more that need
    auto delay = timepassed(start);
    if (delay > sleep)
    {
        oversleep = delay - sleep;
    }
}

double Cpuloop::getFrequency() const
{
    return freqrate;
}

double Cpuloop::timepassed(timepoint start)
{
    duration<double> elapsed = steady_clock::now() - start;
    return elapsed.count();
}

void Cpuloop::addevent(std::shared_ptr<Command> callback)
{
    events.push_back(callback);
}
