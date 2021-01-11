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

#ifndef Environment_hpp
#define Environment_hpp

#ifdef __APPLE__
    #include <TargetConditionals.h>

    #ifdef TARGET_OS_MAC
        #include <CoreFoundation/CFBundle.h>
    #endif
#endif

#include <string>
#include <fstream>
#include <functional>

class Environment
{
public:
    using bufftype = std::ifstream::char_type;
    
public:
    static void readBinaryResource(std::string path, std::ifstream::char_type * begin);
    static void readBinaryFile(std::string path, std::vector<uint8_t> & vector);

private:
    static const std::ios_base::openmode defaultMode = std::ios::in | std::ios::binary | std::ios::ate;
    
    static std::ifstream openBinaryResource(std::string path);
    static std::ifstream openBinaryFile(std::string path, std::ios_base::openmode mode = defaultMode);
    
#ifdef TARGET_OS_MAC
    
private:
    static const CFStringBuiltInEncodings encoding = kCFStringEncodingUTF8;
    static std::string createResourcePath(CFStringRef path);
    
    static CFStringRef toString(std::string string);
    static std::string toString(CFStringRef string);
    
#endif
};

#endif /* Environment_hpp */
