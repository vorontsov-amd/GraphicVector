#include "vector.h"
#include <chrono>
#include <thread>
#include <SFML/Graphics.hpp>

int main()
{
    Vector e1 = {1, 0};
    Vector e2 = {0, -1};
    Point  O  = {200, 200};
    SystemCoord sys(O, e1, e2);
    Vector vec(120, 0, sys);
    vec.setColor(sf::Color::Red);

    Vector vec2(800, 0, sys);
    vec2.setAppPoint(Point(400, 0), sys);
    std::cout << vec2 << '\n';
    
    sf::RenderWindow window(sf::VideoMode(1600, 900), "SOSAT!");
    sf::CircleShape shape(100.f);
    shape.setOrigin(sf::Vector2f(-100, -100));
    shape.setFillColor(sf::Color::Green);

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
                    vec2.SetX(pixelPos.x);
                    vec2.SetY(pixelPos.y);
                }
            }
        }

        window.clear();
        
        vec.SetX(100 * cos(-t * 0.0003), sys);
        vec.SetY(100 * sin(-t * 0.0003), sys);
        t++;

        window.draw(shape);
        vec.draw(window);
        vec2.draw(window);
                
        window.display();
    }

    return 0;
}