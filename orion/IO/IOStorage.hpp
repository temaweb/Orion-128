//
//  IOStorage.hpp
//  Orion
//
//  Created by Артём Оконечников on 01.12.2020.
//

#ifndef IOStorage_hpp
#define IOStorage_hpp

#include <map>

#include "DefaultDevice.hpp"

template<class T, class D>
class IOStorage 
{
private:
    std::map<AddressSpace, std::shared_ptr<T>> map;
    
public:
    const std::shared_ptr<T> & getDevice(uint16_t address) const
    {
        for (auto const & [space, device] : map)
        {
            if (address < space.from)
                continue;

            if (address <= space.to)
                return device;
        }

        return DefaultDevice::getInstance<T>();
    }

    void insert(std::shared_ptr<T> device)
    {
        auto decorator = std::make_shared<D>(device);
        map.emplace(device -> getSpace(), decorator);
    }
};

#endif /* IOStorage_hpp */
