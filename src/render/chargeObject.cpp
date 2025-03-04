#include "chargeObject.h"


ChargeObject::ChargeObject(std::vector<GLfloat> vertices,int number){

    try{
        //fix vertices
        numberObj=NumberObject(vertices,number);
    }
    catch(std::invalid_argument& e){
        throw;
    }

    std::vector<GLfloat> signVertices={
        vertices[4],(vertices[5]+vertices[7])/2
    };

    bool isPositive;
    if(number>0){
        isPositive=true;
    }
    else{
        isPositive=false;
    }

    try{
        signObj=SignObject(signVertices,isPositive);
    }
    catch(std::invalid_argument& e){
        throw;
    }
}

void ChargeObject::Render(){
    numberObj.Render();
    signObj.Render();
}

void ChargeObject::Destroy(){
    numberObj.Destroy();
    signObj.Destroy();
}