#include "vector.h"

void Vector::setAppPoint(const Point& app_point, const SystemCoord& sys)
{
    BasicVector to_app_point(app_point.cx, app_point.cy, sys);
    
    double x = GetX() + to_app_point.GetX() - capp_point.cx;
    double y = GetY() + to_app_point.GetY() - capp_point.cy;
    SetX(x);
    SetY(y);

    capp_point.cx = to_app_point.GetX();
    capp_point.cy = to_app_point.GetY();
    fillVertexArray();
}

void Vector::setAppPoint(const Point& app_point)
{
    double x = GetX() + app_point.cx - capp_point.cx;
    double y = GetY() + app_point.cy - capp_point.cy;
    SetX(x);
    SetY(y);

    capp_point.cx = app_point.cx;
    capp_point.cy = app_point.cy;
    fillVertexArray();
}

void Vector::setColor(const sf::Color& color) 
{
    cline[0].color    = color;
    cline[1].color    = color;
    carrow[0].color   = color;
    carrow[1].color   = color;
    carrow[2].color   = color;
}

void Vector::draw(sf::RenderWindow& window)
{
    if (GetX() == capp_point.cx && GetY() == capp_point.cy) return;
    
    for (int dy = -cthickness; dy <= cthickness; ++dy)
    {
        for (int dx = -cthickness; dx <= cthickness; ++dx)
        {
            moveFigure(dx, dy);
            window.draw(cline);
            window.draw(carrow);
            moveFigure(-dx, -dy);
        }
    }
}

void Vector::moveFigure(int dx, int dy)
{
    cline[0].position.x += dx;
    cline[0].position.y += dy;
    cline[1].position.x += dx;
    cline[1].position.y += dy;


    carrow[0].position.x += dx;
    carrow[0].position.y += dy;
    carrow[1].position.x += dx;
    carrow[1].position.y += dy;
    carrow[2].position.x += dx;
    carrow[2].position.y += dy;
}

void Vector::fillVertexArray()
{
    createLine();
    createArrow();
}

void Vector::createLine()
{
    cline[0].position = sf::Vector2f(capp_point.cx, capp_point.cy);
    cline[1].position = sf::Vector2f(GetX(), GetY());   
}

void Vector::createArrow()
{
    const double cos30 = std::cos(7 * M_PI / 6); 
    const double sin30 = std::sin(7 * M_PI / 6); 

    auto left_line = BasicVector(cos30 * (GetX() - capp_point.cx) + sin30 * (GetY() - capp_point.cy),
                                -sin30 * (GetX() - capp_point.cx) + cos30 * (GetY() - capp_point.cy));
    left_line = left_line.normalize() * 10;

    auto right_line = BasicVector(cos30 * (GetX() - capp_point.cx) - sin30 * (GetY() - capp_point.cy),
                                  sin30 * (GetX() - capp_point.cx) + cos30 * (GetY() - capp_point.cy));

    right_line = right_line.normalize() * 10;

    auto left_point_vec  = sf::Vector2f( left_line.GetX() + GetX(),  left_line.GetY() + GetY());
    auto right_point_vec = sf::Vector2f(right_line.GetX() + GetX(), right_line.GetY() + GetY());
    
    carrow[0].position = left_point_vec;
    carrow[1].position = cline[1].position;
    carrow[2].position = right_point_vec;
}