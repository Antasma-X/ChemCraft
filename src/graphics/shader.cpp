#include "shader.h"

std::string Shader::getShaderFromFile(std::string filePath){
    std::ifstream file(filePath);
    if (!file.is_open()) {
        std::cout<<"bitv";
    }
    std::stringstream buffer;
    buffer << file.rdbuf(); 
    return buffer.str();
}


Shader::Shader(std::string vertShaderFilePath,std::string fragShaderFilePath){
    std::string vert=getShaderFromFile(vertShaderFilePath);
    std::string frag=getShaderFromFile(fragShaderFilePath);

    const char* vertSource = vert.c_str();
    const char* fragSource = frag.c_str();

    GLuint vertexShader=glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader,1,&vertSource,nullptr);
    glCompileShader(vertexShader);

    GLint success;
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char infoLog[1024];
        glGetShaderInfoLog(vertexShader, 1024, nullptr, infoLog);
        std::cerr << "VERTEX SHADER COMPILATION ERROR:\n" << infoLog << std::endl;
        throw std::runtime_error("Vertex Shader Could not compile");
    }

    GLuint fragmentShader=glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader,1,&fragSource,nullptr);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char infoLog[1024];
        glGetShaderInfoLog(fragmentShader, 1024, nullptr, infoLog);
        std::cerr << "FRAGMENT SHADER COMPILATION ERROR:\n" << infoLog << std::endl;
        throw std::runtime_error("Fragment Shader Could not compile");
    }

    shaderProgram=glCreateProgram();

    glAttachShader(shaderProgram,vertexShader);
    glAttachShader(shaderProgram,fragmentShader);
    glLinkProgram(shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    glGetShaderiv(shaderProgram, GL_COMPILE_STATUS, &success);
    if (!success) {
        char infoLog[1024];
        glGetShaderInfoLog(shaderProgram, 1024, nullptr, infoLog);
        std::cerr << " SHADER COMPILATION ERROR:\n" << infoLog << std::endl;
        throw std::runtime_error("Shader Could not compile");
    }
}

void Shader::Activate(){
    glUseProgram(shaderProgram);
}

void Shader::Deactivate(){
    glUseProgram(0);
}
void Shader::Delete(){
    glDeleteProgram(shaderProgram);
}

void Shader::SetMat4Uniform(glm::mat4 mat,const char* uniform){
    Activate();
    int loc=glGetUniformLocation(shaderProgram,uniform);
    glUniformMatrix4fv(loc,1,GL_FALSE,glm::value_ptr(mat));
}

void Shader::Set3fUniform(float R,float G,float B, const char* uniform){
    Activate();
    int loc=glGetUniformLocation(shaderProgram,uniform);
    glUniform3f(loc,R,G,B);
}