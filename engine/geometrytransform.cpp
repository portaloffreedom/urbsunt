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

#include "geometrytransform.h"
using namespace sm;

GeometryTransform::GeometryTransform()
{
    status_modified = true;
}

void GeometryTransform::setModelViewMatrixStack(MatrixStack& mModelView)
{
    this->mModelView = &mModelView;
    status_modified = true;
}

void GeometryTransform::setProjectionMatrixStack(MatrixStack& mProjection)
{
    this->mProjection = &mProjection;
    status_modified = true;
}

void GeometryTransform::setMatrixStacks(MatrixStack& mModelView, MatrixStack& mProjection)
{
    this->setModelViewMatrixStack(mModelView);
    this->setProjectionMatrixStack(mProjection);
}

const Matrix44& GeometryTransform::getModelViewProjectionMatrix()
{
    if (status_modified) {
        mModelViewProjection = mProjection->getMatrix() * mModelView->getMatrix();
        status_modified = false;
    }
    return mModelViewProjection;
}

const Matrix44& GeometryTransform::getModelViewMatrix()
{
    return mModelView->getMatrix();
}
const Matrix44& GeometryTransform::getProjectionMatrix()
{
    return mProjection->getMatrix();
}

MatrixStack* GeometryTransform::getModelViewStack()
{
    return mModelView;
}
MatrixStack* GeometryTransform::getProjectionStack()
{
    return mProjection;
}

const Matrix33& GeometryTransform::getNormalMatrix(bool bNormalize)
{
    if (status_modified) {
        mNormalMatrix = this->getModelViewMatrix().extractRotationMatrix();

        if(bNormalize)
            mNormalMatrix.normalize();

        status_modified = false;
    }

    return mNormalMatrix;
}
