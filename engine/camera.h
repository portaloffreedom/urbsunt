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

#ifndef SMCAMERA_H
#define SMCAMERA_H

#include "math/math.h"

//TODO angle
//TODO frustum

namespace sm {

/**
 * @brief Class implementing the abstraction to manage a virtual camera into
 * the 3D space
 * 
 * Note that all calculation are made in "getCameraMatrix" or "getMatrix" functions
 * 
 * TODO general usage description
 * 
 */
class Camera
{
private:
    Vector3 vPosition; // Where am I?
    Vector3 vForward;  // Where am I going?
    Vector3 vUp;       // Which way is up?
    
public:
    /**
     * @brief internal values set to default
     * 
     * Position set to (0,0,0)
     * View angle set to (0,0,0)
     * frustum set to Ortogonal
     * TODO bla bla bla...
     * 
     */
    Camera();
    
    /**
     * @brief set the position of the camera to "vector"
     * 
     * Note that no calculation are made here, this function only changes the
     * internal status
     * 
     */
    void setPosition(const Vector3 &vector) {
        this->vPosition = vector;
    }
    
    /**
     * @brief gets the actual position of the camera
     * 
     * @return SmVector3 the position of the camera
     */
    Vector3 getPosition() {
        return vPosition;
    }
    
    Matrix44 getCameraMatrix();
    Matrix44 getCameraMatrixRotationOnly();
    
};

}

#endif // SMCAMERA_H
