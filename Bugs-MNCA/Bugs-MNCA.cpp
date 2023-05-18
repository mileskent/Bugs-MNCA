#include <SFML/Graphics.hpp>
#include <iostream>

int main() {
	sf::err().rdbuf(NULL);
	const float winW = 800;
	const float winH = 800;

	sf::RenderWindow window(sf::VideoMode(winW, winH), "SFML Shader Example");
	// window.setMouseCursorVisible(false); // hide the cursor

	// Create a texture and a sprite for the shader
	sf::Texture tex;
	tex.create(winW, winH);
	sf::Sprite spr(tex);

	sf::Shader shader;


	if (!sf::Shader::isAvailable() || !shader.loadFromFile(".\\mnca.glsl", sf::Shader::Fragment))
	{
		std::cout << "Error loading shader!\n";
		return 1;
	}

	shader.setUniform("texture", sf::Shader::CurrentTexture);

	while (window.isOpen()) {
		sf::Event event;

		while (window.pollEvent(event)) {
			if (event.type == sf::Event::KeyPressed)
				window.close();
		}

		window.clear();
		window.draw(spr, &shader);
		window.display();
	}

	return 0;
}