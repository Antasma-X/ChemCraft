#include "camera.h"

Camera::Camera(){
    position={0.0f,0.0f};
    zoom=1.0f;
    screenWidth=windowWidth;
    screenHeight=windowWidth;
    view=glm::mat4(1.0f);
    proj=glm::ortho(0.0f,screenWidth/zoom,0.0f,screenHeight/zoom);
}

void Camera::UpdateProj(){
    proj=glm::ortho(0.0f,screenWidth/zoom,0.0f,screenHeight/zoom);
}

void Camera::UpdateView(){
    view=glm::translate(glm::mat4(1.0f),glm::vec3(-position,0.0f));
    view=glm::scale(view,glm::vec3(zoom,zoom,1.0f));
}