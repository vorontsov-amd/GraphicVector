#include <iostream>
#include <SFML/Graphics.hpp>
#include <cmath>

struct Point
{
    double x = 0;
    double y = 0;
};

class Graphic2dVector
{
private:
    double cx, cy;
    double clen;

    sf::VertexArray cline = sf::VertexArray(sf::Lines, 2);
    sf::Color ccolor = sf::Color::White;

public:
    Graphic2dVector() : Graphic2dVector(0, 0) {}
    Graphic2dVector(double x, double y) : cx(x), cy(y), clen(NAN) {}
    Graphic2dVector(const Graphic2dVector& init) : cx(init.cx), cy(init.cy), clen(init.clen) {}

    double length() 
    { 
        if (std::isnan(clen))
        {
            clen = std::sqrt(cx * cx + cy * cy);
        }
        return clen;
    }

    void setColor(const sf::Color& color)
    {
        ccolor = color;
    }

    void draw(sf::RenderWindow& window)
    {
        cline[0].position = sf::Vector2f(0,0);
        cline[1].position = sf::Vector2f(cx, cy);
        cline[0].color    = ccolor;
        cline[1].color    = ccolor;
        window.draw(cline);
    }

    Graphic2dVector operator+(const Graphic2dVector& rvec) const
    {
        return Graphic2dVector(cx + rvec.cx, cy + rvec.cy);
    }

    Graphic2dVector& operator+=(const Graphic2dVector& rvec)
    {
        cx += rvec.cx;
        cy += rvec.cy;
        clen = NAN;
        return *this;
    }

    Graphic2dVector operator-(const Graphic2dVector& rvec) const
    {
        return Graphic2dVector(cx - rvec.cx, cy - rvec.cy);
    }

    Graphic2dVector& operator-=(const Graphic2dVector& rvec)
    {
        cx -= rvec.cx;
        cy -= rvec.cy;
        clen = NAN;
        return *this;
    }

    int operator*(const Graphic2dVector& rvec) const 
    {
        return cx * rvec.cx + cy * rvec.cy; 
    }

    friend std::ostream& operator<<(std::ostream& out, const Graphic2dVector& vec)
    {
        out << "{ " << vec.cx << ", " << vec.cy << " }";
        return out;
    }

    friend std::istream& operator>>(std::istream& in, Graphic2dVector& vec)
    {
        in >> vec.cx >> vec.cy;
        return in;
    }
};
