#include <iostream>
#include <SFML/Graphics.hpp>

#define SIZE_X 1920
#define SIZE_Y 1080
#define PIXEL_SIZE 

int main()
{
    sf::err().rdbuf(NULL);
    sf::RenderWindow window(sf::VideoMode(SIZE_X, SIZE_Y), "This a window");
    window.clear();
    sf::Uint8* pixels = new sf::Uint8[PIXEL_SIZE];
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        for (int x = 0; x < SIZE_X; x++) {
            for (int y = 0; y < SIZE_Y; y++) {
                sf::Vertex point(sf::Vector2f(x, y), sf::Color(rand() % 255, rand() % 255, rand() % 255, 255));
                window.draw(&point, 1, sf::Points);
            }
        }
        window.display();
    }

    return 0;
}