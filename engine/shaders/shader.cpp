/*
 * Example of the OpenGL usage with SDL2
 * Copyright (C) 2013 Matteo De Carlo <matteo.dek@gmail.com>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */

#include "shader.h"
#include "GL/glew.h"
#include <iostream>
#include <fstream>
#include <cstdarg>

using namespace sm;

bool Shader::loadShaderFile(const char *szFile, GLuint shader)
{
    GLint shaderLength = 0;
    std::ifstream shaderStream;
    shaderStream.open(szFile, std::ios_base::in);
    if (!shaderStream) {
        shaderStream.close();
        return false;
    }

    /*
    while (shaderStream.get() != std::istream::traits_type::eof()) {
        shaderLenght++;
    }

    if(shaderLenght > MAX_SHADER_LENGTH) {
        shaderStream.close();
        return false;
    }

    // Go back at the beginning of the file
    shaderStream.seekg(1);
    char *buffer = new char[shaderLenght+1];
    //shaderStream.read(buffer,shaderLenght);
    for (int i = 0; i<shaderLenght; i++){
        buffer[i] = shaderStream.get();
    }
    buffer[shaderLenght] = '\0';
    */
    char buffer[MAX_SHADER_LENGTH];
    char c;
    while (true) {
        c = shaderStream.get();
        if (c == std::istream::traits_type::eof()) {
            break;
        }
        shaderLength++;
        if (shaderLength >= MAX_SHADER_LENGTH) {
            shaderStream.close();
            return false;
        }
        buffer[shaderLength-1]=c;
    }
    buffer[shaderLength]='\0';

    {
        GLchar *stringArrayPtr[1];
        stringArrayPtr[0] = (GLchar *)buffer;
        glShaderSource(shader, 1, (const GLchar **)stringArrayPtr, NULL);
    }

    shaderStream.close();

    return true;
}

/**
 * Load a pair of shaders, compile, and link together.
 * Specify the complete source text for each shader. After the shader names,
 * specify the number of attributes, followed by the index and attribute name
 * of each attribute
 *
 * @param vertexShaderFilename Path to vertex shader source code
 * @param fragmentShaderFilename Path to the fragment shader source code
 * 
 * //TODO make it take only a single config file that has all of this informations
 */
Shader::Shader(const char* vertexShaderFilename, const char* fragmentShaderFilename, ...)
{
    // Temporary Shader objects
    GLuint hVertexShader;
    GLuint hFragmentShader;
    GLint testVal;
    char *log;
    goto begin;

VertexErrorExit:
    glGetShaderiv(hVertexShader, GL_INFO_LOG_LENGTH, &testVal);
    log = new char[testVal+1];
    glGetShaderInfoLog(hVertexShader, testVal+1, &testVal, log);
    log[testVal] = '\0';
    std::cerr<<"#ERROR: Vertex shader Log:\n"<<log<<std::endl;
    delete[] log;
    glDeleteShader(hVertexShader);
    goto errorExit;

FragmentErrorExit:
    glGetShaderiv(hFragmentShader, GL_INFO_LOG_LENGTH, &testVal);
    log = new char[testVal+1];
    glGetShaderInfoLog(hFragmentShader, testVal+1, &testVal, log);
    log[testVal] = '\0';
    std::cerr<<"#ERROR: Fragment shader Log:\n"<<log<<std::endl;
    delete[] log;
    glDeleteShader(hFragmentShader);

errorExit:
    this->statusValue = false;
    return;

    
begin:
    // Create Shader objects
    std::cerr<<"glCreateShader:"<<glCreateShader<<std::endl;
    hVertexShader = glCreateShader(GL_VERTEX_SHADER);
    hFragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    // Load them
    if (loadShaderFile(vertexShaderFilename, hVertexShader) == false) {
        goto errorExit;
    }
    if (loadShaderFile(fragmentShaderFilename, hFragmentShader) == false) {
        goto errorExit;
    }

    // Compile them
    glCompileShader(hVertexShader);
    glCompileShader(hFragmentShader);


    // Check for errors
    glGetShaderiv(hVertexShader, GL_COMPILE_STATUS, &testVal);
    if(testVal == GL_FALSE)     {
        goto VertexErrorExit;
    }
    glGetShaderiv(hFragmentShader, GL_COMPILE_STATUS, &testVal);
    if(testVal == GL_FALSE)     {
        goto FragmentErrorExit;
    }

    this->shaderPointer = glCreateProgram();
    glAttachShader(shaderPointer,hVertexShader);
    glAttachShader(shaderPointer,hFragmentShader);


    // List of attributes
    va_list attributeList;
    va_start (attributeList, fragmentShaderFilename);

    char *szNextArg;
    int iArgCount = va_arg(attributeList, int); // Number of attributes
    for(int i = 0; i < iArgCount; i++)
    {
        int index = va_arg(attributeList, int);
        szNextArg = va_arg(attributeList, char*);
        glBindAttribLocation(shaderPointer, index, szNextArg);
    }

    va_end(attributeList);

    // Link the shader program
    glLinkProgram(shaderPointer);

    // These are no longer needed
    glDeleteShader(hVertexShader);
    glDeleteShader(hFragmentShader);

    // Make sure the link worked
    glGetProgramiv(shaderPointer, GL_LINK_STATUS, &testVal);
    if (testVal == GL_FALSE) {
        glGetProgramiv(shaderPointer, GL_INFO_LOG_LENGTH, &testVal);
        log = new char[testVal+1];
        glGetShaderInfoLog(shaderPointer, testVal+1, &testVal, log);
        log[testVal] = '\0';
        std::cerr<<"#ERROR: Shader Program Linking :\n"<<log<<std::endl;
        delete[] log;
        glDeleteProgram(shaderPointer);
        goto errorExit;
    }

    this->statusValue = true;
    return;
}

void Shader::Uniform(const char* name, int arg1)
{
    GLint uniformLoc = glGetUniformLocation(shaderPointer,name);
    //this->use();
    glUniform1i(uniformLoc, arg1);
}
void Shader::Uniform(const char* name, int arg1, int arg2)
{
    GLint uniformLoc = glGetUniformLocation(shaderPointer,name);
    //this->use();
    glUniform2i(uniformLoc, arg1, arg2);
}
void Shader::Uniform(const char* name, int arg1, int arg2, int arg3)
{
    GLint uniformLoc = glGetUniformLocation(shaderPointer,name);
    //this->use();
    glUniform3i(uniformLoc, arg1, arg2, arg3);
}
void Shader::Uniform(const char* name, int arg1, int arg2, int arg3, int arg4)
{
    GLint uniformLoc = glGetUniformLocation(shaderPointer,name);
    //this->use();
    glUniform4i(uniformLoc, arg1, arg2, arg3, arg4);
}

//UNIFORM FLOAT
void Shader::Uniform(const char* name, float arg1)
{
    GLint uniformLoc = glGetUniformLocation(shaderPointer,name);
    //this->use();
    glUniform1f(uniformLoc, arg1);
}
void Shader::Uniform(const char* name, float arg1, float arg2)
{
    GLint uniformLoc = glGetUniformLocation(shaderPointer,name);
    //this->use();
    glUniform2f(uniformLoc, arg1, arg2);
}
void Shader::Uniform(const char* name, float arg1, float arg2, float arg3)
{
    GLint uniformLoc = glGetUniformLocation(shaderPointer,name);
    //this->use();
    glUniform3f(uniformLoc, arg1, arg2, arg3);
}
void Shader::Uniform(const char* name, float arg1, float arg2, float arg3, float arg4)
{
    GLint uniformLoc = glGetUniformLocation(shaderPointer,name);
    //this->use();
    glUniform4f(uniformLoc, arg1, arg2, arg3, arg4);
}

void Shader::UniformMatrix33(const char* name, const Matrix33& matrix)
{
    GLint uniformLoc = glGetUniformLocation(shaderPointer,name);
    //this->use();
    glUniformMatrix4fv(uniformLoc, 1, GL_FALSE, matrix.data());
}
void Shader::UniformMatrix44(const char* name, const Matrix44& matrix)
{
    GLint uniformLoc = glGetUniformLocation(shaderPointer,name);
    //this->use();
    glUniformMatrix3fv(uniformLoc, 1, GL_FALSE, matrix.data());
}
