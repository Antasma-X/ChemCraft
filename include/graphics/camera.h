#ifndef CAMERA_H
#define CAMERA_H

#include "StdLibDependencies.h"
#include "GUIDependencies.h"
#include "config.h"

struct Camera{
    glm::vec2 position;

    float zoom;
    float screenWidth;
    float screenHeight;

    glm::mat4 view;
    glm::mat4 proj;

    Camera();

    void UpdateProj();

    void UpdateView();
};

#endif