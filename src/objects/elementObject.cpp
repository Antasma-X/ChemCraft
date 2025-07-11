#include "elementObject.h"
#include <glm/gtx/string_cast.hpp>
std::map<Element*,ElementObject*> ElementObject::elementObjects={};

ElementObject::ElementObject(glm::vec2 position, Element* el){

    if(el->getSymbol().size()==1){
        width=elementSingleTextureWidth;
    }
    else if(el->getSymbol().size()==2){
        width=elementDoubleTextureWidth;
    } 
    else{
        throw std::runtime_error("Atomic Symbol is Incorrect");
    }     
    
    Vertices={
        -width/2,-elementTextureHeight/2,0.0,0.0,
        -width/2,elementTextureHeight/2,0.0,1.0,
        width/2,elementTextureHeight/2,1.0,1.0,
        width/2,-elementTextureHeight/2,1.0,0.0
    };

    element=el;
    std::vector<GLuint> Indices={
        0,1,2,
        2,3,0
    };

    this->position=position;
 
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

    model=glm::translate(glm::mat4(1.0f),glm::vec3(position,0.0f));
    
    elementObjects[element]=this;

    std::cout<<"sexx"<<std::endl;

    try{
        GenerateElectrons();
        GenerateDatives();
    std::cout<<element->getName()<<std::endl;

        if(element->getCharge()!=0)
        {
            GenerateCharge();
        }
        
    }
    catch(std::runtime_error& e){
        throw;
    } 
}  

void ElementObject::GenerateElectrons(){
    std::cout<<"sexx"<<std::endl;

    int n=element->getNumberOfValenceElectrons();
    GLfloat transparency=1.0f;

    for(int i=0;i<8;i++){
        glm::vec2 pos;

        if(i==n){
            transparency=0.0f;
        }

        if(i==0){
            pos={
               position[0] -width/2-electronDistanceDirect,position[1]-elementTextureHeight/2+electronDistanceAdjust 
            };

        }
        else if(i==1){
            pos={
                position[0]+ width/2+electronDistanceDirect,position[1]+elementTextureHeight/2-electronDistanceAdjust 
            };         
        }
        else if(i==2){
            pos={
                position[0]-width/2+electronDistanceAdjust,position[1]+elementTextureHeight/2+electronDistanceDirect 
            };         
        }
        else if(i==3){
            pos={
                position[0]+width/2-electronDistanceAdjust,position[1]-elementTextureHeight/2-electronDistanceDirect 
            };         
        }
        else if(i==4){
            pos={
                position[0]-width/2-electronDistanceDirect,position[1]+elementTextureHeight/2-electronDistanceAdjust 
            };
        }
        else if(i==5){
            pos={
                position[0]+width/2-electronDistanceAdjust,position[1]+elementTextureHeight/2+electronDistanceDirect 
            };         
        }
        else if(i==6){
            pos={
                position[0]+width/2+electronDistanceDirect,position[1]-elementTextureHeight/2+electronDistanceAdjust 
            };         
        }
        else if(i==7){
            pos={
                position[0]-width/2+electronDistanceAdjust,position[1]-elementTextureHeight/2-electronDistanceDirect 
            };
        }
        else{
            throw std::runtime_error("Electron Generation went Wrong");
        }

        //removed new for now
        std::cout<<"sexx"<<std::endl;

        ElectronObject electron= ElectronObject(pos,transparency);
        electrons[i]=electron;
        
    }

    std::cout<<"sexx"<<std::endl;
}

void ElementObject::GenerateDatives(){
    for(int i=0;i<4; i++){
        glm::vec2 pos;

        if(i==0){
            pos={
                position[0]-width/2-electronDistanceDirect,position[1]
            };
        }
        else if(i==1){
            pos={
                position[0],position[1]+elementTextureHeight/2+electronDistanceDirect
            };
        }
        else if(i==2){
            pos={
                position[0]+width/2+electronDistanceDirect,position[1]
            };
        }
        else if(i==3){
            pos={
                position[0],position[1]-elementTextureHeight/2-electronDistanceDirect
            };
        }
        else{
            throw std::runtime_error("Dative Generation went Wrong");
        }
        ElectronObject dative= ElectronObject(pos,0.0f);
        datives[i]=dative;
    }
} 
 
void ElementObject::GenerateCharge(){
    //idk why i dont divide by 2 but fine
    glm::vec2 chargePos={position[0]+width/2,position[1]-elementTextureHeight};
    charge=ChargeObject(chargePos,element->getCharge());
}

void ElementObject::Render(){

    shaderProgram.Activate();

    shaderProgram.SetMat4Uniform(model,"model");
    shaderProgram.SetMat4Uniform(camera->GetView(),"view");
    shaderProgram.SetMat4Uniform(camera->GetProj(),"proj");

//     //     shaderProgram.SetMat4Uniform(glm::mat4(1.0f),"view");
//     // shaderProgram.SetMat4Uniform(glm::mat4(1.0f),"proj");
//     std::cout<<"swhfbshbshvbsjgbvsjgv"<<std::endl;
//     glm::mat4 m = camera->GetView();   // or any mat4
//     std::cout << glm::to_string(m) << std::endl;

//     m = camera->GetProj();   // or any mat4
// std::cout << glm::to_string(m) << std::endl;

    vao.Bind();
    texture.BindAndSetTexUnit(shaderProgram,"ourTexture");

    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

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

    if(element->getCharge()!=0)
    {
        charge.Render();
    }
}

void ElementObject::Move(glm::vec2 delta){
    position+=delta;
    model=glm::translate(glm::mat4(1.0f),glm::vec3(position,0.0f));

    for(auto& electron:electrons){
        electron.Move(delta);
    }

    for(auto& dative:datives){
        dative.Move(delta);
    }

    if(element->getCharge()!=0)
    {
        charge.Move(delta);
    }
}


std::vector<glm::vec2> ElementObject::getElectronPositions(){

    std::vector<glm::vec2> pos;
    for(auto e: electrons)
    {
        pos.push_back(e.position);
    }

    return pos;
}
std::vector<glm::vec2> ElementObject::getDativePositions(){
    std::vector<glm::vec2> pos;
    for(auto dative: datives)
    {
        pos.push_back(dative.position);
    }
    return pos;
}

glm::vec2 ElementObject::getChargePosition(){
    GLfloat width;
    if(element->getSymbol().size()==1){
        width=elementSingleTextureWidth;
    }
    else if(element->getSymbol().size()==2){
        width=elementDoubleTextureWidth;
    } 

    return {position[0]+width/2,position[1]-elementTextureHeight};
}
 





// for(int i=0;i<8;i++){
//     std::vector<GLfloat> electronVertices;

//     if(i==n){
//         transparency=0.0f;
//     }

//     if(i==0){
//         electronVertices={
//            Vertices[0]-electronDistanceDirect,Vertices[1]+electronDistanceAdjust ,transparency
//         };

//     }
//     else if(i==1){
//         electronVertices={
//             Vertices[8]+electronDistanceDirect,Vertices[9]-electronDistanceAdjust ,transparency
//         };         
//     }
//     else if(i==2){
//         electronVertices={
//             Vertices[4]+electronDistanceAdjust,Vertices[5]+electronDistanceDirect ,transparency
//         };         
//     }
//     else if(i==3){
//         electronVertices={
//             Vertices[12]-electronDistanceAdjust,Vertices[13]-electronDistanceDirect ,transparency
//         };         
//     }
//     else if(i==4){
//         electronVertices={
//             Vertices[4]-electronDistanceDirect,Vertices[5]-electronDistanceAdjust ,transparency
//         };
//     }
//     else if(i==5){
//         electronVertices={
//             Vertices[8]-electronDistanceAdjust,Vertices[9]+electronDistanceDirect ,transparency
//         };         
//     }
//     else if(i==6){
//         electronVertices={
//             Vertices[12]+electronDistanceDirect,Vertices[13]+electronDistanceAdjust ,transparency
//         };         
//     }
//     else if(i==7){
//         electronVertices={
//             Vertices[0]+electronDistanceAdjust,Vertices[1]-electronDistanceDirect ,transparency
//         };
//     }
//     else{
//         throw std::runtime_error("Electron Generation went Wrong");
//     }

//     //removed new for now
//     ElectronObject electron= ElectronObject(electronVertices,transparency
    
    
//     );
//     electrons[i]=electron;
