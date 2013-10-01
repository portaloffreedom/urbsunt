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

#ifndef ERRORHANDLING_H
#define ERRORHANDLING_H

#include <iostream>
#include <string>
#include <sstream>
#include <SDL2/SDL.h>

namespace sm {

//#define emitError(message) emitError(message,__FILE__,__LINE__)
    /**
    * @brief Emits errors to STDERR.
    * 
    * watch the define: emitError(message) -> emitError(message,__FILE__,__LINE__)
    * 
    * @param message error message.
    * @param file file from witch comes the error. Defaults to nullptr.
    * @param line line from witch comes the error. Defaults to -1.
    * @return void
    */
    void emitError(const char* message, const char* file = nullptr, int line = -1)
    {
        if (file != nullptr && line != -1)
            std::cerr<<file<<':'<<line;
        
        std::cerr<<" SMEngine Error: "<<message<<std::endl;
    }
    void emitError(const std::string &message, const char* file = nullptr, int line = -1){
        emitError(message.data(),file,line);
    }

//#define emitErrorFatal(message,exit_number) emitErrorFatal(message,__FILE__,__LINE__)
    /**
    * @brief Emits errors to STDERR.
    * 
    * watch the define: emitErrorFatal(message,exit_number) -> emitErrorFatal(message,__FILE__,__LINE__)
    * 
    * @param message error message.
    * @param file file from witch comes the error. Defaults to nullptr.
    * @param line line from witch comes the error. Defaults to -1.
    * @return void
    */
    void emitErrorFatal(const char* message, const int exit_number,const char* file = nullptr, int line = -1)
    {
        emitError(message,file,line);
        SDL_Quit();
        exit(exit_number);
    }
    void emitErrorFatal(const std::string &message, const int exit_number, const char* file = nullptr, int line = -1)
    {
        emitErrorFatal(message.data(),exit_number,file,line);
    }
    
    
    /**
    * @brief A simple function that prints a message, the error code returned by SDL, and quits the application.
    * 
    * @param msg error message
    * @return void
    */
    void sdldie(const char *msg)
    {
        std::stringstream message;
        message<<msg<<": "<<SDL_GetError();
        emitErrorFatal(msg,1,nullptr,-1);
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
            std::stringstream message;
            message<<"SDL Error: "<<error;
            emitError(message.str(),file,line);
            SDL_ClearError();
        }
    #endif
    }
}

#endif // ERRORHANDLING_H