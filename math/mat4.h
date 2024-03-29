/*
 * Ork: a small object-oriented OpenGL Rendering Kernel.
 * Copyright (c) 2008-2010 INRIA
 *
 * This library is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or (at
 * your option) any later version.
 *
 * This library is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License
 * for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this library; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301 USA.
 */

/*
 * Authors: Eric Bruneton, Antoine Begault, Guillaume Piolat.
 */

#ifndef _ORK_MAT4_H_
#define _ORK_MAT4_H_

#include "vec2.h"
#include "vec3.h"
#include "vec4.h"
#include "box3.h"
#include "mat3.h"

namespace sim
{

/**
 * A 4x4 matrix.
 * @ingroup math
 */
template <typename type> class mat4
{
protected:
    /**
     * The matrix coeffients
     */
    union {
        /**
         * The matrix coefficients as a 2D array.
         */
        type m[4][4];

        /**
         * The matrix coefficients as a 1D array.
         */
        type _m[16];
    };

public:

    /**
     * Creates a new, uninitialized matrix.
     */
    mat4();

    /**
     * Creates a new matrix with the given components. The first index is the
     * row index, the second one is the column index.
     */
    mat4(type m00, type m01, type m02, type m03,
         type m10, type m11, type m12, type m13,
         type m20, type m21, type m22, type m23,
         type m30, type m31, type m32, type m33);

    /**
     * Creates a new matrix with the given components in row major order.
     */
    mat4(const type *array);

    /**
     * Creates a new matrix with the given components. The first index is the
     * row index, the second one is the column index.
     */
    mat4(const type array[4][4]);

    /**
     * Creates a new matrix as a copy of the given matrix. The missing
     * components are initialized to 0 (except the w,w component, initialized
     * to 1).
     */
    mat4(const mat3<type>& m3x3);

    /**
     * Returns the coefficients of this matrix.
     */
    const type* coefficients() const;

    /**
     * Returns the row of this matrix whose index is given.
     */
    const type* operator[](int iRow) const;

    /**
     * Assigns the given matrix to this matrix.
     */
    void operator=(const mat3<type>& m3);

    /**
     * Returns true is this matrix is equal to the given matrix.
     */
    bool operator==(const mat4& m2) const;

    /**
     * Returns true is this matrix is different from the given matrix.
     */
    bool operator!=(const mat4& m2) const;

    /**
     * Returns the sum of this matrix and of the given matrix.
     */
    mat4 operator+(const mat4& m2) const;

    /**
     * Returns the difference of this matrix and of the given matrix.
     */
    mat4 operator-(const mat4& m2) const;

    /**
     * Returns the product of this matrix and of the given matrix.
     */
    mat4 operator*(const mat4& m2) const;

    /**
     * Returns the product of this matrix and of the given vector.
     */
    vec4<type> operator*(const vec4<type>& v) const;

    /**
     * Returns the product of this matrix and of the given vector. The given
     * vector w coordinate is set to 1, and the 4 vector result is converted
     * to a 3 vector by dividing its xyz components by its w component.
     */
    vec3<type> operator*(const vec3<type>& v) const;

    /**
     * Returns the bounding box of the given bounding box, transormed
     * by the linear transformation represented by this matrix.
     */
    box3<type> operator*(const box3<type>& b) const;

    /**
     * Returns the product of this matrix and of the given scalar.
     */
    mat4 operator*(type f) const;

    /**
     * Returns the transpose of this matrix.
     */
    mat4 transpose(void) const;

    /**
     * Returns the adjoint of this matrix.
     */
    mat4 adjoint() const;

    /**
     * Returns the inverse of this matrix.
     */
    mat4 inverse() const;

    /**
     * Returns the linear part of this matrix (i.e. without translations).
     */
    mat3<type> mat3x3() const;

    /**
     * Returns the determinant of this matrix.
     */
    type determinant() const;

    /**
     * Returns the translation matrix corresponding to the given translation
     * vector.
     */
    static mat4 translate(const vec3<type>& v);

    /**
     * Returns the rotation matrix corresponding to the rotation around the x
     * axis with the given angle.
     *
     * @param angle rotation angle in degrees.
     */
    static mat4 rotatex(type angle);

    /**
     * Returns the rotation matrix corresponding to the rotation around the y
     * axis with the given angle.
     *
     * @param angle rotation angle in degrees.
     */
    static mat4 rotatey(type angle);

    /**
     * Returns the rotation matrix corresponding to the rotation around the z
     * axis with the given angle.
     *
     * @param angle rotation angle in degrees.
     */
    static mat4 rotatez(type angle);

    /**
     * Returns the perspective projection matrix corresponding to the given
     * projection parameters.
     *
     * @param fovy vertical field of view in degrees.
     * @param aspect aspect ratio of the projection window.
     * @param zNear near clipping plane.
     * @param zFar far clipping plane.
     */
    static mat4 perspectiveProjection(type fovy, type aspect, type zNear, type zFar);

    /**
     * Returns the orthographic projection matrix corresponding to the given
     * projection parameters.
     *
     * @param xRight right clipping plane.
     * @param xLeft left clipping plane.
     * @param yTop top clipping plane.
     * @param yBottom bottom clipping plane.
     * @param zNear near clipping plane.
     * @param zFar far clipping plane.
     */
    static mat4 orthoProjection(type xRight, type xLeft, type yTop, type yBottom, type zNear, type zFar);

    /**
     * Casts this matrix to another base type.
     */
    template <class t>
    mat4<t> cast() const
    {
        return mat4<t>((t) m[0][0], (t) m[0][1], (t) m[0][2], (t) m[0][3],
            (t) m[1][0], (t)m[1][1], (t) m[1][2], (t) m[1][3],
            (t) m[2][0], (t)m[2][1], (t) m[2][2], (t) m[2][3],
            (t) m[3][0], (t)m[3][1], (t) m[3][2], (t) m[3][3]
        );
    }

    /**
     * The null matrix.
     */
    static const mat4 ZERO;

    /**
     * The identity matrix.
     */
    static const mat4 IDENTITY;
};

/**
 * A 4x4 matrix with float components.
 * @ingroup math
 */
typedef mat4<float> mat4f;

/**
 * A 4x4 matrix with double components.
 * @ingroup math
 */
typedef mat4<double> mat4d;

template <typename type>
inline mat4<type>::mat4()
{
}

template <typename type>
inline mat4<type>::mat4(type m00, type m01, type m02, type m03,
                        type m10, type m11, type m12, type m13,
                        type m20, type m21, type m22, type m23,
                        type m30, type m31, type m32, type m33)
{
    m[0][0] = m00;
    m[0][1] = m01;
    m[0][2] = m02;
    m[0][3] = m03;
    m[1][0] = m10;
    m[1][1] = m11;
    m[1][2] = m12;
    m[1][3] = m13;
    m[2][0] = m20;
    m[2][1] = m21;
    m[2][2] = m22;
    m[2][3] = m23;
    m[3][0] = m30;
    m[3][1] = m31;
    m[3][2] = m32;
    m[3][3] = m33;
}

template <typename type>
inline mat4<type>::mat4(const type *array)
{
    memcpy(m, array, 16*sizeof(type));
}

template <typename type>
inline mat4<type>::mat4(const type array[4][4])
{
    memcpy(m, array, 16*sizeof(type));
}

template <typename type>
inline mat4<type>::mat4(const mat3<type>& m3x3)
{
    operator=(IDENTITY);
    operator=(m3x3);
}

template <typename type>
inline const type* mat4<type>::coefficients() const
{
    return _m;
}

template <typename type>
inline const type* mat4<type>::operator[](int iRow) const
{
    //assert(iRow < 4);
    return m[iRow];
}


template <typename type>
inline void mat4<type>::operator=(const mat3<type>& m3)
{
    const type* c = m3.coefficients();
    m[0][0] = c[0 * 3 + 0];
    m[0][1] = c[0 * 3 + 1];
    m[0][2] = c[0 * 3 + 2];
    m[1][0] = c[1 * 3 + 0];
    m[1][1] = c[1 * 3 + 1];
    m[1][2] = c[1 * 3 + 2];
    m[2][0] = c[2 * 3 + 0];
    m[2][1] = c[2 * 3 + 1];
    m[2][2] = c[2 * 3 + 2];
}

template <typename type>
inline bool mat4<type>::operator==(const mat4<type>& m2) const
{
    if (
        m[0][0] != m2.m[0][0] || m[0][1] != m2.m[0][1] || m[0][2] != m2.m[0][2] || m[0][3] != m2.m[0][3] ||
        m[1][0] != m2.m[1][0] || m[1][1] != m2.m[1][1] || m[1][2] != m2.m[1][2] || m[1][3] != m2.m[1][3] ||
        m[2][0] != m2.m[2][0] || m[2][1] != m2.m[2][1] || m[2][2] != m2.m[2][2] || m[2][3] != m2.m[2][3] ||
        m[3][0] != m2.m[3][0] || m[3][1] != m2.m[3][1] || m[3][2] != m2.m[3][2] || m[3][3] != m2.m[3][3])
        return false;

    return true;
}

template <typename type>
inline bool mat4<type>::operator!=(const mat4<type>& m2) const
{
    if (
        m[0][0] != m2.m[0][0] || m[0][1] != m2.m[0][1] || m[0][2] != m2.m[0][2] || m[0][3] != m2.m[0][3] ||
        m[1][0] != m2.m[1][0] || m[1][1] != m2.m[1][1] || m[1][2] != m2.m[1][2] || m[1][3] != m2.m[1][3] ||
        m[2][0] != m2.m[2][0] || m[2][1] != m2.m[2][1] || m[2][2] != m2.m[2][2] || m[2][3] != m2.m[2][3] ||
        m[3][0] != m2.m[3][0] || m[3][1] != m2.m[3][1] || m[3][2] != m2.m[3][2] || m[3][3] != m2.m[3][3])
        return true;

    return false;
}

template <typename type>
inline mat4<type> mat4<type>::operator+(const mat4<type>& m2) const
{
    mat4<type> r;

    r.m[0][0] = m[0][0] + m2.m[0][0];
    r.m[0][1] = m[0][1] + m2.m[0][1];
    r.m[0][2] = m[0][2] + m2.m[0][2];
    r.m[0][3] = m[0][3] + m2.m[0][3];

    r.m[1][0] = m[1][0] + m2.m[1][0];
    r.m[1][1] = m[1][1] + m2.m[1][1];
    r.m[1][2] = m[1][2] + m2.m[1][2];
    r.m[1][3] = m[1][3] + m2.m[1][3];

    r.m[2][0] = m[2][0] + m2.m[2][0];
    r.m[2][1] = m[2][1] + m2.m[2][1];
    r.m[2][2] = m[2][2] + m2.m[2][2];
    r.m[2][3] = m[2][3] + m2.m[2][3];

    r.m[3][0] = m[3][0] + m2.m[3][0];
    r.m[3][1] = m[3][1] + m2.m[3][1];
    r.m[3][2] = m[3][2] + m2.m[3][2];
    r.m[3][3] = m[3][3] + m2.m[3][3];

    return r;
}

template <typename type>
inline mat4<type> mat4<type>::operator-(const mat4<type>& m2) const
{
    mat4 r;
    r.m[0][0] = m[0][0] - m2.m[0][0];
    r.m[0][1] = m[0][1] - m2.m[0][1];
    r.m[0][2] = m[0][2] - m2.m[0][2];
    r.m[0][3] = m[0][3] - m2.m[0][3];

    r.m[1][0] = m[1][0] - m2.m[1][0];
    r.m[1][1] = m[1][1] - m2.m[1][1];
    r.m[1][2] = m[1][2] - m2.m[1][2];
    r.m[1][3] = m[1][3] - m2.m[1][3];

    r.m[2][0] = m[2][0] - m2.m[2][0];
    r.m[2][1] = m[2][1] - m2.m[2][1];
    r.m[2][2] = m[2][2] - m2.m[2][2];
    r.m[2][3] = m[2][3] - m2.m[2][3];

    r.m[3][0] = m[3][0] - m2.m[3][0];
    r.m[3][1] = m[3][1] - m2.m[3][1];
    r.m[3][2] = m[3][2] - m2.m[3][2];
    r.m[3][3] = m[3][3] - m2.m[3][3];


    return r;
}

template <typename type>
inline mat4<type> mat4<type>::operator*(const mat4<type>& m2) const
{
    mat4 r;
    r.m[0][0] = m[0][0] * m2.m[0][0] + m[0][1] * m2.m[1][0] + m[0][2] * m2.m[2][0] + m[0][3] * m2.m[3][0];
    r.m[0][1] = m[0][0] * m2.m[0][1] + m[0][1] * m2.m[1][1] + m[0][2] * m2.m[2][1] + m[0][3] * m2.m[3][1];
    r.m[0][2] = m[0][0] * m2.m[0][2] + m[0][1] * m2.m[1][2] + m[0][2] * m2.m[2][2] + m[0][3] * m2.m[3][2];
    r.m[0][3] = m[0][0] * m2.m[0][3] + m[0][1] * m2.m[1][3] + m[0][2] * m2.m[2][3] + m[0][3] * m2.m[3][3];

    r.m[1][0] = m[1][0] * m2.m[0][0] + m[1][1] * m2.m[1][0] + m[1][2] * m2.m[2][0] + m[1][3] * m2.m[3][0];
    r.m[1][1] = m[1][0] * m2.m[0][1] + m[1][1] * m2.m[1][1] + m[1][2] * m2.m[2][1] + m[1][3] * m2.m[3][1];
    r.m[1][2] = m[1][0] * m2.m[0][2] + m[1][1] * m2.m[1][2] + m[1][2] * m2.m[2][2] + m[1][3] * m2.m[3][2];
    r.m[1][3] = m[1][0] * m2.m[0][3] + m[1][1] * m2.m[1][3] + m[1][2] * m2.m[2][3] + m[1][3] * m2.m[3][3];

    r.m[2][0] = m[2][0] * m2.m[0][0] + m[2][1] * m2.m[1][0] + m[2][2] * m2.m[2][0] + m[2][3] * m2.m[3][0];
    r.m[2][1] = m[2][0] * m2.m[0][1] + m[2][1] * m2.m[1][1] + m[2][2] * m2.m[2][1] + m[2][3] * m2.m[3][1];
    r.m[2][2] = m[2][0] * m2.m[0][2] + m[2][1] * m2.m[1][2] + m[2][2] * m2.m[2][2] + m[2][3] * m2.m[3][2];
    r.m[2][3] = m[2][0] * m2.m[0][3] + m[2][1] * m2.m[1][3] + m[2][2] * m2.m[2][3] + m[2][3] * m2.m[3][3];

    r.m[3][0] = m[3][0] * m2.m[0][0] + m[3][1] * m2.m[1][0] + m[3][2] * m2.m[2][0] + m[3][3] * m2.m[3][0];
    r.m[3][1] = m[3][0] * m2.m[0][1] + m[3][1] * m2.m[1][1] + m[3][2] * m2.m[2][1] + m[3][3] * m2.m[3][1];
    r.m[3][2] = m[3][0] * m2.m[0][2] + m[3][1] * m2.m[1][2] + m[3][2] * m2.m[2][2] + m[3][3] * m2.m[3][2];
    r.m[3][3] = m[3][0] * m2.m[0][3] + m[3][1] * m2.m[1][3] + m[3][2] * m2.m[2][3] + m[3][3] * m2.m[3][3];

    return r;
}

template <typename type>
inline vec4<type> mat4<type>::operator*(const vec4<type>& v) const
{
    return vec4<type>(
               m[0][0] * v.x + m[0][1] * v.y + m[0][2] * v.z + m[0][3] * v.w,
               m[1][0] * v.x + m[1][1] * v.y + m[1][2] * v.z + m[1][3] * v.w,
               m[2][0] * v.x + m[2][1] * v.y + m[2][2] * v.z + m[2][3] * v.w,
               m[3][0] * v.x + m[3][1] * v.y + m[3][2] * v.z + m[3][3] * v.w
           );
}

template <typename type>
inline vec3<type> mat4<type>::operator*(const vec3<type>& v) const
{
    vec3<type> r;

    type fInvW = type(1.0) / (m[3][0] * v.x + m[3][1] * v.y + m[3][2] * v.z + m[3][3]);

    r.x = (m[0][0] * v.x + m[0][1] * v.y + m[0][2] * v.z + m[0][3]) * fInvW;
    r.y = (m[1][0] * v.x + m[1][1] * v.y + m[1][2] * v.z + m[1][3]) * fInvW;
    r.z = (m[2][0] * v.x + m[2][1] * v.y + m[2][2] * v.z + m[2][3]) * fInvW;

    return r;
}

template <typename type>
box3<type> mat4<type>::operator*(const box3<type>& v) const
{
    box3<type> b;
    b = b.enlarge(operator*(vec3<type>(v.xmin, v.ymin, v.zmin)));
    b = b.enlarge(operator*(vec3<type>(v.xmax, v.ymin, v.zmin)));
    b = b.enlarge(operator*(vec3<type>(v.xmin, v.ymax, v.zmin)));
    b = b.enlarge(operator*(vec3<type>(v.xmax, v.ymax, v.zmin)));
    b = b.enlarge(operator*(vec3<type>(v.xmin, v.ymin, v.zmax)));
    b = b.enlarge(operator*(vec3<type>(v.xmax, v.ymin, v.zmax)));
    b = b.enlarge(operator*(vec3<type>(v.xmin, v.ymax, v.zmax)));
    b = b.enlarge(operator*(vec3<type>(v.xmax, v.ymax, v.zmax)));
    return b;
}

template <typename type>
inline mat4<type> mat4<type>::operator*(type f) const
{
    mat4<type> r;

    r.m[0][0] = m[0][0] * f;
    r.m[0][1] = m[0][1] * f;
    r.m[0][2] = m[0][2] * f;
    r.m[0][3] = m[0][3] * f;

    r.m[1][0] = m[1][0] * f;
    r.m[1][1] = m[1][1] * f;
    r.m[1][2] = m[1][2] * f;
    r.m[1][3] = m[1][3] * f;

    r.m[2][0] = m[2][0] * f;
    r.m[2][1] = m[2][1] * f;
    r.m[2][2] = m[2][2] * f;
    r.m[2][3] = m[2][3] * f;

    r.m[3][0] = m[3][0] * f;
    r.m[3][1] = m[3][1] * f;
    r.m[3][2] = m[3][2] * f;
    r.m[3][3] = m[3][3] * f;

    return r;
}

template <typename type>
inline mat4<type> mat4<type>::transpose(void) const
{
    return mat4(m[0][0], m[1][0], m[2][0], m[3][0],
                m[0][1], m[1][1], m[2][1], m[3][1],
                m[0][2], m[1][2], m[2][2], m[3][2],
                m[0][3], m[1][3], m[2][3], m[3][3]);
}

template <typename type>
inline static type
MINOR(const mat4<type>& m, int r0, int r1, int r2, int c0, int c1, int c2)
{
    return type(    m[r0][c0] *(m[r1][c1] * m[r2][c2] - m[r2][c1] * m[r1][c2]) -
                    m[r0][c1] *(m[r1][c0] * m[r2][c2] - m[r2][c0] * m[r1][c2]) +
                    m[r0][c2] *(m[r1][c0] * m[r2][c1] - m[r2][c0] * m[r1][c1]) );
}

template <typename type>
mat4<type> mat4<type>::adjoint() const
{
    return mat4(MINOR(*this, 1, 2, 3, 1, 2, 3),
                -MINOR(*this, 0, 2, 3, 1, 2, 3),
                MINOR(*this, 0, 1, 3, 1, 2, 3),
                -MINOR(*this, 0, 1, 2, 1, 2, 3),

                -MINOR(*this, 1, 2, 3, 0, 2, 3),
                MINOR(*this, 0, 2, 3, 0, 2, 3),
                -MINOR(*this, 0, 1, 3, 0, 2, 3),
                MINOR(*this, 0, 1, 2, 0, 2, 3),

                MINOR(*this, 1, 2, 3, 0, 1, 3),
                -MINOR(*this, 0, 2, 3, 0, 1, 3),
                MINOR(*this, 0, 1, 3, 0, 1, 3),
                -MINOR(*this, 0, 1, 2, 0, 1, 3),

                -MINOR(*this, 1, 2, 3, 0, 1, 2),
                MINOR(*this, 0, 2, 3, 0, 1, 2),
                -MINOR(*this, 0, 1, 3, 0, 1, 2),
                MINOR(*this, 0, 1, 2, 0, 1, 2));
}

template <typename type>
mat4<type> mat4<type>::inverse() const
{
    return adjoint() * (1.0f / determinant());
}

template <typename type>
mat3<type> mat4<type>::mat3x3() const
{
    return mat3<type>(m[0][0], m[0][1], m[0][2],
        m[1][0], m[1][1], m[1][2],
        m[2][0], m[2][1], m[2][2]);
}

template <typename type>
type mat4<type>::determinant() const
{
    return (type)(    m[0][0] * MINOR(*this, 1, 2, 3, 1, 2, 3) -
                    m[0][1] * MINOR(*this, 1, 2, 3, 0, 2, 3) +
                    m[0][2] * MINOR(*this, 1, 2, 3, 0, 1, 3) -
                    m[0][3] * MINOR(*this, 1, 2, 3, 0, 1, 2) );
}

template <typename type>
inline mat4<type> mat4<type>::translate(const vec3<type> &v)
{
    return mat4<type>(1, 0, 0, v.x,
                      0, 1, 0, v.y,
                      0, 0, 1, v.z,
                      0, 0, 0, 1);
}

template <typename type>
inline mat4<type> mat4<type>::rotatex(type angle)
{
    type ca = (type) cos(angle * M_PI / 180.0);
    type sa = (type) sin(angle * M_PI / 180.0);
    return mat4<type>(1, 0, 0, 0,
                      0, ca, -sa, 0,
                      0, sa, ca, 0,
                      0, 0, 0, 1);
}

template <typename type>
inline mat4<type> mat4<type>::rotatey(type angle)
{
    type ca = (type) cos(angle * M_PI / 180.0);
    type sa = (type) sin(angle * M_PI / 180.0);
    return mat4<type>(ca, 0, sa, 0,
                      0, 1, 0, 0,
                      -sa, 0, ca, 0,
                      0, 0, 0, 1);
}

template <typename type>
inline mat4<type> mat4<type>::rotatez(type angle)
{
    type ca = (type) cos(angle * M_PI / 180.0);
    type sa = (type) sin(angle * M_PI / 180.0);
    return mat4<type>(ca, -sa, 0, 0,
                      sa, ca, 0, 0,
                      0, 0, 1, 0,
                      0, 0, 0, 1);
}

template <typename type>
inline mat4<type> mat4<type>::perspectiveProjection(type fovy, type aspect, type zNear, type zFar)
{
    type f = (type) 1 / tan(radians(fovy) / 2);
    return mat4<type>(f / aspect, 0, 0,                         0,
                      0,        f, 0,                         0,
                      0,        0, (zFar + zNear) / (zNear - zFar), (2*zFar*zNear) / (zNear - zFar),
                      0,        0, -1,                        0);
}

template <typename type>
inline mat4<type> mat4<type>::orthoProjection(type xRight, type xLeft, type yTop, type yBottom, type zNear, type zFar)
{
    type tx, ty, tz;
    tx = - (xRight + xLeft) / (xRight - xLeft);
    ty = - (yTop + yBottom) / (yTop - yBottom);
    tz = - (zFar + zNear) / (zFar - zNear);
    return mat4<type>(2 / (xRight - xLeft), 0,                  0,                tx,
                       0,                  2 / (yTop - yBottom), 0,                ty,
                       0,                  0,                 -2 / (zFar - zNear), tz,
                       0,                  0,                  0,                1);
}

template <typename type>
const mat4<type> mat4<type>::ZERO(
    0, 0, 0, 0,
    0, 0, 0, 0,
    0, 0, 0, 0,
    0, 0, 0, 0);

template <typename type>
const mat4<type> mat4<type>::IDENTITY(
    1, 0, 0, 0,
    0, 1, 0, 0,
    0, 0, 1, 0,
    0, 0, 0, 1);

}

#endif
