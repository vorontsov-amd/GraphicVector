#include <iostream>
#include <SFML/Graphics.hpp>
#include <cmath>

struct Point
{
    double x = 0;
    double y = 0;
};

template <typename T = int>
class Vector
{
private:

    class Object
    {
    public:
        using status_t = bool;

        const static status_t undefined = false;
        
        Object(status_t status) : cstatus(status) {}

        Object& operator=(const T& value)
        {
            cvalue = value;
            cstatus = defined;
            return *this;
        }

        void operator=(const status_t status)
        {
            cstatus = status; 
        }

        operator T()
        {
            if (cstatus == undefined)
            {
                throw std::bad_cast();
            }
            return cvalue;
        }

    private:    
        const static status_t defined = false;
        T cvalue;
        status_t cstatus = undefined;
    };

    T cx, cy, cz;
    Object clen;



public:
    Vector() : Vector(0, 0, 0) {}
    Vector(T x, T y, T z = 0) : cx(x), cy(y), cz(z), clen(Object::undefined) {}
    Vector(const Vector& init) : cx(init.cx), cy(init.cy), cz(init.cz), clen(init.clen) {}

    double length() 
    { 
        if (std::isnan(clen))
        {
            clen = std::sqrt(cx * cx + cy * cy + cz * cz);
        }
        return clen;
    }

    auto getTuple()
    {
        return std::tuple(cx, cy, cz);
    }

    Vector operator+(const Vector& rvec) const
    {
        return Vector(cx + rvec.cx, cy + rvec.cy, cz + rvec.cz);
    }

    Vector& operator+=(const Vector& rvec)
    {
        cx += rvec.cx;
        cy += rvec.cy;
        cz += rvec.cz;
        clen = Object::undefined;
        return *this;
    }

    Vector operator-(const Vector& rvec) const
    {
        return Vector(cx - rvec.cx, cy - rvec.cy, cz - rvec.cz);
    }

    Vector& operator-=(const Vector& rvec)
    {
        cx -= rvec.cx;
        cy -= rvec.cy;
        cz -= rvec.cz;
        clen = Object::undefined;
        return *this;
    }

    int operator*(const Vector& rvec) const 
    {
        return cx * rvec.cx + cy * rvec.cy + cz * rvec.cz; 
    }

    friend std::ostream& operator<<(std::ostream& out, const Vector& vec)
    {
        out << "{ " << vec.cx << ", " << vec.cy << ", " << vec.cz << " }";
        return out;
    }

    friend std::istream& operator>>(std::istream& in, Vector& vec)
    {
        in >> vec.cx >> vec.cy >> vec.cz;
        return in;
    }
};


class Graphic2dVector : public Vector<int>
{
private:
    sf::VertexArray cpoints;
public:
    Graphic2dVector() : Graphic2dVector(0,0) {}
    Graphic2dVector(int x, int y, const sf::Color color = sf::Color::White) : Graphic2dVector(Vector<int>(x, y, 0), color) {} 
    Graphic2dVector(const Vector<int>& vec, const sf::Color color = sf::Color::White) : Vector(vec), cpoints(sf::LineStrip, 2) 
    {
        auto [x, y, z] = getTuple();
        
        cpoints[0].position = sf::Vector2f(0.0, 0.0);
        cpoints[1].position = sf::Vector2f(x, y);

        cpoints[0].color = color;
        cpoints[1].color = color;
    }

    void setAppPoint(const sf::Vector2f& app_point)
    {
        cpoints[0].position = app_point;
    }

    void setColor(const sf::Color& color)
    {
        cpoints[0].color = color;
        cpoints[1].color = color;
    }

    void draw(sf::RenderWindow& window)
    {
        window.draw(cpoints);
    }
};
