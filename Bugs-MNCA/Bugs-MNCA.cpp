#include <SFML/Graphics.hpp>
#include <iostream>
#include <time.h>
#include <stdlib.h>

int main() {
	sf::err().rdbuf(NULL);
	const float winW = 800;
	const float winH = 800;


	sf::RenderWindow window(sf::VideoMode(winW, winH), "Bugs-MNCA");
	// window.setMouseCursorVisible(false); // hide the cursor
	window.setFramerateLimit(60);

	// Create a texture and a sprite for the shader
	sf::Texture tex;
	tex.create(winW, winH);
	sf::Sprite spr(tex);

	sf::Uint8 * pixels = new sf::Uint8[winH * winW];

	for (size_t k = 0; k < winH * winW; k += 4)
	{
		sf::Uint8 val = rand() % 256;
		*(pixels + k) = val;
		*(pixels + k + 1) = *(pixels + k);
		*(pixels + k + 2) = *(pixels + k);
		*(pixels + k + 3) = 255;
	}

	tex.update(pixels);
	spr.setTexture(tex);
	delete[] pixels;

	sf::Shader shader;


	if (!sf::Shader::isAvailable() || !shader.loadFromFile(".\\mnca.glsl", sf::Shader::Fragment))
	{
		std::cout << "Error loading shader!\n";
		return 1;
	}

	shader.setUniform("u_resolution", sf::Vector2f(winW, winH));

	while (window.isOpen())
	{
		sf::Event event;

		while (window.pollEvent(event)) {
			if (event.type == sf::Event::KeyPressed)
				window.close();
		}

		shader.setUniform("u_time", (float)clock());
		window.clear();
		window.draw(spr, &shader);
		window.display();
	}

	return 0;
}