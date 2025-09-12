#version 330 core
in vec2 localPos;
out vec4 FragColor;

uniform float glow;

float roundedBoxSDF(vec2 p, vec2 b, float r) {
    vec2 q = abs(p) - b + vec2(r);
    return length(max(q, 0.0)) - r;
}
  
void main() {
    vec2 halfBoxSize = vec2(0.5, 0.5);
    float cornerRadius = 0.1;
    float edgeThickness = 0.001;
    float glowSoftness = 0.05;

    vec3 glowColor = vec3(1.0); // white glow

    float dist = roundedBoxSDF(localPos, halfBoxSize - vec2(cornerRadius), cornerRadius);

    // Alpha controlled by glow intensity
    float baseAlpha = smoothstep(edgeThickness + glowSoftness, edgeThickness, abs(dist));
    float alpha = clamp(glow * baseAlpha, 0.0, 1.0);

    FragColor = vec4(glowColor, alpha);
}


