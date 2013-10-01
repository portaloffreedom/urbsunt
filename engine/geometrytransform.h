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

#ifndef GEOMETRYTRANSFORM_H
#define GEOMETRYTRANSFORM_H

#include "math.h"
#include "matrixstack.h"

namespace sm {

    class GeometryTransform
    {
    public:
        GeometryTransform();

        void setModelViewMatrixStack(MatrixStack& mModelView);
        void setProjectionMatrixStack(MatrixStack& mProjection);
        void setMatrixStacks(MatrixStack& mModelView, MatrixStack& mProjection);

        const Matrix44& getModelViewProjectionMatrix();
        const Matrix44& getModelViewMatrix();
        const Matrix44& getProjectionMatrix();

        MatrixStack* getModelViewStack();
        MatrixStack *getProjectionStack();

        const Matrix33& getNormalMatrix(bool bNormalize = false);

    protected:
        Matrix44       mModelViewProjection;
        Matrix33       mNormalMatrix;

        MatrixStack* mModelView;
        MatrixStack* mProjection;
        
        bool status_modified;
    };
}

#endif // GEOMETRYTRANSFORM_H