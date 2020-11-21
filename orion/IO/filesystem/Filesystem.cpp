//
//  Filesystem.cpp
//  orion
//
//  Created by Артём Оконечников on 21.11.2020.
//

#include "Filesystem.hpp"

#include <fstream>
#include <vector>
#include <cstdint>

void Filesystem::create(std::string path)
{
    auto file = std::ifstream(path, std::ios::in | std::ios::binary);
    char buffer = 0x00;
    
    std::vector<uint8_t> mem;
    while (!file.eof())
    {
        file.read(&buffer, sizeof(buffer));
        mem.push_back(buffer);
    }
    
    file.close();

    for (int i = 0; i < mem.size(); i++)
    {
        memory -> writeB(i, mem[i]);
    }
}
