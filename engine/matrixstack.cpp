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

#include "matrixstack.h"
#include "errorhandling.h"
#include <cstring>  //per memcpy
#include <sstream>

using namespace sm;

MatrixStack::MatrixStack(int stackDepth)
{
    if (stackDepth <= 0) {
        std::stringstream message;
        message<<"matrix stack dimensions could not be "<<stackDepth<<
               ". Setting default to 256";
        emitError(message.str());
        stackDepth = 256;
    }

    this->stackDepth = stackDepth;
    this->stackPointer = 0;
    this->pStack = new Matrix44[stackDepth];
    pStack[0].loadIdentity();
}

MatrixStack::~MatrixStack()
{
    delete [] pStack;
}

void MatrixStack::PushMatrix()
{
    this->stackPointer++;
    if (stackPointer >= stackDepth) {
        std::stringstream message;
        message<<"matrix stack (dimensions:"<<stackDepth<<") full!"
               " Couldn't push something in anymore."
               " Program aborting preventing segmentation fault";
        emitErrorFatal(message.str(),1);
    }

    pStack[stackPointer].copyFrom(pStack[stackPointer-1]);
}

void MatrixStack::PopMatrix()
{
    this->stackPointer--;
    if (stackPointer < 0)
        emitError("matrix stack empty! Couldn't pop from it any more");
}

void MatrixStack::loadIdentity()
{
    pStack[stackPointer].loadIdentity();
}

void MatrixStack::loadMatrix(const Matrix44 &matrix)
{
    pStack[stackPointer].copyFrom(matrix);
}

void MatrixStack::scale(const Vector3 vScale)
{
    Matrix44 mScale;
    mScale.loadScaleMatrix(vScale);
    pStack[stackPointer] = pStack[stackPointer] * mScale;
}

void MatrixStack::translate(const Vector3 vTranslate)
{
    Matrix44 mTranslate;
    mTranslate.loadTranslationMatrix(vTranslate);
    pStack[stackPointer] = pStack[stackPointer] * mTranslate;
}


void MatrixStack::rotate(GLfloat rad, Vector3 vAxis)
{
    Matrix44 mRotation;
    mRotation.loadRotationMatrix(rad,vAxis);
    pStack[stackPointer] = pStack[stackPointer] * mRotation;
}

MatrixStack& MatrixStack::operator*=(const Matrix44& matrix)
{
    pStack[stackPointer] *= matrix;
    return *this;
}

