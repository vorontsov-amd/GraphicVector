#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <cmath>

struct SystemCoord;

struct Point
{
    double cx;
    double cy;
    
    Point(double x = 0, double y = 0) : cx(x), cy(y) {}
};

class BasicVector
{
private:
    double cx;
    double cy;
    double clen;
public:
    BasicVector(double x = 0, double y = 0) : cx(x),       cy(y),       clen(NAN) {}
    BasicVector(const BasicVector& init)    : cx(init.cx), cy(init.cy), clen(init.clen) {}
    BasicVector(double x, double y, const SystemCoord& sys);

    double length();

    virtual void SetX(double x) { cx = x; clen = NAN; }
    virtual void SetY(double y) { cy = y; clen = NAN; }
    virtual void SetX(double x, const SystemCoord& sys_coord);
    virtual void SetY(double y, const SystemCoord& sys_coord);

    double GetX() const { return cx; }
    double GetY() const { return cy; }

    BasicVector operator/(double number) const { return BasicVector(cx / number, cy / number); }
    BasicVector operator*(double number) const { return BasicVector(cx * number, cy * number); }

    BasicVector operator+(const BasicVector& rvec) const { return BasicVector(cx + rvec.cx, cy + rvec.cy); }
    BasicVector operator-(const BasicVector& rvec) const { return BasicVector(cx - rvec.cx, cy - rvec.cy); }

    BasicVector& operator+=(const BasicVector& rvec);
    BasicVector& operator-=(const BasicVector& rvec);

    int operator*(const BasicVector& rvec) const { return cx * rvec.cx + cy * rvec.cy; }

    BasicVector normalize() { return BasicVector(cx / length(), cy / length()); }

    friend std::ostream& operator<<(std::ostream& out, const BasicVector& vec);
    friend std::istream& operator>>(std::istream& in, BasicVector& vec);
};

struct SystemCoord
{
    Point cstart_point;
    BasicVector ce1;
    BasicVector ce2;

    SystemCoord(const Point& start_point, const BasicVector& e1, const BasicVector& e2) :
        cstart_point(start_point),
        ce1(e1),
        ce2(e2)
        {}
};
