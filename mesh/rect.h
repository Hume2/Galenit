#ifndef RECT_H
#define RECT_H

#include "point.h"

class Rect2D
{
  public:
    Rect2D();
    Rect2D(Point2D p1, Point2D p2);
    Rect2D(float x1, float y1, float x2, float y2);

    Point2D p1, p2;

    void normalize(); //sets the size to positive coordinates
    void resize(Point2D size);

    Point2D get_size() const;
    bool collides(const Rect2D a) const;
    bool is_inside(const Point2D a) const;

    bool operator==(const Rect2D a) const;
    bool operator!=(const Rect2D a) const;
};

class Rect3D
{
  public:
    Rect3D();
    Rect3D(Point3D p1, Point3D p2);
    Rect3D(float x1, float y1, float z1, float x2, float y2, float z2);

    Point3D p1, p2;

    void normalize(); //sets the size to positive coordinates
    void resize(Point3D size);

    Point3D get_size() const;
    bool collides(const Rect3D a) const;
    bool is_inside(const Point3D a) const;

    bool operator==(const Rect3D a) const;
    bool operator!=(const Rect3D a) const;
};

#endif // RECT_H
