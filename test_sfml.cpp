#include "vector.h"
#include <chrono>
#include <thread>
#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(1600, 900), "SOSAT!");
    sf::CircleShape shape(100.f);
    shape.setOrigin(sf::Vector2f(-100, -100));
    shape.setFillColor(sf::Color::White);
    
    Vector e1 = {1, 0};
    Vector e2 = {0, -1};
    Point  O1 = {200, 200};
    Point  O2  = {800, 450};
    SystemCoord sys_1(O1, e1, e2);
    SystemCoord sys_2(O2, e1, e1);

    Vector x = {1600, 0};
    x.setAppPoint(Point(0, 450));
    
    Vector y = {0, -900};
    y.setAppPoint(Point(800, 900));


    Vector vec_1 = {0, 0, sys_1};
    vec_1.setColor(sf::Color::Black);
    vec_1.setThickness(Vector::medium);

    Vector vec_2 = {100, 0, sys_2};
    vec_2.setColor(sf::Color::Blue);
    vec_2.setThickness(Vector::medium);

    int t = 0;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
            
            if (event.type == sf::Event::Closed)
                window.close();
            else if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.key.code == sf::Mouse::Left)
                {
                    vec_2.SetX(pixelPos.x);
                    vec_2.SetY(pixelPos.y);
                }
            }
        }

        window.clear(sf::Color(180, 180, 180));
        
        vec_1.SetX(100 * cos(-t * 0.0003), sys_1);
        vec_1.SetY(100 * sin(-t * 0.0003), sys_1);
        t++;

        window.draw(shape);
        x.draw(window);
        y.draw(window);
        vec_1.draw(window);
        vec_2.draw(window);
                
        window.display();
    }

    return 0;
}