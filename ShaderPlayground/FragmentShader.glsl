#version 330
out vec4 FragColor;
in vec3 outColor;
in vec3 outPos;

uniform float seed;

float pow2(float a)
{
    return a * a;
}

float distance(vec2 a, vec2 b)
{
    return sqrt(pow2(a.x - b.x) + pow2(a.y - b.y));
}

void main()
{
    float x = outPos.x;
    float y = outPos.y + 1 / 8.;
    
    const float r = 5 / 8.;
    float theta = seed;
    const float pi = 3.1415926f;
    
    vec2 rPoint = vec2(r * cos(theta), r * sin(theta));
    vec2 gPoint = vec2(r * cos(theta + 2 * pi / 3), r * sin(theta + 2 * pi / 3));
    vec2 bPoint = vec2(r * cos(theta + 4 * pi / 3), r * sin(theta + 4 * pi / 3));
    
    vec2 point = vec2(x, y);
    float fR = 1 - distance(point, rPoint) / r / 2;
    float fG = 1 - distance(point, gPoint) / r / 2;
    float fB = 1 - distance(point, bPoint) / r / 2;
   
    FragColor = vec4(fR, fG, fB, 1);
}
