#version 330 core

in vec2 localPos;
in float transparency;

out vec4 FragColor;

uniform int hover;

void main() {
    float dist=length(localPos);
    if (dist > 1.0) discard;

    if(hover==1){
        //This is very hacky since electronGlow wasnt working
        float innerRadius = 0.7;
        float outerRadius = 0.9;

        if(dist>outerRadius||dist<innerRadius) discard;

        FragColor = vec4(1.0, 1.0, 1.0, 1.0); 
    }
    else{
        FragColor = vec4(1.0, 1.0, 1.0, transparency); 
    }
}