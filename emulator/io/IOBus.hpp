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

#ifndef IOBus_hpp
#define IOBus_hpp

#include <map>

#include "IO.hpp"
#include "IODevice.hpp"
#include "IOStorage.hpp"

class IOBus : public IODevice, public IO<uint16_t>
{
private:
    std::unique_ptr<IORStorage> rstorage;
    std::unique_ptr<IOWStorage> wstorage;
    
public:
    IOBus();
    
    virtual uint8_t read(uint16_t address) const override;
    virtual void write(uint16_t address, uint8_t data) override;

    void insertR  (const std::shared_ptr<RDevice>  & device);
    void insertW  (const std::shared_ptr<WDevice>  & device);
    void insertRW (const std::shared_ptr<IODevice> & device);
    
public:
    
    template<class T, class ...Args>
    void createR (Args&& ...args)
    {
        insertR(std::make_shared<T>(std::forward<Args>(args)...));
    }
    
    template<class T, class ...Args>
    void createW (Args&& ...args)
    {
        insertW(std::make_shared<T>(std::forward<Args>(args)...));
    }
    
    template<class T, class ...Args>
    void createRW (Args&& ...args)
    {
        insertRW(std::make_shared<T>(std::forward<Args>(args)...));
    }
};

#endif /* IOBus_hpp */
