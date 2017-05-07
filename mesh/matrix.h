#ifndef MESH_MATRIX_H
#define MESH_MATRIX_H

#include <stdio.h>
#include <string>

class Point2D;
class Point3D;

class Matrix2D
{
  public:
    enum Method{TRANSLATE, SCALE, SHEAR, ROTATE};

    /**
     * TRANSLATE (X, Y)
     * SCALE (X, Y)
     * SHEAR (X, Y)
     * ROTATE (A, 0)
     */

    Matrix2D();
    Matrix2D(const float a_, const float b_, const float c_,
             const float d_, const float e_, const float f_,
             const float g_, const float h_, const float i_);
    Matrix2D(Method method, const float x, const float y);

    float a, b, c;
    float d, e, f;
    float g, h, i;

    Matrix2D operator+(const Matrix2D x) const;
    Matrix2D operator-() const;
    Matrix2D operator-(const Matrix2D x) const;
    Matrix2D operator*(const Matrix2D x) const;

    bool operator==(const Matrix2D x) const;
    bool operator!=(const Matrix2D x) const;

    Matrix2D& operator+=(const Matrix2D x);
    Matrix2D& operator-=(const Matrix2D x);
    Matrix2D& operator*=(const Matrix2D x);

    std::string to_string() const;

    void add_transform(const Matrix2D x);
    Point2D apply_transform(const Point2D x) const;
};

class Matrix3D
{
  public:
    enum Method{TRANSLATE, SCALE, SHEAR_XY, SHEAR_XZ, SHEAR_YZ, ROTATE};

    /**
     * TRANSLATE (X, Y, Z)
     * SCALE (X, Y, Z)
     * SHEAR_XY (X, Y, 0)
     * SHEAR_XZ (X, Z, 0)
     * SHEAR_YZ (Y, Z, 0)
     * ROTATE (A, B, G) jaw, pitch and roll
     */

    Matrix3D();
    Matrix3D(const float a_, const float b_, const float c_, const float d_,
             const float e_, const float f_, const float g_, const float h_,
             const float i_, const float j_, const float k_, const float l_,
             const float m_, const float n_, const float o_, const float p_);
    Matrix3D(Method method, const float x, const float y, const float z);

    float a, b, c, d;
    float e, f, g, h;
    float i, j, k, l;
    float m, n, o, p;

    Matrix3D operator+(const Matrix3D x) const;
    Matrix3D operator-() const;
    Matrix3D operator-(const Matrix3D x) const;
    Matrix3D operator*(const Matrix3D x) const;

    bool operator==(const Matrix3D x) const;
    bool operator!=(const Matrix3D x) const;

    Matrix3D& operator+=(const Matrix3D x);
    Matrix3D& operator-=(const Matrix3D x);
    Matrix3D& operator*=(const Matrix3D x);

    std::string to_string() const;

    void add_transform(const Matrix3D x);
    Point3D apply_transform(const Point3D x) const;
};

#endif // MESH_MATRIX_H
