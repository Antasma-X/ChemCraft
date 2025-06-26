#include "chargeObject.h"


ChargeObject::ChargeObject(glm::vec2 position,int number){

    try{
        //fix vertices
        numberObj=NumberObject(position,number);
    }
    catch(std::invalid_argument& e){
        throw;
    }

    glm::vec2 signPosition={
        position[0]+numWidth/2+signLengt(h)/2,position[1]
    };

    bool isPositive;
    if(number>0){
        isPositive=true;
    }
    else{
        isPositive=false;
    }

    try{
        signObj=SignObject(signPosition,isPositive);
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