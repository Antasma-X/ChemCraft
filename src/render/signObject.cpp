#include "signObject.h"

GLuint SignObject::colorLocation;
SignObject::SignObject(std::vector<GLfloat> initialVertices,bool isPositive){

    if(initialVertices.size() !=0){
        throw std::invalid_argument("Vertices are Invalid");
    }

    this->isPositive=isPositive;
    std::vector<GLuint> Indices;

    if(isPositive){
        Vertices={
            initialVertices[0],initialVertices[1], 1,
            initialVertices[0]+signLength,initialVertices[1], 1,

            (initialVertices[0]+signLength+initialVertices[0])/2,initialVertices[1]+signLength, 1,
            (initialVertices[0]+signLength+initialVertices[0])/2,initialVertices[1]-signLength, 1
        };

        
        Indices={0,1,2,3};
    }
    else{
        Vertices={
            initialVertices[0],initialVertices[1], 0,
            initialVertices[0]+signLength,initialVertices[1], 0
        };
        
        Indices={0,1};
    }

    shaderProgram=shaders["sign"];

    vao=VAO();
    vao.Bind();
    vbo=VBO(Vertices);
    ebo=EBO(Indices);

    vao.LinkVBO(vbo,0,2,GL_FLOAT,2*sizeof(GLfloat),0);

    vbo.UnBind();
    vao.UnBind();
    ebo.UnBind();
}

void SignObject::Render(){
    shaderProgram.Activate();
    if(isPositive){
        glUniform3f(colorLocation,0.0f,0.0f,1.0f);
    }
    else{
        glUniform3f(colorLocation,1.0f,0.0f,0.0f);
    }
    vao.Bind();


    glLineWidth(signThickness);
    glDrawElements(GL_LINES, int(Vertices.size()/2), GL_UNSIGNED_INT, 0);

    vao.UnBind();
    shaderProgram.Deactivate();
}

void SignObject::Destroy(){
    vao.Delete();
    vbo.Delete();
    ebo.Delete();
}