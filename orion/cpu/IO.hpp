//
//  IOCpu.hpp
//  orion
//
//  Created by Артём Оконечников on 25.11.2020.
//

#ifndef IO_hpp
#define IO_hpp

#include <stdio.h>
#include <iostream>

template<class T>
class IO
{
public:
    virtual uint8_t read(const T address) const = 0;
    virtual void write(const T address, uint8_t data) = 0;
};

template<class T>
class DefaultIO : public IO<T>
{
public:
    virtual uint8_t read(const T address) const override final
    {
        return 0x00;
    }
    
    virtual void write(const T address, uint8_t data) override final
    {
        printf("%04X %02X$\n", address, data);
    }
};

#endif /* IO_hpp */
