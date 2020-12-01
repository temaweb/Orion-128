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

#include "Orion.hpp"

#include "IOSplitter.hpp"

#include "Disk.hpp"
#include "System.hpp"
#include "MonitorRom.hpp"

#include "PageSelector.hpp"
#include "PaletteSelector.hpp"
#include "ScreenSelector.hpp"

Orion::Orion()
{
    auto memory = std::make_shared<Memory>();

    auto iobus = std::make_shared<IOBus>();
    auto iospl = std::make_shared<IOSplitter> (iobus);
    
    iobus -> insertR  <MonitorRom> ();
    iobus -> insertRW <System>();
    iobus -> insertRW (memory);
    iobus -> insertRW (keyboard);
    
    iobus -> insertRW <Disk>();
    
    iobus -> insertW  <PageSelector>    (memory);
    iobus -> insertW  <PaletteSelector> (video);
    iobus -> insertW  <ScreenSelector>  (video);
    
    video -> connect(memory);

    cpu   -> connect(iobus);
    cpu   -> connect(iospl);

    filesystem = std::make_unique<Filesystem>(memory);
}

double Orion::getFrequency() const
{
    return loop -> getFrequency();
}

std::shared_ptr<Video> Orion::getVideo() const
{
    return video;
}

void Orion::run(int frequency)
{
    loop = std::make_unique<Cpuloop>(frequency, cpu);
    
    loop -> add(ORION_FRAME_FREQUENCY, [this](double, int) {
        video -> createFrame();
    });
    
    loop -> run();
}

void Orion::stop()
{
    loop -> hold();
}

void Orion::keyevent(unsigned short code, bool isPressed)
{
    keyboard -> keyevent(code, isPressed);
}

void Orion::createFile(std::string path)
{
    filesystem -> create(path);
}


