#ifndef CAMERA_H
#define CAMERA_H

#include "StdLibDependencies.h"
#include "GUIDependencies.h"
#include "utils.h"

struct Camera{ 

    //Basically world coordinate of center of screen
    glm::vec2 position;
 
    //zoom
    float zoom;

    //Screen width and height. They're used for the view and proj matrices since they depend on these
    float screenWidth;
    float screenHeight;

    /*
    Constructor for Camera
    Sets zoom, position and screen sizes
    */
    Camera();

    //Gets Projection Matrix
    glm::mat4 GetProj();

    //Gets View Matrix
    glm::mat4 GetView();

    //Gets Projection Matrix * View Matrix
    glm::mat4 GetVP();

    /*
    Called by CursorPosCallback to move the camera atound depending on zoom and the vector passed in
    It moves by the amount of x and y passed in movmement*zoom

    Pass In: Amount to be moved as a vec
    */
    void Move(glm::vec2 movement);

    //Zooms by amount of factor passed in
    void Zoom(float factor);

    //Changes screenWidth and screenHeight with values passed in. Called by FrameSizeCallback to change whwnever screen is resized
    void Resize(float newWidth, float newHeight);

    //Returns position of camera
    glm::vec2 GetCurrentPosition();
 
    //Returns current zoom factor
    float GetCurrentZoom();
    
};

extern Camera* camera;
#endif