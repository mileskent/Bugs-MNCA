#version 120
uniform sampler2D texture;
uniform float zoom;
uniform vec2 offset;
uniform float resolution;

float get(float x, float y)
{
    return float(texture2D(texture, (gl_TexCoord[0].xy + vec2(x, y)/resolution)).b);
}

void main(void)
{
    vec2 UV=gl_TexCoord[0].xy - vec2(.5);
    UV /= zoom;
    UV += offset;

    vec4 fin = texture2D(texture,UV);
    (fin == vec4(0.0, 0.0, 0.0, 1.0)) ? fin = vec4(.0694, .0847, .123, 1.0) : fin = vec4(.2235, .2823, .4039, 1.0);
    gl_FragColor = fin;
}