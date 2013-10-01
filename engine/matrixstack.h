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

#ifndef MATRIXSTACK_H
#define MATRIXSTACK_H

#include "math/math.h"
#include "GL/glew.h"
#include "camera.h"


namespace sm {

class MatrixStack
{
public:
    MatrixStack(int stackDepth = 256);
    ~MatrixStack();

    void PushMatrix();
    void PopMatrix();

    void loadIdentity();
    void loadMatrix(const Matrix44 &matrix);
    inline void LoadCameraMatrix(Camera& frame) {
        loadMatrix(frame.getCameraMatrix());
        }
    MatrixStack& operator*=(const Matrix44 &matrix);

    void scale(const sm::Vector3 vScale);
    void translate(const Vector3);
    void rotate(GLfloat rad, Vector3 vAxis);

    const Matrix44& getMatrix() const { return pStack[stackPointer]; }
    void getMatrix(Matrix44 mMatrix) { mMatrix.copyFrom(pStack[stackPointer]); }    

private:
    int     stackDepth;
    int     stackPointer;
    Matrix44    *pStack;
};

}

#endif // MATRIXSTACK_H
