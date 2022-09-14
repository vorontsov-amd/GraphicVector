#include <iostream>
#include <SFML/Graphics.hpp>
#include <cmath>

struct SystemCoord;

struct Point
{
    double cx;
    double cy;
    double clen = NAN;

    Point(double x = 0, double y = 0) : cx(x), cy(y) {}
    Point operator+(const Point& right) const
    {
        return Point(cx + right.cx, cy + right.cy);
    }
    Point operator/(double number)
    {
        return Point(cx / number, cy / number);
    }
    Point operator*(double number)
    {
        return Point(cx * number, cy * number);
    }
    double length() 
    { 
        if (std::isnan(clen))
        {
            clen = std::sqrt(cx * cx + cy * cy);
        }
        return clen;
    }
    Point normalize()
    {
        return Point(cx / length(), cy / length());
    }
};


class Vector
{
private:
    double cx, cy;
    double clen;

    Point capp_point = Point(0 , 0);
    sf::VertexArray cline = sf::VertexArray(sf::Lines, 2);
    sf::VertexArray carrow = sf::VertexArray(sf::LineStrip, 3);
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

    void setAppPoint(const Point& app_point, const SystemCoord& sys_coord);
    void setAppPoint(int x, int y, const SystemCoord& sys_coord);
    

    void setColor(const sf::Color& color)
    {
        ccolor = color;
    }

    void SetX(double x, const SystemCoord& sys_coord);
    void SetY(double y, const SystemCoord& sys_coord);
    void SetX(double x);
    void SetY(double y);

    void draw(sf::RenderWindow& window)
    {
        const double cos30 = std::cos(7 * M_PI / 6); 
        const double sin30 = std::sin(7 * M_PI / 6); 

        auto left_point = Point(cos30 * (cx - capp_point.cx) + sin30 * (cy - capp_point.cy),
                               -sin30 * (cx - capp_point.cx) + cos30 * (cy - capp_point.cy));
        left_point = left_point.normalize() * 10;

        auto right_point = Point(cos30 * (cx - capp_point.cx) - sin30 * (cy - capp_point.cy),
                                 sin30 * (cx - capp_point.cx) + cos30 * (cy - capp_point.cy));

        right_point = right_point.normalize() * 10;

        auto left_point_vec  = sf::Vector2f(left_point.cx + cx, left_point.cy + cy);
        auto right_point_vec = sf::Vector2f(right_point.cx + cx, right_point.cy + cy);
        
        cline[0].position = sf::Vector2f(capp_point.cx, capp_point.cy);
        cline[1].position = sf::Vector2f(cx, cy);

        carrow[0].position = left_point_vec;
        carrow[1].position = cline[1].position;
        carrow[2].position = right_point_vec;

        
        cline[0].color    = ccolor;
        cline[1].color    = ccolor;
        carrow[0].color   = sf::Color::Green;
        carrow[1].color   = sf::Color::Blue;
        carrow[2].color   = sf::Color::Yellow;


        window.draw(cline);
        window.draw(carrow);
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
    cx = sys_coord.ce1.cx * x + sys_coord.ce2.cx * y + sys_coord.cstart_point.cx;
    cy = sys_coord.ce1.cy * x + sys_coord.ce2.cy * y + sys_coord.cstart_point.cy;
    clen = NAN;
}

void Vector::SetX(double x, const SystemCoord& sys_coord)
{
    cx = sys_coord.ce1.cx * x + sys_coord.ce2.cx * cy + sys_coord.cstart_point.cx;
    clen = NAN;
}

void Vector::SetY(double y, const SystemCoord& sys_coord)
{
    cy = sys_coord.ce1.cy * cx + sys_coord.ce2.cy * y + sys_coord.cstart_point.cy;
    clen = NAN;
}


void Vector::SetX(double x)
{
    cx = x;
    clen = NAN;
}

void Vector::SetY(double y)
{
    cy = y;
    clen = NAN;
}

void Vector::setAppPoint(const Point& app_point, const SystemCoord& sys_coord)
{
    capp_point = app_point + sys_coord.cstart_point;
}

void Vector::setAppPoint(int x, int y, const SystemCoord& sys_coord)
{
    capp_point = Point(x, y) + sys_coord.cstart_point;
}