//
//  IOCpu.hpp
//  orion
//
//  Created by Артём Оконечников on 25.11.2020.
//

#ifndef IOCpu_hpp
#define IOCpu_hpp

#include <stdio.h>
#include <iostream>

class IO
{
public:
    virtual uint8_t read(const uint16_t address) const = 0;
    virtual void write(const uint16_t address, uint8_t data) = 0;
};

class DefaultIO : public IO
{
private:
    
private:
    DefaultIO () {}
    DefaultIO (const DefaultIO &);
    DefaultIO& operator=(DefaultIO &);
    
public:
    
    static std::shared_ptr<DefaultIO> & getInstance()
    {
        static std::shared_ptr<DefaultIO> instance;
        return instance;
    }
    
    virtual uint8_t read(const uint16_t address) const override
    {
        return 0x00;
    }
    
    virtual void write(const uint16_t address, uint8_t data) override
    { }
};

#endif /* IOCpu_hpp */
