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

#include <cstddef>
#include "GraphicsContext.hpp"

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated"

void GraphicsContext::initialize()
{
    glDisable(GL_CULL_FACE);
    glDisable(GL_DEPTH_TEST);
    
    glGenBuffers(1, &vertexBuffer);
    glGenBuffers(1, &colorBuffer);
}

void GraphicsContext::initializeLayout(GLdouble width, GLdouble height)
{
    glClearColor(0, 0, 0, 0);
    glClear (GL_COLOR_BUFFER_BIT);

    glMatrixMode (GL_MODELVIEW);
    glPushMatrix ();
    
    glOrtho(0, width, 0, height, -1.0, 1.0);
}

void GraphicsContext::flush()
{
    glPopMatrix ();
    glFlush ();
}

void GraphicsContext::flushBuffers(float * pixels, float * colors, uint16_t size)
{
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(*pixels) * size, pixels, GL_STATIC_DRAW);
    glVertexPointer(3, GL_FLOAT, 0, NULL);
    
    glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(*colors) * size, colors, GL_STATIC_DRAW);
    
    glEnableClientState(GL_COLOR_ARRAY);
    glColorPointer(3, GL_FLOAT, 0, NULL);
    
    glEnableClientState(GL_VERTEX_ARRAY);
    glDrawArrays(GL_QUADS, 0, size / 2);
}

#pragma clang diagnostic pop
