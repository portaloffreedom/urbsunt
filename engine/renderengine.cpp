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

#include "renderengine.h"
#include "GL/glew.h"
#include <iostream>

using namespace sm;

RenderEngine::RenderEngine()
{
    this->initGL();
}

void RenderEngine::initGL()
{
    std::cout<<"version: "<<glGetString(GL_VERSION)<<std::endl;

    GLenum err = glewInit();
    if (GLEW_OK != err) {
        std::cerr<<"GLEW Error: "<<glewGetErrorString(err)<<std::endl;
        exit(1);
    }

    glClearColor(0,0,0,1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

}

void RenderEngine::resizeScene(int width, int height)
{
    glViewport(0,0,width,height);
    viewFrustum.setPerspective(35.0f, float(width)/float(height), 1.0f, 1000.0f);
    projectionMatrix.loadMatrix(viewFrustum.GetProjectionMatrix());
    transformPipeline.setMatrixStacks(modelViewMatix,projectionMatrix);
}
