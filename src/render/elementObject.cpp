#include "elementObject.h"

std::map<Element*,ElementObject*> ElementObject::elementObjects={};

ElementObject::ElementObject(std::vector<GLfloat> vertices, Element* el){

    if(vertices.size()!=16){
        throw std::invalid_argument("Vertices are Invalid");
    }
 
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    element=el;
    Vertices=vertices;
    std::vector<GLuint> Indices={
        0,1,2,
        2,3,0
    };
 
    shaderProgram=shaders["element"];

    vao=VAO();
    vao.Bind();
    vbo=VBO(Vertices);
    ebo=EBO(Indices);
 
    vao.LinkVBO(vbo,0,2,GL_FLOAT,4*sizeof(GLfloat),0);
    vao.LinkVBO(vbo,1,2,GL_FLOAT,4*sizeof(GLfloat),(void*)(2*sizeof(GLfloat)));

    vbo.UnBind();
    vao.UnBind();
    ebo.UnBind();

    texture=Texture(elementFilePath1+std::to_string(el->getAtomicNumber())+elementFilePath2);

    elementObjects[element]=this;

    try{
        GenerateElectrons();
        GenerateDatives();
        GenerateCharge();
    }
    catch(std::runtime_error& e){
        throw;
    }
}

void ElementObject::GenerateElectrons(){
    int n=element->getNumberOfValenceElectrons();
    GLfloat transparency=1.0f;

    for(int i=0;i<8;i++){
        std::vector<GLfloat> electronVertices;

        if(i==n){
            transparency=0.0f;
        }

        if(i==0){
            electronVertices={
               Vertices[0]-electronDistanceDirect,Vertices[1]+electronDistanceAdjust ,transparency
            };

        }
        else if(i==1){
            electronVertices={
                Vertices[8]+electronDistanceDirect,Vertices[9]-electronDistanceAdjust ,transparency
            };         
        }
        else if(i==2){
            electronVertices={
                Vertices[4]+electronDistanceAdjust,Vertices[5]+electronDistanceDirect ,transparency
            };         
        }
        else if(i==3){
            electronVertices={
                Vertices[12]-electronDistanceAdjust,Vertices[13]-electronDistanceDirect ,transparency
            };         
        }
        else if(i==4){
            electronVertices={
                Vertices[4]-electronDistanceDirect,Vertices[5]-electronDistanceAdjust ,transparency
            };
        }
        else if(i==5){
            electronVertices={
                Vertices[8]-electronDistanceAdjust,Vertices[9]+electronDistanceDirect ,transparency
            };         
        }
        else if(i==6){
            electronVertices={
                Vertices[12]+electronDistanceDirect,Vertices[13]+electronDistanceAdjust ,transparency
            };         
        }
        else if(i==7){
            electronVertices={
                Vertices[0]+electronDistanceAdjust,Vertices[1]-electronDistanceDirect ,transparency
            };
        }
        else{
            throw std::runtime_error("Electron Generation went Wrong");
        }

        //removed new for now
        ElectronObject electron= ElectronObject(electronVertices);
        electrons[i]=electron;
    }
}

void ElementObject::GenerateDatives(){
    for(int i=0;i<4; i++){
        std::vector<GLfloat> dativeVertices;

        if(i==0){
            dativeVertices={
                Vertices[0]-electronDistanceDirect,(Vertices[1]+Vertices[5])/2,0.0f
            };
        }
        if(i==1){
            dativeVertices={
                (Vertices[4]+Vertices[8])/2,Vertices[5]+electronDistanceDirect,0.0f
            };
        }
        if(i==2){
            dativeVertices={
                Vertices[8]+electronDistanceDirect,(Vertices[9]+Vertices[13])/2,0.0f
            };
        }
        if(i==3){
            dativeVertices={
                (Vertices[12]+Vertices[0])/2,Vertices[13]-electronDistanceDirect,0.0f
            };
        }
        else{
            throw std::runtime_error("Dative Generation went Wrong");
        }
        ElectronObject dative= ElectronObject(dativeVertices);
        datives[i]=dative;
    }
} 

void ElementObject::GenerateCharge(){
    std::vector<GLfloat> chargeVertice={
        Vertices[8],Vertices[9]
    };
    charge=ChargeObject(chargeVertice,element->getCharge());
}

void ElementObject::Render(){

    shaderProgram.Activate();
    vao.Bind();
    texture.BindAndSetTexUnit(shaderProgram,"ourTexture");

    glDrawElements(GL_TRIANGLES, ebo.noOfIndices, GL_UNSIGNED_INT, 0);

    vao.UnBind();
    shaderProgram.Deactivate(); 
    texture.UnBind();

    for(auto electron:electrons){
        electron.Render();
    }

    for(auto dative:datives){
        dative.Render();
    }

    charge.Render();
}