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

#include "../types.h"
#include <cstring>

#ifndef SMMATRIX33_H
#define SMMATRIX33_H

namespace sm {

class Matrix33 {
    friend class Matrix44;
private:
    typedef smReal int_matrix[3*3];
    int_matrix matrix;
    
    /** performs a copy of the matrix */
    Matrix33(const int_matrix &matrix) {
        memcpy(this->matrix, matrix, sizeof(int_matrix));
    }
    
public:
    /**
     * @brief default loads identity matrix
     * 
     */
    Matrix33() {
        this->loadIdentity();
    }
    
    /**
     * @brief Loads an Identity matrix into the internal data.
     * 
     * All previous data will be lost.
     */
    void loadIdentity() {
        // Don't be fooled, this is still column major
        static const int_matrix identity = { 1, 0, 0,
                                             0, 1, 0,
                                             0, 0, 1 };

        memcpy(this->matrix, identity, sizeof(int_matrix));
    }
    
    /**
     * @brief Loads a matrix full of zero into the internal data
     * 
     * All previuous data will be lost.
     */
    void loadZero() {
        // Don't be fooled, this is still column major
        static const int_matrix zero = { 0, 0, 0,
                                         0, 0, 0,
                                         0, 0, 0 };

        memcpy(this->matrix, zero, sizeof(int_matrix));
    }
    
    /**
     * @brief Copies the matrix "from" into this.
     * 
     * All previous data will be lost.
     */
    void copyFrom(const Matrix33& from) {
        memcpy(this->matrix, from.matrix, sizeof(int_matrix));
    }
    
    /**
     * @brief Copies the matrix "from" into this.
     * 
     * The same as copyFrom(matrix). All previuos data will be lost
     */
    Matrix33& operator=(const Matrix33& from) {
        this->copyFrom(from);
        return *this;
    }
    
    /**
     * @brief Multiplies the matrix "this" as left matrix with the "right" 
     * matrix. The result gets into a new Matrix.
     * 
     * No data from existing matrices gets modified, only a new one gets created.
     */
    Matrix33 operator*(const sm::Matrix33& right) const;

    /**
     * @brief Normalize the column vectors of the matrix
     */
    void normalize();
    
    const smReal* data() const
    {
        return matrix;
    }
};

}

#endif // SMMATRIX44_H