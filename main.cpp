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

#include "engine/errorhandling.h"
#include <iostream>
#include <sstream>
#include <GL/glew.h>
#include <SDL2/SDL.h>

void testOpenGL(const int majorGLVersion, const int minorGLVersion) {
    SDL_Window *mainwindow; /* Our window handle */
    SDL_GLContext maincontext; /* Our opengl context handle */
    
    if (SDL_Init(SDL_INIT_VIDEO) < 0) /* Initialize SDL's Video subsystem */
        exit(1);
    
    /* Request the opengl context.
     * TODO choose right OpenGL profile*/
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, majorGLVersion);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, minorGLVersion);
    
    /* Turn on double buffering with a 24bit Z buffer.
     * You may need to change this to 16 or 32 for your system */
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    
    /* Create our window centered at 512x512 resolution */
    std::stringstream windowName;
    windowName<<"testing OpenGL "<<majorGLVersion<<'.'<<minorGLVersion;
    mainwindow = SDL_CreateWindow(windowName.str().data(), SDL_WINDOWPOS_CENTERED, 
                                  SDL_WINDOWPOS_CENTERED, 512, 512, 
                                  SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
    if (!mainwindow) /* Die if creation failed */
        sm::sdldie("Unable to create window");
    
    /* Create our opengl context and attach it to our window */
    maincontext = SDL_GL_CreateContext(mainwindow);
    sm::CheckSDLError();
    
    std::cout<<"version string: "<<glGetString(GL_VERSION)<<std::endl;
    //std::cout<<"version: "<<glGetString(GL_)
    GLint major,minor;
    glGetIntegerv(GL_MAJOR_VERSION, &major);
    glGetIntegerv(GL_MINOR_VERSION, &minor);
    std::cout<<"version: "<<major<<'.'<<minor<<std::endl;
    
    GLenum err = glewInit();
    if (GLEW_OK != err) {
        std::cerr<<"GLEW Error: "<<glewGetErrorString(err)<<std::endl;
        exit(1);
    }
    
    /* This makes our buffer swap syncronized with the monitor's vertical refresh */
    SDL_GL_SetSwapInterval(1);
 
    /* Clear our buffer with a red background */
    glClearColor ( 1.0, 0.0, 0.0, 1.0 );
    glClear ( GL_COLOR_BUFFER_BIT );
    /* Swap our back buffer to the front */     
    SDL_GL_SwapWindow(mainwindow);
    /* Wait 2 seconds */
    SDL_Delay(1000);
 
    /* Same as above, but green */
    glClearColor ( 0.0, 1.0, 0.0, 1.0 );
    glClear ( GL_COLOR_BUFFER_BIT );
    SDL_GL_SwapWindow(mainwindow);
    SDL_Delay(1000);
 
    /* Same as above, but blue */
    glClearColor ( 0.0, 0.0, 1.0, 1.0 );
    glClear ( GL_COLOR_BUFFER_BIT );
    SDL_GL_SwapWindow(mainwindow);
    SDL_Delay(1000);
 
    /* Delete our opengl context, destroy our window, and shutdown SDL */
    SDL_GL_DeleteContext(maincontext);
    SDL_DestroyWindow(mainwindow);
    SDL_Quit();
}

/**
 * @brief Main function
 */
int main(int argc, char **argv) {
    
    /*
    testOpenGL(1,0);
    testOpenGL(1,1);
    testOpenGL(1,2);
    testOpenGL(1,3);
    testOpenGL(1,4);
    testOpenGL(2,0);
    testOpenGL(2,1);
    testOpenGL(2,2);
    testOpenGL(2,3);    
    testOpenGL(3,0);    
    testOpenGL(3,1);    
    testOpenGL(3,2);    
    testOpenGL(3,3);    
    testOpenGL(4,0);    
    testOpenGL(4,1);    
    testOpenGL(4,2);    
    testOpenGL(4,3);
    */
    
    testOpenGL(4,3);
    
    return 0;
}