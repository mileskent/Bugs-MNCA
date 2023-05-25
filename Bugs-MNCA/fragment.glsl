#version 120
uniform sampler2D texture;
uniform float resolution;

int get(float x, float y)
{
    return int(texture2D(texture, (gl_TexCoord[0].xy + vec2(x, y)/resolution)).b);
}

void main(void)
{
    float sum;
    int size = 6;
    for (int x = -size; x <= size; x++)
    {
        for (int y = -size; y <= size; y++)
        {
            if (x != 0 && y != 0)
            {
                sum += get(x, y);
            }
        }
    }

    if( sum >= 0.0 &&  sum <=  33.0 ) { gl_FragColor = vec4(0.0, 0.0, 0.0, 1.0); }
    if( sum >=  34.0 &&  sum <=  45.0 ) { gl_FragColor = vec4(1.0, 1.0, 1.0, 1.0); }
    if( sum >=  58.0 &&  sum <= 121.0 ) { gl_FragColor = vec4(0.0, 0.0, 0.0, 1.0); }

    


}