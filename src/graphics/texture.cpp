#include "texture.h"

Texture::Texture(std::string imageFilePath){

    int width,height,noColorChannels;
    // stbi_set_flip_vertically_on_load(true);
    //replaced 0 with rgba
    unsigned char* image= stbi_load(imageFilePath.c_str(),&width,&height,&noColorChannels,STBI_rgb_alpha);

    if (!image) {
        error->Push("Failed to load texture: "+imageFilePath);
        std::cerr << "Failed to load texture: " << imageFilePath << std::endl;
        return;
    }
    
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
    glGenerateMipmap(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);
    stbi_image_free(image);
}

void Texture::Bind(){
    glBindTexture(GL_TEXTURE_2D, texture);
}

void Texture::UnBind(){
    glBindTexture(GL_TEXTURE_2D,0);
}

void Texture::BindAndSetTexUnit(Shader& shader, const char* uniform){
    //for now no unit
    glActiveTexture(GL_TEXTURE0); 
    glBindTexture(GL_TEXTURE_2D, this->texture);  

    GLuint texUni=glGetUniformLocation(shader.shaderProgram,uniform);
    shader.Activate();
    glUniform1i(texUni,0);

}

void Texture::Delete(){
    glDeleteTextures(1,&texture);
}