/*
#include <iostream>
#include <SFML/Graphics.hpp>

#define SIZE_X 1920
#define SIZE_Y 1080
#define PIXEL_SIZE SIZE_X * SIZE_Y * 4

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
} */
#define NOMINMAX
#define SIZE_X 400
#define SIZE_Y 400
#define SIZE_ARR SIZE_X * SIZE_Y * 4

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <SFML/Graphics.hpp>
#include <math.h>
#include <time.h>
using namespace sf;

int convertXY(int x, int y) {
	return ((x + (y * SIZE_X)) * 4);
}

void randomArr(Uint8 pixels[]) {
	for (int y = 0; y < SIZE_Y; y++) {
		for (int x = 0; x < SIZE_X; x++) {
			int random = rand() % 256;
			if (random < 157) {
				random = 0;
			}
			else {
				random = 255;
			}
			int k = convertXY(x, y);
			pixels[k] = random;
			pixels[k + 1] = random;
			pixels[k + 2] = random;
			pixels[k + 3] = 255;
		}
		puts("");
	}
}

int numNeighbors(int x, int y, Uint8 oldPixels[]) {
	int onNeighbors = 0;
	if (oldPixels[convertXY(x - 1, y)] == 255) {
		onNeighbors += 1;
	}
	if (oldPixels[convertXY(x + 1, y)] == 255) {
		onNeighbors += 1;
	}
	if (oldPixels[convertXY(x, y - 1)] == 255) {
		onNeighbors += 1;
	}
	if (oldPixels[convertXY(x, y + 1)] == 255) {
		onNeighbors += 1;
	}
	if (oldPixels[convertXY(x - 1, y - 1)] == 255) {
		onNeighbors += 1;
	}
	if (oldPixels[convertXY(x + 1, y - 1)] == 255) {
		onNeighbors += 1;
	}
	if (oldPixels[convertXY(x - 1, y + 1)] == 255) {
		onNeighbors += 1;
	}
	if (oldPixels[convertXY(x + 1, y + 1)] == 255) {
		onNeighbors += 1;
	}
	return onNeighbors;
}

void conway(Uint8 oldPixels[], Uint8 newPixels[]) {
	for (int x = 0; x < SIZE_X; x++) {
		for (int y = 0; y < SIZE_Y; y++) {
			int onNeighbors = numNeighbors(x, y, oldPixels);
			int pixelValue = oldPixels[convertXY(x, y)];
			int k = convertXY(x, y);
			if ((onNeighbors == 2 || onNeighbors == 3) && pixelValue == 255) {
				newPixels[k] = 255;
				newPixels[k + 1] = 255;
				newPixels[k + 2] = 255;
				newPixels[k + 3] = 255;
			}
			else if (onNeighbors == 3 && pixelValue == 0) {
				newPixels[k] = 255;
				newPixels[k + 1] = 255;
				newPixels[k + 2] = 255;
				newPixels[k + 3] = 255;
			}
			else {
				newPixels[k] = 0;
				newPixels[k + 1] = 0;
				newPixels[k + 2] = 0;
				newPixels[k + 3] = 255;
			}
		}
	}
	for (int i = 0; i < SIZE_ARR; i++) {
		oldPixels[i] = newPixels[i];
	}
}

void printScr(Uint8 pixels[]) {
	for (int y = 0; y < SIZE_Y; y++) {
		for (int x = 0; x < SIZE_X; x++) {
			printf("%d", pixels[convertXY(x, y)]);
		}
		puts("");
	}
}

int main() {
	err().rdbuf(NULL);
	srand(time(NULL));
	RenderWindow window(VideoMode(SIZE_X, SIZE_Y), "Conway's Life");
	window.setFramerateLimit(60);
	Uint8* pixels = new Uint8[SIZE_ARR];
	Uint8* newPixels = new Uint8[SIZE_ARR];
	randomArr(pixels);
	Texture texture;
	texture.create(SIZE_X, SIZE_Y);
	texture.update(pixels);
	Sprite sprite;

	clock_t start_t, end_t;
	while (window.isOpen())
	{
		start_t = clock();
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}

		window.clear();
		conway(pixels, newPixels);
		texture.update(pixels);
		sprite.setTexture(texture);
		window.draw(sprite);
		window.display();
		end_t = clock();
		printf("fps: %f\n", 1 / ((double)(end_t - start_t) / CLOCKS_PER_SEC));
	}

	delete[] pixels;
	return 0;
}


/*
	while (1) {
		conway(pixels, newPixels);
		printScr(newPixels);
		Sleep(500);
		system("CLS");
	} */
