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

#ifndef GraphicsContext_hpp
#define GraphicsContext_hpp

#include <OpenGL/gl.h>

class GraphicsContext
{
private:
    GLuint vertexBuffer;
    GLuint colorBuffer;

public:
    void initialize();
    void initializeLayout(GLdouble width, GLdouble height);
    
    void flush();
    void flushBuffers (float * pixels, float * colors, uint16_t size);
    void bindBuffer   (GLuint & vbo,   float * buffer, uint16_t size);
};

#endif /* GraphicsContext_hpp */
