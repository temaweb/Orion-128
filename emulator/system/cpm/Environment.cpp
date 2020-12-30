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

#include <iostream>
#include "Environment.hpp"

std::ifstream Environment::openBinaryResource(std::string path)
{
#ifdef TARGET_OS_MAC
    CFStringRef pathStr = toString(path);
    path = createResourcePath(pathStr);
#endif

    return openBinaryFile(path);
}

std::ifstream Environment::openBinaryFile(std::string path)
{
    return std::ifstream(path, std::ios::in | std::ios::binary);
}

#ifdef TARGET_OS_MAC

std::string Environment::createResourcePath(CFStringRef path)
{
    auto bundle = CFBundleGetMainBundle();
    auto url    = CFBundleCopyResourceURL(bundle, path, nullptr, nullptr);
    auto file   = CFURLCopyPath(url);
    
    return toString(file);
}

CFStringRef Environment::toString(std::string string)
{
    auto cstring = string.c_str();
    return CFStringCreateWithCString(nullptr, cstring, encoding);
}

std::string Environment::toString(CFStringRef string)
{
    auto cstring = CFStringGetCStringPtr(string, encoding);
    return std::string(cstring);
}

#endif
