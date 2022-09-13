#include "vector.h"
#include <chrono>
#include <thread>

#include <SFML/Graphics.hpp>

int main()
{
    Vector e1(1, 0);
    Vector e2(0, -1);
    Point  O(200, 200);
    SystemCoord sys(O, e1, e2);
    Vector vec(120, 0, sys);
    vec.setColor(sf::Color::Red);
    
    sf::RenderWindow window(sf::VideoMode(800, 600), "SOSAT!");
    sf::CircleShape shape(100.f);
    shape.setOrigin(sf::Vector2f(-100, -100));
    shape.setFillColor(sf::Color::Green);

    int t = 0;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        
        vec.SetX(100 * cos(t * 0.0003), sys);
        vec.SetY(100 * sin(t * 0.0003), sys);
        t++;

        window.draw(shape);
        vec.draw(window);
                
        window.display();
    }

    return 0;
}