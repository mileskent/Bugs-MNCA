#version 120
uniform sampler2D texture;
uniform float zoom;
uniform vec2 offset;

vec4 OFF = vec4(.0694, .0847, .123, 1.0);
vec4 ON = vec4(.2235, .2823, .4039, 1.0);

void main(void)
{
    vec2 UV=gl_TexCoord[0].xy-vec2(.5);
    UV/=zoom;
    UV+=(offset);
    vec4 fin = texture2D(texture,UV);
    (fin == vec4(0.0, 0.0, 0.0, 1.0)) ? fin = OFF : fin = ON;
    gl_FragColor = fin;
}