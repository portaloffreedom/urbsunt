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

#ifndef FRUSTUM_H
#define FRUSTUM_H

#include <GL/glew.h>
#include "math.h"

namespace sm {
    class Frustum
    {
    public:
        explicit Frustum();
        void init();

        const Matrix44& GetProjectionMatrix() { return projMatrix; }
        void setOrthographic(smReal xMin, smReal xMax, smReal yMin, smReal yMax, smReal zMin, smReal zMax);
        void setPerspective(smReal fFov, smReal fAspect, smReal fNear, smReal fFar);

    private:
        // The projection matrix for this frustum
        Matrix44 projMatrix;

        // Untransformed corners of the frustum
        Vector4  nearUL, nearLL, nearUR, nearLR;
        Vector4  farUL,  farLL,  farUR,  farLR;

        // Transformed corners of Frustum
        Vector4  nearULT, nearLLT, nearURT, nearLRT;
        Vector4  farULT,  farLLT,  farURT,  farLRT;

        // Base and Transformed plane equations
        Vector4 nearPlane, farPlane, leftPlane, rightPlane;
        Vector4 topPlane, bottomPlane;
    };
}

#endif // FRUSTUM_H
