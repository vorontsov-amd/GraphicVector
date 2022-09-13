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


class Vector
{
private:
    double cx, cy;
    double clen;

    Point capp_point = Point(0 , 0);

    sf::VertexArray cline = sf::VertexArray(sf::Lines, 2);
    sf::Color ccolor = sf::Color::White;

public:
    Vector() : Vector(0, 0) {}
    Vector(double x, double y) : cx(x), cy(y), clen(NAN) {}
    Vector(const Vector& init) : cx(init.cx), cy(init.cy), clen(init.clen) {}
    Vector(double x, double y, const SystemCoord sys_coord);


    double length() 
    { 
        if (std::isnan(clen))
        {
            clen = std::sqrt(cx * cx + cy * cy);
        }
        return clen;
    }

    void setAppPoint(const Point& app_point)
    {
        capp_point = app_point;
    }

    void setAppPoint(int x, int y)
    {
        capp_point = Point(x, y);
    }

    void setColor(const sf::Color& color)
    {
        ccolor = color;
    }

    void SetX(double x, const SystemCoord& sys_coord);
    void SetY(double y, const SystemCoord& sys_coord);

    void draw(sf::RenderWindow& window)
    {
        cline[0].position = sf::Vector2f(capp_point.cx + 1, capp_point.cy);
        cline[1].position = sf::Vector2f(capp_point.cx + cx + 1, capp_point.cy + cy);
        cline[0].color    = ccolor;
        cline[1].color    = ccolor;
        window.draw(cline);
    }

    Vector operator+(const Vector& rvec) const
    {
        return Vector(cx + rvec.cx, cy + rvec.cy);
    }

    Vector& operator+=(const Vector& rvec)
    {
        cx += rvec.cx;
        cy += rvec.cy;
        clen = NAN;
        return *this;
    }

    Vector operator-(const Vector& rvec) const
    {
        return Vector(cx - rvec.cx, cy - rvec.cy);
    }

    Vector& operator-=(const Vector& rvec)
    {
        cx -= rvec.cx;
        cy -= rvec.cy;
        clen = NAN;
        return *this;
    }

    int operator*(const Vector& rvec) const 
    {
        return cx * rvec.cx + cy * rvec.cy; 
    }

    friend std::ostream& operator<<(std::ostream& out, const Vector& vec)
    {
        out << "{ " << vec.cx << ", " << vec.cy << " }";
        return out;
    }

    friend std::istream& operator>>(std::istream& in, Vector& vec)
    {
        in >> vec.cx >> vec.cy;
        return in;
    }
};

struct SystemCoord
{
    Point cstart_point;
    Vector ce1;
    Vector ce2;

    SystemCoord(const Point& start_point, const Vector& e1, const Vector& e2) : cstart_point(start_point), ce1(e1), ce2(e2) {}
};


Vector::Vector(double x, double y, const SystemCoord sys_coord)
{
    capp_point = sys_coord.cstart_point;
    cx = sys_coord.ce1.cx * x + sys_coord.ce2.cx * y;
    cy = sys_coord.ce1.cy * x + sys_coord.ce2.cy * y;
    clen = NAN;
}

void Vector::SetX(double x, const SystemCoord& sys_coord)
{
    cx = sys_coord.ce1.cx * x + sys_coord.ce2.cx * cy;
    clen = NAN;
}

void Vector::SetY(double y, const SystemCoord& sys_coord)
{
    cy = sys_coord.ce1.cy * cx + sys_coord.ce2.cy * y;
    clen = NAN;
}