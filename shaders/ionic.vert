#version 330 core
layout(location = 0) in vec2 aPos;

out vec3 vertPos;        // world-space vertex position
flat out vec3 startPos;  // start of the bond
flat out vec3 bondDir;   // normalized bond direction
out float t;             // 0 → 1 across bond for gradient

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

void main() {
    vec4 worldPos = model * vec4(aPos, 0.0, 1.0);
    vertPos = worldPos.xyz;

    // first vertex sets startPos
    if (gl_VertexID == 0) {
        startPos = worldPos.xyz;
    }
    // second vertex sets bondDir
    if (gl_VertexID == 1) {
        vec4 worldStart = model * vec4(-0.5, 0.0, 0.0, 1.0);
        vec4 worldEnd   = model * vec4( 0.5, 0.0, 0.0, 1.0);
        bondDir = normalize(worldEnd.xyz - worldStart.xyz);
    }

    t = aPos.x + 0.5; // [0..1] along X
    gl_Position = proj * view * worldPos;
}
