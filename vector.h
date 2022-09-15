#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <cmath>
#include "basic_vector.h"


class Vector : public BasicVector
{
public:
    enum Thickness { thin, medium, bold };
private:
    Point capp_point       = Point(0 , 0);
    sf::VertexArray cline  = sf::VertexArray(sf::Lines, 2);
    sf::VertexArray carrow = sf::VertexArray(sf::LineStrip, 3);
    Thickness cthickness   = Thickness::thin;

    void fillVertexArray();
    void createLine();
    void createArrow();
    void moveFigure(int x, int y);
public:
    Vector(double x = 0, double y = 0) : BasicVector(x, y) { fillVertexArray(); }
    Vector(const BasicVector& init)    : BasicVector(init) { fillVertexArray(); }
    Vector(double x, double y, const SystemCoord& sys) : BasicVector(x, y, sys), capp_point(sys.cstart_point) { fillVertexArray(); }

    void SetX(double x) { BasicVector::SetX(x); fillVertexArray(); }
    void SetY(double y) { BasicVector::SetY(y); fillVertexArray(); }
    void SetX(double x, const SystemCoord& sys) { BasicVector::SetX(x, sys); fillVertexArray(); }
    void SetY(double y, const SystemCoord& sys) { BasicVector::SetY(y, sys); fillVertexArray(); }

    void setThickness(Thickness thickness) { cthickness = thickness; }
    void setAppPoint(const Point& app_point, const SystemCoord& sys_coord);
    void setAppPoint(const Point& app_point);
    void setColor(const sf::Color& color);

    void draw(sf::RenderWindow& window);
};

