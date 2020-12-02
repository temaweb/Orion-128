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

#ifndef FrameEvent_hpp
#define FrameEvent_hpp

#include "Event.hpp"
#include "Video.hpp"

#define ORION_FRAME_CYCLES 5000

class FrameEvent : public Event
{
private:
    std::shared_ptr<Video> video;
    
public:
    FrameEvent(std::shared_ptr<Video> video) : video(video)
    { }
    
    virtual int getLimit() override;
    virtual void execute(double elapsed, int ticks) override;
};

#endif /* FrameEvent_hpp */
