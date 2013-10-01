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

#ifndef SM_SHADER_H
#define SM_SHADER_H

#include "../math/math.h"
#include "GL/glew.h"

namespace sm {

class Shader
{
public:
    enum ATTRIBUTE {
        ATTRIBUTE_VERTEX  = 0,
        ATTRIBUTE_COLOR   = 1,
        ATTRIBUTE_NORMAL  = 2,
        ATTRIBUTE_TEXTURE = 3,
        ATTRIBUTE_4  = 4,
        ATTRIBUTE_5  = 5,
        ATTRIBUTE_6  = 6,
        ATTRIBUTE_7  = 7,
        ATTRIBUTE_8  = 8,
        ATTRIBUTE_9  = 9,
        ATTRIBUTE_10 = 10,
        ATTRIBUTE_11 = 11,
        ATTRIBUTE_12 = 12,
        ATTRIBUTE_13 = 13,
        ATTRIBUTE_14 = 14,
        ATTRIBUTE_15 = 15
    };
    
    static const int MAX_SHADER_LENGTH = 8192;

    Shader(const char *vertexShaderFilename, const char *fragmentShaderFilename, ...);

    //UNIFORM INTEGER
    void Uniform(const char* name, const int arg1);
    void Uniform(const char* name, const int arg1, const int arg2);
    void Uniform(const char* name, const int arg1, const int arg2, const int arg3);
    void Uniform(const char* name, const int arg1, const int arg2, const int arg3, const int arg4);
    //UNIFORM FLOAT
    void Uniform(const char* name, const smReal arg1);
    void Uniform(const char* name, const smReal arg1, const smReal arg2);
    void Uniform(const char* name, const smReal arg1, const smReal arg2, const smReal arg3);
    void Uniform(const char* name, const smReal arg1, const smReal arg2, const smReal arg3, const smReal arg4);
    //UNIFORM MATRIX
    void UniformMatrix44(const char *name, const Matrix44 &matrix);
    void UniformMatrix33(const char *name, const Matrix33 &matrix);


private:
    bool statusValue;

    GLuint shaderPointer;
    bool loadShaderFile(const char *szFile, GLuint shader);



};
}

#endif // SM_SHADER_H
