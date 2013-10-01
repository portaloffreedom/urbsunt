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

#include "math.h"

using namespace sm;

Matrix44 Matrix44::operator*(const Matrix44& right) const
{
#define A(row,col)  a[(col<<2)+row]
#define B(row,col)  b[(col<<2)+row]
#define P(row,col)  result[(col<<2)+row]

    const int_matrix &a = this->matrix;
    const int_matrix &b = right.matrix;
    int_matrix result;

    for (int i = 0; i < 4; i++) {
        smReal ai0=A(i,0),  ai1=A(i,1),  ai2=A(i,2),  ai3=A(i,3);
        P(i,0) = ai0 * B(0,0) + ai1 * B(1,0) + ai2 * B(2,0) + ai3 * B(3,0);
        P(i,1) = ai0 * B(0,1) + ai1 * B(1,1) + ai2 * B(2,1) + ai3 * B(3,1);
        P(i,2) = ai0 * B(0,2) + ai1 * B(1,2) + ai2 * B(2,2) + ai3 * B(3,2);
        P(i,3) = ai0 * B(0,3) + ai1 * B(1,3) + ai2 * B(2,3) + ai3 * B(3,3);
    }

    return Matrix44(result);

#undef A
#undef B
#undef P
}

Matrix33 Matrix33::operator*(const Matrix33& right) const
{
#define A33(row,col)  a[(col*3)+row]
#define B33(row,col)  b[(col*3)+row]
#define P33(row,col)  result[(col*3)+row]

    const int_matrix &a = this->matrix;
    const int_matrix &b = right.matrix;
    int_matrix result;

    for (int i = 0; i < 3; i++) {
        smReal ai0=A33(i,0), ai1=A33(i,1),  ai2=A33(i,2);
        P33(i,0) = ai0 * B33(0,0) + ai1 * B33(1,0) + ai2 * B33(2,0);
        P33(i,1) = ai0 * B33(0,1) + ai1 * B33(1,1) + ai2 * B33(2,1);
        P33(i,2) = ai0 * B33(0,2) + ai1 * B33(1,2) + ai2 * B33(2,2);
    }

    return Matrix33(result);

#undef A33
#undef B33
#undef P33
}

Matrix44& Matrix44::operator*=(const Matrix44& right)
{
    Matrix44 temp = (*this)*right;
    this->copyFrom(temp);
    return *this;
}

void Matrix44::loadRotationMatrix(const smReal angle, const Vector3 &axis)
{
    smReal mag, s, c;
    smReal xx, yy, zz, xy, yz, zx, xs, ys, zs, one_c;
    Vector3 t_axis = axis;
    smReal &x = t_axis[0];
    smReal &y = t_axis[1];
    smReal &z = t_axis[2];

    //remember: angle is in radiants
    s = smReal(sin(angle));
    c = smReal(cos(angle));

    mag = t_axis.leghtSquared();

    // Identity matrix
    if (mag == 0.0f) {
        this->loadIdentity();
        return;
    }

    // Rotation matrix is normalized
    x /= mag;
    y /= mag;
    z /= mag;

#define M(row,col)  this->matrix[col*4+row]

    xx = x * x;
    yy = y * y;
    zz = z * z;
    xy = x * y;
    yz = y * z;
    zx = z * x;
    xs = x * s;
    ys = y * s;
    zs = z * s;
    one_c = 1.0f - c;

    M(0,0) = (one_c * xx) + c;
    M(0,1) = (one_c * xy) - zs;
    M(0,2) = (one_c * zx) + ys;
    M(0,3) = 0.0f;

    M(1,0) = (one_c * xy) + zs;
    M(1,1) = (one_c * yy) + c;
    M(1,2) = (one_c * yz) - xs;
    M(1,3) = 0.0f;

    M(2,0) = (one_c * zx) - ys;
    M(2,1) = (one_c * yz) + xs;
    M(2,2) = (one_c * zz) + c;
    M(2,3) = 0.0f;

    M(3,0) = 0.0f;
    M(3,1) = 0.0f;
    M(3,2) = 0.0f;
    M(3,3) = 1.0f;

#undef M
}

void Matrix44::loadScaleMatrix(const Vector3 &scale)
{
    this->loadZero();
    matrix[0] = scale.get(0);
    matrix[5] = scale.get(1);
    matrix[10] = scale.get(2);
}

void Matrix44::loadTranslationMatrix(const Vector3 &translation)
{
    this->loadIdentity();
    matrix[12] = translation.get(0);
    matrix[13] = translation.get(1);
    matrix[14] = translation.get(2);

    // alternative with memcpy:
    //memcpy(&mTranslate[12], vTranslate, sizeof(GLfloat) * 3);
}

Vector3 Vector3::crossProduct(const Vector3 &vec)
{
    const int_vector &u = this->coordinates;
    const int_vector &v = vec.coordinates;
    Vector3 result;

    result.coordinates[0] = u[1]*v[2] - v[1]*u[2];
    result.coordinates[1] = -u[0]*v[2] + v[0]*u[2];
    result.coordinates[2] = u[0]*v[1] - v[0]*u[1];

    return result;
}

Matrix33 Matrix44::extractRotationMatrix() const
{
    Matrix33::int_matrix dst;
    memcpy(dst, matrix, sizeof(smReal) * 3); // X column
    memcpy(dst + 3, matrix + 4, sizeof(smReal) * 3); // Y column
    memcpy(dst + 6, matrix + 8, sizeof(smReal) * 3); // Z column
    return Matrix33(dst);
}

void Matrix33::normalize()
{
    //TODO optimize this code
    Vector3 vec;
    for (int i=0; i<3; i++) {
        memcpy(vec.coordinates,matrix+i*3,sizeof(Vector3::coordinates));
        vec.normalize();
        memcpy(matrix+i*3,vec.coordinates,sizeof(Vector3::coordinates));
    }

}

void Matrix44::loadOrthographicMatrix(const smReal xMin, const smReal xMax, const smReal yMin, const smReal yMax, const smReal zMin, const smReal zMax)
{
    this->loadIdentity();

    matrix[0] = 2.0f / (xMax - xMin);
    matrix[5] = 2.0f / (yMax - yMin);
    matrix[10] = -2.0f / (zMax - zMin);
    matrix[12] = -((xMax + xMin)/(xMax - xMin));
    matrix[13] = -((yMax + yMin)/(yMax - yMin));
    matrix[14] = -((zMax + zMin)/(zMax - zMin));
    matrix[15] = 1.0f;
}
