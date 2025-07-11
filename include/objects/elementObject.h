#ifndef ELEMENTOBJECT_H
#define ELEMENTOBJECT_H

#include "GUIDependencies.h"
#include "StdLibDependencies.h"

#include "chemistry.h"
#include "graphics.h"
#include "utils.h"

#include "texture.h"

#include "electronObject.h"
#include "chargeObject.h"
 
class Element;

struct ElementObject{
    //Element being rendered
    Element* element; 

    /*
    Vertices

    Structure:
    There are 4 vertices
    They represent the 4 corners of rectangle

    1)Bottom Left
    2)Top Left
    3)Top Right
    4)Bottom Right

    Each vertice has x and y coordinate
    {
        x,y,0.0,0.0
        x,y,1.0,0.0
        x,y,1.0,1.0
        x,y,0.0,1.0
    }
    */
    std::vector<GLfloat> Vertices;

    //VAO for Element
    VAO vao;

    //VBO for Element
    VBO vbo;

    //EBO for Element. The indices are predefined in the constructor
    EBO ebo;

    //Texture for Element
    Texture texture;

    //Shader for Element
    Shader shaderProgram; 

    //Position vector of center of element in world space
    glm::vec2 position;

    //Model Matrix of Element. Ngl never understood
    glm::mat4 model;

    //width of the texture
    GLfloat width;

    //Electrons array. Depending on how many there are some will be invisible. Goes through same order as vertices. Bottom Left,Top Left,Top Right,Bottom Right
    std::array<ElectronObject,8> electrons; 

    //Datives Array. All invisible. Used to select and create dative bonds
    std::array<ElectronObject,4> datives;

    //Charge Object for element at top right
    ChargeObject charge;

    //A map mapping Element to its element object
    static std::map<Element*,ElementObject*> elementObjects;

    /*
    Constructor for Element Object

    Takes in a vector(x,y) which is the center of the object in world space

    Takes in pointer to element being rendered

    Throws std::invalid_argument("Vertices are Invalid") if invalid vertices are passed in
    Throws std::runtime_error("Electron Generation went Wrong") when Electrons are not generated properly
    Throws std::runtime_error("Dative Generation went Wrong") when Datives are not generated properly
    */
    ElementObject(glm::vec2 position, Element* el);

    //Used by Render to render element
    void Render();

    std::vector<glm::vec2> getElectronPositions();
    std::vector<glm::vec2> getDativePositions();
    glm::vec2 getChargePosition();

    void Move(glm::vec2 delta);

    private:
        //Generates Electron Objects. Some Electrons will be invisible for valency
        void GenerateElectrons();

        //Generate Dative Objects. These Objects will be used to make dative bonds
        void GenerateDatives();

        //Generate Charge Object so it spawns on the top right corner of the element
        void GenerateCharge();
     
};
#endif 