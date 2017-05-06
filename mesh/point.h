#ifndef MESH_POINT_H
#define MESH_POINT_H

#include <stdio.h>
#include <string>
#include <iostream>

class Point3D;

class Point2D
{
  public:
    Point2D();
    Point2D(const double x_, const double y_);
    Point2D(const Point3D p);

    double x, y;

    Point2D operator+(const Point2D a) const;
    Point2D operator-() const;
    Point2D operator-(const Point2D a) const;
    Point2D operator*(const double a) const;
    Point2D operator/(const double a) const;

    bool operator==(const Point2D a) const;
    bool operator!=(const Point2D a) const;

    Point2D& operator+=(const Point2D a);
    Point2D& operator-=(const Point2D a);
    Point2D& operator*=(const double a);
    Point2D& operator/=(const double a);

    std::string to_string() const;

    bool is_on_screen() const;
};

class Point3D
{
  public:
    Point3D();
    Point3D(const double x_, const double y_, const double z_);
    Point3D(const Point2D p);

    double x, y, z;

    Point3D operator+(const Point3D a) const;
    Point3D operator-() const;
    Point3D operator-(const Point3D a) const;
    Point3D operator*(const double a) const;
    Point3D operator/(const double a) const;

    bool operator==(const Point3D a) const;
    bool operator!=(const Point3D a) const;

    Point3D& operator+=(const Point3D a);
    Point3D& operator-=(const Point3D a);
    Point3D& operator*=(const double a);
    Point3D& operator/=(const double a);

    std::string to_string() const;
};

#endif // MESH_POINT_H
