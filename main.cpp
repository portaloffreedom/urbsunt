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


#include <iostream>
#include <GL/glew.h>
#include <SDL2/SDL.h>


#define PROGRAM_NAME "Tutorial1"

/**
 * @brief A simple function that prints a message, the error code returned by SDL, and quits the application.
 * 
 * @param msg error message
 * @return void
 */
void sdldie(const char *msg)
{
    std::cerr<<msg<<": "<<SDL_GetError()<<std::endl;
    SDL_Quit();
    exit(1);
}

#define CheckSDLError() checkSDLError(__FILE__,__LINE__)
void checkSDLError(const char* file = nullptr,int line = -1)
/**
 * @brief Checks if there are SDL errores and prints them on STDERR.
 * 
 * @param file file from witch comes the error. Defaults to nullptr.
 * @param line line from witch comes the error. Defaults to -1.
 * @return void
 */
{
#ifndef NDEBUG
        const char *error = SDL_GetError();
        if (*error != '\0')
        {
                std::cerr<<"SDL Error: "<<error<<std::endl;
                if (line != -1 && file != nullptr)
                        std::cerr<<file<<':'<<line<<std::endl;
                SDL_ClearError();
        }
#endif
}

/**
 * @brief Main function
 */
int main(int argc, char **argv) {
    std::cout << "Hello, world!" << std::endl;
    
    SDL_Window *mainwindow; /* Our window handle */
    SDL_GLContext maincontext; /* Our opengl context handle */
    
    if (SDL_Init(SDL_INIT_VIDEO) < 0) /* Initialize SDL's Video subsystem */
        return 1;
    
    /* Request opengl 4.3 context.
     * TODO choose right OpenGL profile*/
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    
    /* Turn on double buffering with a 24bit Z buffer.
     * You may need to change this to 16 or 32 for your system */
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    
    /* Create our window centered at 512x512 resolution */
    mainwindow = SDL_CreateWindow(PROGRAM_NAME, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        512, 512, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
    if (!mainwindow) /* Die if creation failed */
        sdldie("Unable to create window");
    
    /* Create our opengl context and attach it to our window */
    maincontext = SDL_GL_CreateContext(mainwindow);
    CheckSDLError();
    
    std::cout<<"version: "<<glGetString(GL_VERSION)<<std::endl;
    
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
    SDL_Delay(2000);
 
    /* Same as above, but green */
    glClearColor ( 0.0, 1.0, 0.0, 1.0 );
    glClear ( GL_COLOR_BUFFER_BIT );
    SDL_GL_SwapWindow(mainwindow);
    SDL_Delay(2000);
 
    /* Same as above, but blue */
    glClearColor ( 0.0, 0.0, 1.0, 1.0 );
    glClear ( GL_COLOR_BUFFER_BIT );
    SDL_GL_SwapWindow(mainwindow);
    SDL_Delay(2000);
 
    /* Delete our opengl context, destroy our window, and shutdown SDL */
    SDL_GL_DeleteContext(maincontext);
    SDL_DestroyWindow(mainwindow);
    SDL_Quit();
    
    return 0;
}