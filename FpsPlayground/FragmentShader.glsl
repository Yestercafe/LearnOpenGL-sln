#version 330
out vec4 FragColor;

in vec2 TexCoord;
in vec3 outPos;

uniform sampler2D Texture1;
uniform sampler2D Texture2;
uniform float seed;

float distance(vec2 a, vec2 b) {
    return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}

float bound(float a) {
    if (a > 1) return 1;
    else if (a < 0) return 0;
    else return a;
}

void main()
{
    float x = outPos.x + 0.5;
    float y = outPos.y + 0.5;
    
    float radius = 1;
    
    vec2 center1, center2;
    if (0 <= seed && seed < 0.5) {
        center1 = vec2(seed * 2 * (1 + radius) - radius, 0);
        center2 = vec2(0, seed * 2 * (1 + radius) - radius);
    }
    else {
        center1 = vec2(1, (seed - 0.5) * 2 * (1 + radius));
        center2 = vec2((seed - 0.5) * 2 * (1 + radius), 1);
    }
    
    float dist = distance(center1, center2);
    
    vec2 point = vec2(x, y);
    float f1 = bound(1 - distance(point, center1) / radius);
    float f2 = bound(1 - distance(point, center2) / radius);

    FragColor = mix(texture(Texture1, TexCoord), texture(Texture2, TexCoord), 0.4) * vec4(0.6, 0.6, 0.6 + 0.4 * (f1 + f2), 1);
}
