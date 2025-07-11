#ifndef TEXTURE_H
#define TEXTURE_H

#include "GUIDependencies.h"
#include "StdLibDependencies.h"

#include "shader.h"
#include "utils.h"

struct Texture{
    //ID of Texture
    GLuint texture;

    //Because Errors
    Texture()=default;

    //Creates Texture using imageilepath passed in and Unbinds texture
    Texture(std::string imageFilePath);

    //Binds Texture
    void Bind();

    //Unbinds Texture
    void UnBind();

    //Does the unit stuff ngl never understood this. Does not unbind shader and texture
    void BindAndSetTexUnit(Shader& shader, const char* uniform);

    //Destroys Texture
    void Delete();

};


#endif