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

#include "camera.h"

using namespace sm;

Matrix44 Camera::getCameraMatrixRotationOnly()
{
    Vector3 x, z;
    Matrix44 m;

    // Make rotation matrix
    // Z vector is reversed
    z[0] = -vForward[0];
    z[1] = -vForward[1];
    z[2] = -vForward[2];

    // X vector = Y cross Z
    x = vUp.crossProduct(z);

    // Matrix has no translation information and is
    // transposed.... (rows instead of columns)
#define M(row,col)  m[col*4+row]
    M(0, 0) = x[0];
    M(0, 1) = x[1];
    M(0, 2) = x[2];
    M(0, 3) = 0.0;
    M(1, 0) = vUp[0];
    M(1, 1) = vUp[1];
    M(1, 2) = vUp[2];
    M(1, 3) = 0.0;
    M(2, 0) = z[0];
    M(2, 1) = z[1];
    M(2, 2) = z[2];
    M(2, 3) = 0.0;
    M(3, 0) = 0.0;
    M(3, 1) = 0.0;
    M(3, 2) = 0.0;
    M(3, 3) = 1.0;
#undef M

    return m;
}

Matrix44 Camera::getCameraMatrix()
{
    Matrix44 m = this->getCameraMatrixRotationOnly();

    // Apply translation too
    Matrix44 trans;
    //TODO MMath::TranslationMatrix44(trans, -vOrigin[0], -vOrigin[1], -vOrigin[2]);
    trans.loadTranslationMatrix(-vPosition);

    return m * trans;
}
