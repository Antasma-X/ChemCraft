#include "camera.h"

Camera* camera = nullptr;

Camera::Camera(){ 
    position={0.0f,0.0f};
    zoom=1.0f;

    screenWidth=windowWidth;
    screenHeight=windowHeight;
}

glm::mat4 Camera::GetProj(){
    return glm::ortho(0.0f,screenWidth,screenHeight,0.0f,-1.0f,1.0f);
} 

glm::mat4 Camera::GetView(){
    return glm::scale(glm::translate(glm::mat4(1.0f),glm::vec3(-position,0.0f)),glm::vec3(zoom,zoom,1.0f));
}

glm::mat4 Camera::GetVP(){
    return GetProj()*GetView();
}

void Camera::Move(glm::vec2 movement) {
   position+=zoom*movement;
}

void Camera::Zoom(float factor) {
    zoom = std::clamp(static_cast<float>(zoom*factor), minZoom, maxZoom);
}

void Camera::Resize(float newWidth, float newHeight) {
    screenWidth = newWidth;
    screenHeight = newHeight;
}

glm::vec2 Camera::GetCurrentPosition(){
    return position; 
}

float Camera::GetCurrentZoom(){ 
    return zoom; 
}

 