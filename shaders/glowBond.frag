#version 330 core
in vec2 localPos;
out vec4 FragColor;

uniform float glow;

void main() {
    float halfHeight = 0.5;        // Bond is a horizontal bar in local space
    float ringEdge = 0.3;          // inner radius of the glow ring
    float glowSoftness = 0.2;      // how far the glow fades outward
    vec3 glowColor = vec3(1.0);    // white glow

    float dist = abs(localPos.y);  // distance from bond center vertically

    // Make the center transparent, glow as you move away from edge
    float alpha = smoothstep(ringEdge, ringEdge + glowSoftness, dist);
    alpha *= glow;

    FragColor = vec4(glowColor, alpha);
}
