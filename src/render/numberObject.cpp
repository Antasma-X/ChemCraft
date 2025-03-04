#include "numberObject.h"

NumberObject::NumberObject(std::vector<GLfloat> vertices, int number){

    if(!((number<=8 &&number>=1)||(number>=-8&&number<=-1))){
        throw std::runtime_error("Invalid Number");
    }
    if(vertices.size()!=16){
        throw std::invalid_argument("Vertices are Invalid");
    }
    this->number=number;

    if(number>0){
        texture=Texture("../Assets/numberAtlasBlue.png");
    }
    else if(number<0){
        texture=Texture("../Assets/numberAtlasRed.png");
    }
    else{
        throw std::runtime_error("Invalid Number");
    }
 

    float h=std::abs(number)<5?0.5f:0.0f;
    float w=std::abs(number)%5;
    Vertices={
        vertices[0],vertices[1],w*0.2f,h+0.0f,
        vertices[2],vertices[3],w*0.2f,h+0.5f,
        vertices[4],vertices[5],(w+1)*0.2f,h+0.5f,
        vertices[6],vertices[7],(w+1)*0.2f,h+0.0f,
    };
    
    std::vector<GLuint> Indices={
        0,1,2,
        2,3,0
    };

    shaderProgram=shaders["number"];

    vao=VAO();
    vao.Bind();
    vbo=VBO(Vertices);
    ebo=EBO(Indices);

    vao.LinkVBO(vbo,0,2,GL_FLOAT,4*sizeof(GLfloat),0);
    vao.LinkVBO(vbo,1,2,GL_FLOAT,4*sizeof(GLfloat),(void*)(2*sizeof(GLfloat)));

    vbo.UnBind();
    vao.UnBind();
    ebo.UnBind();
}

void NumberObject::Render(){
    shaderProgram.Activate();
    vao.Bind();
    texture.BindAndSetTexUnit(shaderProgram,"ourTexture");

    glDrawElements(GL_TRIANGLES, ebo.noOfIndices, GL_UNSIGNED_INT, 0);

    vao.UnBind();
    shaderProgram.Deactivate(); 
    texture.UnBind();
}

void NumberObject::Destroy(){
    vao.Delete();
    vbo.Delete();
    ebo.Delete();
    texture.Delete();
}