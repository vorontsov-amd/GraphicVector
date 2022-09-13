#include <SFML/Graphics.hpp>
#include "vector.h"

int main()
{
    Graphic2dVector vec(100, 20);
    std::cin >> vec;
    std::cout << vec;

    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        vec.draw(window);
        window.display();
    }

    return 0;
}