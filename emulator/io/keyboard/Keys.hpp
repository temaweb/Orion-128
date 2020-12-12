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

#ifndef Keys_h
#define Keys_h

enum Keys
{
    Home      = 0x01000010,
    Clear     = 0x0100000B,
    Escape    = 0x01000000,
    Tab       = 0x01000001,
    Return    = 0x01000004,
    Backspace = 0x01000003,
    
    Left      = 0x01000012,
    Up        = 0x01000013,
    Right     = 0x01000014,
    Down      = 0x01000015,
    
    Shift     = 0x01000020,
    Control   = 0x01000021,
    Alt       = 0x01000023,
    
    F1        = 0x01000030,
    F2        = 0x01000031,
    F3        = 0x01000032,
    F4        = 0x01000033,
    F5        = 0x01000034,
    F6        = 0x01000035,
    
    K0        = 0x00000030,
    K1        = 0x00000031,
    K2        = 0x00000032,
    K3        = 0x00000033,
    K4        = 0x00000034,
    K5        = 0x00000035,
    K6        = 0x00000036,
    K7        = 0x00000037,
    K8        = 0x00000038,
    K9        = 0x00000039,
    
    
    Colon     = 0x0000003A,
    Semicolon = 0x0000003B,
    
    Comma     = 0x0000002C,
    Minus     = 0x0000002D,
    Period    = 0x0000002E,
    Slash     = 0x0000002F,
    
    At        = 0x00000040,
    
    A         = 0x00000041,
    B         = 0x00000042,
    C         = 0x00000043,
    D         = 0x00000044,
    E         = 0x00000045,
    F         = 0x00000046,
    G         = 0x00000047,
    H         = 0x00000048,
    I         = 0x00000049,
    J         = 0x0000004A,
    K         = 0x0000004B,
    L         = 0x0000004C,
    M         = 0x0000004D,
    N         = 0x0000004E,
    O         = 0x0000004F,
    P         = 0x00000050,
    Q         = 0x00000051,
    R         = 0x00000052,
    S         = 0x00000053,
    T         = 0x00000054,
    U         = 0x00000055,
    V         = 0x00000056,
    W         = 0x00000057,
    X         = 0x00000058,
    Y         = 0x00000059,
    Z         = 0x0000005A,
    
    BLeft     = 0x0000005B,
    BSlash    = 0x0000005C,
    BRight    = 0x0000005D,
    Circum    = 0x0000005E,
    Space     = 0x00000020
};

#endif /* Keys_h */
