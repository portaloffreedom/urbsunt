/*
    Example of the OpenGL usage with SDL2
    Copyright (C) 2012  Matteo De Carlo <<matteo.dek@gmail.com>>

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/

#ifndef RENDERENGINE_H
#define RENDERENGINE_H

#include "matrixstack.h"
#include "geometrytransform.h"
#include "math/frustum.h"

namespace sm {

    //TODO Fps count
    
class RenderEngine
{
public:
    RenderEngine();
    void resizeScene(int width, int hight);
    void drawScene(float elapsed);

private:
    void initGL();
    
    MatrixStack modelViewMatix;
    MatrixStack projectionMatrix;
    GeometryTransform transformPipeline;
    Frustum viewFrustum;
};

}

#endif // RENDERENGINE_H
