#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <SFML/Graphics.hpp>
#include <math.h>
#include <time.h>
using namespace sf;
using namespace std;
constexpr unsigned int SCREEN_WIDTH = 200;
constexpr unsigned int SCREEN_HEIGHT = SCREEN_WIDTH;
constexpr unsigned int PIXEL_SIZE = SCREEN_WIDTH * SCREEN_HEIGHT * 4;

static int SEED = 0;

int perlinhash[] = { 208,34,231,213,32,248,233,56,161,78,24,140,71,48,140,254,245,255,247,247,40,
                     185,248,251,245,28,124,204,204,76,36,1,107,28,234,163,202,224,245,128,167,204,
                     9,92,217,54,239,174,173,102,193,189,190,121,100,108,167,44,43,77,180,204,8,81,
                     70,223,11,38,24,254,210,210,177,32,81,195,243,125,8,169,112,32,97,53,195,13,
                     203,9,47,104,125,117,114,124,165,203,181,235,193,206,70,180,174,0,167,181,41,
                     164,30,116,127,198,245,146,87,224,149,206,57,4,192,210,65,210,129,240,178,105,
                     228,108,245,148,140,40,35,195,38,58,65,207,215,253,65,85,208,76,62,3,237,55,89,
                     232,50,217,64,244,157,199,121,252,90,17,212,203,149,152,140,187,234,177,73,174,
                     193,100,192,143,97,53,145,135,19,103,13,90,135,151,199,91,239,247,33,39,145,
                     101,120,99,3,186,86,99,41,237,203,111,79,220,135,158,42,30,154,120,67,87,167,
                     135,176,183,191,253,115,184,21,233,58,129,233,142,39,128,211,118,137,139,255,
                     114,20,218,113,154,27,127,246,250,1,8,198,250,209,92,222,173,21,88,102,219 };

Vector2f i2xy(size_t k);
size_t xy2i(Vector2f p);
bool inbound(Vector2f p);
float dist(Vector2f p1, Vector2f p2);
float perlin2d(float x, float y, float freq, int depth);
int noise2(int x, int y);
float lin_inter(float x, float y, float s);
float smooth_inter(float x, float y, float s);
float noise2d(float x, float y);

bool run = true;

int main()
{
    RenderWindow window(VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Window Title");
    window.setFramerateLimit(60);

    Uint8* pixels = new Uint8[PIXEL_SIZE];

    for (size_t k = 0; k < PIXEL_SIZE; k += 4)
    {
        Vector2f a = i2xy(k);
        Uint8 val = perlin2d(a.x, a.y, .3, 4) * 255;
        if (val < 157)
            val = 0;
        else
            val = 255;
        *(pixels + k) = val;
        *(pixels + k + 1) = *(pixels + k);
        *(pixels + k + 2) = *(pixels + k);
        *(pixels + k + 3) = 255;
    }

    if (pixels != NULL)
    {
        printf("Pixels intialized.\n");
    }
    else
    {
        window.close();
        delete[] pixels;
        return 0;
    }

    Texture texture;
    texture.create(SCREEN_WIDTH, SCREEN_HEIGHT);
    texture.update(pixels);
    Sprite sprite;

    // generate the neighborhoods

    Vector2f smallnh[36];
    size_t c = 0;

    for (int x = -4; x <= 4; x++)
    {
        for (int y = -4; y <= 4; y++)
        {
            float d = dist(Vector2f(0, 0), Vector2f(x, y));
            if (d > 0 && d <= 3.51)
            {
                smallnh[c++] = Vector2f(x, y);
            }
        }
    }

    Vector2f bignh[108];
    c = 0;

    for (int x = -8; x <= 8; x++)
    {
        for (int y = -8; y <= 8; y++)
        {
            float d = dist(Vector2f(0, 0), Vector2f(x, y));
            if (d >= 4.51 && d <= 7.51)
            {
                bignh[c++] = Vector2f(x, y);
            }
        }
    }

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

        if (run)
        {
            for (size_t k = 0; k < PIXEL_SIZE; k += 4)
            {
                Vector2f pk = i2xy(k);

                float nh0 = 0;
                float nh1 = 0;

                int c1 = 0;
                for (int i = 0; i < 36; i++)
                {
                    if (inbound(pk + smallnh[i]))
                    {
                        c1++;
                        nh0 += pixels[xy2i(pk + smallnh[i])];
                    }

                }
                nh0 /= c1;


                int c2 = 0;
                for (int i = 0; i < 108; i++)
                {
                    if (inbound(pk + bignh[i]))
                    {
                        c2++;
                        nh1 += pixels[xy2i(pk + bignh[i])];
                    }

                }
                nh1 /= c2;

                if (nh0 <= 25) { *(pixels + k) = 0; }
                else if (nh0 <= 50 && nh0 >= 25) { *(pixels + k) = 0; }
                else if (nh0 >= 190) { *(pixels + k) = 255; }

                if (nh1 >= 50 && nh1 <= 71) { *(pixels + k) = 0; }
                else if (nh1 >= 109 && nh1 <= 140) { *(pixels + k) = 255; }
                else if (nh1 >= 140 && nh1 <= 255) { *(pixels + k) = 0; }

                *(pixels + k + 1) = *(pixels + k);
                *(pixels + k + 2) = *(pixels + k);
            }
        }
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

Vector2f i2xy(size_t k)
{
    return Vector2f((k / 4) % SCREEN_WIDTH, (k / 4) / SCREEN_WIDTH);
}
size_t xy2i(Vector2f p)
{
    return p.y * SCREEN_WIDTH * 4 + p.x * 4;
}
bool inbound(Vector2f p)
{
    return (p.x >= 0 && p.x <= SCREEN_WIDTH && p.y >= 0 && p.y <= SCREEN_HEIGHT);
}
float dist(Vector2f p1, Vector2f p2)
{
    return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
}

int noise2(int x, int y)
{
    int tmp = perlinhash[(y + SEED) % 256];
    return perlinhash[(tmp + x) % 256];
}
float lin_inter(float x, float y, float s)
{
    return x + s * (y - x);
}
float smooth_inter(float x, float y, float s)
{
    return lin_inter(x, y, s * s * (3 - 2 * s));
}
float noise2d(float x, float y)
{
    int x_int = x;
    int y_int = y;
    float x_frac = x - x_int;
    float y_frac = y - y_int;
    int s = noise2(x_int, y_int);
    int t = noise2(x_int + 1, y_int);
    int u = noise2(x_int, y_int + 1);
    int v = noise2(x_int + 1, y_int + 1);
    float low = smooth_inter(s, t, x_frac);
    float high = smooth_inter(u, v, x_frac);
    return smooth_inter(low, high, y_frac);
}
float perlin2d(float x, float y, float freq, int depth)
{
    float xa = x * freq;
    float ya = y * freq;
    float amp = 1.0;
    float fin = 0;
    float div = 0.0;

    int i;
    for (i = 0; i < depth; i++)
    {
        div += 256 * amp;
        fin += noise2d(xa, ya) * amp;
        amp /= 2;
        xa *= 2;
        ya *= 2;
    }

    return fin / div;
}
