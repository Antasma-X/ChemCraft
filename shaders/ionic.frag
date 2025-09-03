#version 330 core
out vec4 FragColor;

in vec3 vertPos;
flat in vec3 startPos;
flat in vec3 bondDir;
in float t;



void main() {
    float u_dashSize=10;
    float u_gapSize=10;
    // distance along the bond axis
    float dist = dot(vertPos - startPos, bondDir);

    float patternLength = u_dashSize + u_gapSize;
    float cycle = fract(dist / patternLength);

    if (cycle > u_dashSize / patternLength)
        discard;

    // blue → red gradient
    vec3 color = mix(vec3(0.0, 0.0, 1.0),
                     vec3(1.0, 0.0, 0.0),
                     clamp(t, 0.0, 1.0));

    FragColor = vec4(color, 1.0);
}
