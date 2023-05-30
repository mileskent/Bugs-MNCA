#version 120
uniform sampler2D texture;
uniform float resolution;

float get(float x, float y)
{
    return float(texture2D(texture, (gl_TexCoord[0].xy + vec2(x, y)/resolution)).b);
}

void main(void)
{
    int r = 1;
    float a = 0;
    for (int x = -r; x <= r; r++)
    {
        for (int y = -r; y <= r; y++)
        {
            a += get(x, y);
        }
    }
    a /= 9;
    gl_FragColor = vec4(a, a, a, 1.0);
}