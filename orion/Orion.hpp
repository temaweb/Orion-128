//
//  Orion.hpp
//  orion
//
//  Created by Артём Оконечников on 14.11.2020.
//

#ifndef Orion_hpp
#define Orion_hpp

#include <stdio.h>

#include "i8080.hpp"
#include "Bus.hpp"
#include "Video.hpp"

class Orion
{
public:
    Orion() {}
    
    // Run main loop at 2.5 MHz
    void Run(int frequency = 2500000);
};

#endif /* Orion_hpp */
