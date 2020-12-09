//
//  Filesystem.hpp
//  orion
//
//  Created by Артём Оконечников on 21.11.2020.
//

#ifndef Filesystem_hpp
#define Filesystem_hpp

#include <vector>
#include "Memory.hpp"

class Filesystem
{
private:
    std::shared_ptr<Memory> memory;
    std::vector<uint8_t> read(std::string path);
    
public:
    Filesystem(std::shared_ptr<Memory> memory) : memory(memory)
    {}
    
    void create (std::string path);
};

#endif /* Filesystem_hpp */
