#ifndef MESH_POINT_H
#define MESH_POINT_H

#include <stdio.h>
#include <string>
#include <iostream>

class Point3D;

class Cubepos;
class Toepos;

class Point2D
{
  public:
    Point2D();
    Point2D(const float x_, const float y_);
    Point2D(const Point3D p);

    float x, y;

    Point2D operator+(const Point2D a) const;
    Point2D operator-() const;
    Point2D operator-(const Point2D a) const;
    Point2D operator*(const float a) const;
    Point2D operator/(const float a) const;

    bool operator==(const Point2D a) const;
    bool operator!=(const Point2D a) const;

    Point2D& operator+=(const Point2D a);
    Point2D& operator-=(const Point2D a);
    Point2D& operator*=(const float a);
    Point2D& operator/=(const float a);

    std::string to_string() const;

    bool is_on_screen() const;
};

class Point3D
{
  public:
    Point3D();
    Point3D(const float x_, const float y_, const float z_);
    Point3D(const Point2D p);
    Point3D(const Cubepos p);
    Point3D(const Toepos p);

    float x, y, z;

    Point3D operator+(const Point3D a) const;
    Point3D operator-() const;
    Point3D operator-(const Point3D a) const;
    Point3D operator*(const float a) const;
    Point3D operator/(const float a) const;

    bool operator==(const Point3D a) const;
    bool operator!=(const Point3D a) const;

    Point3D& operator+=(const Point3D a);
    Point3D& operator-=(const Point3D a);
    Point3D& operator*=(const float a);
    Point3D& operator/=(const float a);

    std::string to_string() const;
};

#endif // MESH_POINT_H
