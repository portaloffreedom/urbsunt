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


#ifndef SMVECTOR4_H
#define SMVECTOR4_H

#include "../types.h"
#include <cstring>
#include <cmath>

namespace sm {

class Vector4 {
    /**
     * @brief Implementation of a vector in 4 dimensions 
     * 
     * Warning! this class previleges always to copy a vector, not to reference
     * it. If you want a reference to a vector, please use the C/C++ tools for
     * referencing objects (es *vector)
     * 
     */
    
public:
    /**
     * @brief Creates a 3D vector with all values inizialized to 0
     * 
     */
    inline Vector4() : Vector4(0,0,0,0)
    {
    }
    
    /**
     * @brief Create a 3D vector with values inizialized as passed
     * 
     */
    inline Vector4(smReal x,smReal y,smReal z, smReal w) {
        coordinates[0] = x;
        coordinates[1] = y;
        coordinates[2] = z;
        coordinates[3] = w;
    }
    
    /**
     * @brief Create a new 4D vector with values copyed from the vector passed
     * 
     */
    inline Vector4(Vector4& vec) {
        this->copyFrom(vec);
    }
    
    /**
     * @brief copies the data of the vector passed into the vector "this"
     * 
     * Same as "copyFrom(vec)"
     * 
     */
    inline Vector4& operator=(const Vector4 &vec) {
        this->copyFrom(vec);
        return *this;
    }
    
    /**
     * @brief copies the data from the vector passed to the vector "this"
     * 
     */
    inline void copyFrom(const Vector4 &vec) {
        memcpy(this->coordinates,vec.coordinates,sizeof(int_vector));
    }
    
    inline Vector4& operator-() {
        this->scale(-1);
        return *this;
    }
    
    /*
     * @brief cross product between this and vec
     * 
     * @param vec vector to cross product with
     * @return sm::Vector4 return the result (in a new object)
     */
    //Vector4 crossProduct(const Vector4 vec);
    
    /**
     * @brief scales the vector with the "scale" value
     * 
     * @param scale value to scale
     */
    inline void scale(const smReal scale) {
        this->coordinates[0] *= scale;
        this->coordinates[1] *= scale; 
        this->coordinates[2] *= scale;
        this->coordinates[3] *= scale;
    }
    
    /**
     * @brief calculate the lenght squared of the vector
     * 
     * @return smReal - the leght squared of the vector
     */
    smReal leghtSquared() {
        const int_vector &u = this->coordinates;
        return (u[0] * u[0]) 
             + (u[1] * u[1]) 
             + (u[2] * u[2])
             + (u[3] * u[3]);
    }
    
    /**
     * @brief calculate the lenght of the vector
     * 
     * @return smReal - the lenght of the vector
     */
    smReal lenght() {
        return sqrt(this->leghtSquared());
    }
    
    /**
     * @brief Normalize the vector
     */
    void normalize() {
        this->scale(1.0/this->lenght());
    }
    
    smReal& operator[](int pos) 
    {
        return coordinates[pos];
    }
    
private:
    typedef smReal int_vector[4];
    int_vector coordinates;

};

}
#endif // SMVECTOR4_H
