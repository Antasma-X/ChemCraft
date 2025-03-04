#ifndef SHADER_H
#define SHADER_H

#include "StdLibDependencies.h"
#include "GUIDependencies.h"

struct Shader{

    //ID of shader
    GLuint shaderProgram;

    //Because Errors
    Shader()=default;

    /*
    Creates shader using vertex shader file path anf fragment shader filepath passed in

    Throws std::runtime_error("Vertex Shader Could not compile") when vertex shader does not compile
    Throws std::runtime_error("Fragment Shader Could not compile") when fragment shader does not compile
    Throws std::runtime_error("Shader Could not compile") when shader does not compile

    Pass in: Vertex Shader File Path
           : Fragment Shader File Path
    */
    Shader(std::string vertShaderFilePath,std::string fragShaderFilePath);

    //Activates Shader
    void Activate();

    //Deactivates Shader
    void Deactivate();

    //Destroys Shader
    void Delete();

    private:

        //Gets the shader info from the file pass in as a string
        static std::string getShaderFromFile(std::string filePath);

};

#endif 