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

#include "frustum.h"
#include <cmath>

using namespace sm;
Frustum::Frustum()
{
}

void Frustum::init()
{
    this->setOrthographic(-1.0f, 1.0f, -1.0f, 1.0f, -1.0f, 1.0f);
}

void Frustum::setPerspective(smReal fFov, smReal fAspect, smReal fNear, smReal fFar)
{
    smReal xmin, xmax, ymin, ymax;       // Dimensions of near clipping plane
    smReal xFmin, xFmax, yFmin, yFmax;   // Dimensions of far clipping plane

    // Do the Math for the near clipping plane
    ymax = fNear * float(tan( fFov * sm::PI / 360.0 ));
    ymin = -ymax;
    xmin = ymin * fAspect;
    xmax = -xmin;

    // Construct the projection matrix
    projMatrix.loadIdentity();
    projMatrix[0] = (2.0f * fNear)/(xmax - xmin);
    projMatrix[5] = (2.0f * fNear)/(ymax - ymin);
    projMatrix[8] = (xmax + xmin) / (xmax - xmin);
    projMatrix[9] = (ymax + ymin) / (ymax - ymin);
    projMatrix[10] = -((fFar + fNear)/(fFar - fNear));
    projMatrix[11] = -1.0f;
    projMatrix[14] = -((2.0f * fFar * fNear)/(fFar - fNear));
    projMatrix[15] = 0.0f;

    // Do the Math for the far clipping plane
    yFmax = fFar * float(std::tan(fFov * sm::PI / 360.0));
    yFmin = -yFmax;
    xFmin = yFmin * fAspect;
    xFmax = -xFmin;


    // Fill in values for untransformed Frustum corners
    // Near Upper Left
    nearUL[0] = xmin;
    nearUL[1] = ymax;
    nearUL[2] = -fNear;
    nearUL[3] = 1.0f;

    // Near Lower Left
    nearLL[0] = xmin;
    nearLL[1] = ymin;
    nearLL[2] = -fNear;
    nearLL[3] = 1.0f;

    // Near Upper Right
    nearUR[0] = xmax;
    nearUR[1] = ymax;
    nearUR[2] = -fNear;
    nearUR[3] = 1.0f;

    // Near Lower Right
    nearLR[0] = xmax;
    nearLR[1] = ymin;
    nearLR[2] = -fNear;
    nearLR[3] = 1.0f;

    // Far Upper Left
    farUL[0] = xFmin;
    farUL[1] = yFmax;
    farUL[2] = -fFar;
    farUL[3] = 1.0f;

    // Far Lower Left
    farLL[0] = xFmin;
    farLL[1] = yFmin;
    farLL[2] = -fFar;
    farLL[3] = 1.0f;

    // Far Upper Right
    farUR[0] = xFmax;
    farUR[1] = yFmax;
    farUR[2] = -fFar;
    farUR[3] = 1.0f;

    // Far Lower Right
    farLR[0] = xFmax;
    farLR[1] = yFmin;
    farLR[2] = -fFar;
    farLR[3] = 1.0f;
}

void Frustum::setOrthographic(smReal xMin, smReal xMax, smReal yMin, smReal yMax, smReal zMin, smReal zMax)
{
    projMatrix.loadOrthographicMatrix(xMin, xMax, yMin, yMax, zMin, zMax);
    projMatrix[15] = 1.0f;


    // Fill in values for untransformed Frustum corners
    // Near Upper Left
    nearUL[0] = xMin;
    nearUL[1] = yMax;
    nearUL[2] = zMin;
    nearUL[3] = 1.0f;

    // Near Lower Left
    nearLL[0] = xMin;
    nearLL[1] = yMin;
    nearLL[2] = zMin;
    nearLL[3] = 1.0f;

    // Near Upper Right
    nearUR[0] = xMax;
    nearUR[1] = yMax;
    nearUR[2] = zMin;
    nearUR[3] = 1.0f;

    // Near Lower Right
    nearLR[0] = xMax;
    nearLR[1] = yMin;
    nearLR[2] = zMin;
    nearLR[3] = 1.0f;

    // Far Upper Left
    farUL[0] = xMin;
    farUL[1] = yMax;
    farUL[2] = zMax;
    farUL[3] = 1.0f;

    // Far Lower Left
    farLL[0] = xMin;
    farLL[1] = yMin;
    farLL[2] = zMax;
    farLL[3] = 1.0f;

    // Far Upper Right
    farUR[0] = xMax;
    farUR[1] = yMax;
    farUR[2] = zMax;
    farUR[3] = 1.0f;

    // Far Lower Right
    farLR[0] = xMax;
    farLR[1] = yMin;
    farLR[2] = zMax;
    farLR[3] = 1.0f;
}
