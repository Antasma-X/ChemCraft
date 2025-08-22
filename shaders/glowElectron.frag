#version 330 core
in vec2 localPos;
out vec4 FragColor;

uniform float glow;

void main() {
    float coreRadius = 0.3;        // where the ring starts
    float glowSoftness = 0.05;     // how wide the glow fades outward
    vec3 glowColor = vec3(0.2, 0.8, 1.0); // glow color (light blue)

    float dist = length(localPos);

    // Fade in the glow as you move away from the core radius
    float alpha = smoothstep(coreRadius, coreRadius + glowSoftness, dist);
    alpha *= glow;

    FragColor = vec4(glowColor, alpha);
}
 