#ifndef BONDCOVALENT_H
#define BONDCOVALENT_H

#include "GUIDependencies.h"
#include "StdLibDependencies.h"

#include "elementObject.h"
#include "graphics.h"
#include "utils.h"

class BondObject{

    /*
    Static Vector to get all bond objects from
    */
    static std::vector<BondObject*> bonds;

    //The 2 elements being bonded in same order as ends
    std::vector<ElementObject*> elements;

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
    std::vector<GLfloat> vertices;

    //VAO for Bond
    VAO vao;

    //VBO for Bond
    VBO vbo;
 
    //EBO for Bond. The indices are predefined in constructor for bond
    EBO ebo;

    //Shader for Bond. Uses covalent, dative, ionic shader depending on type of bond. Shader makes first vertex red and second vertex white when dative and makes line dotted when ionic
    Shader shaderProgram;

    //Shader for the glow surrounding bond when selected or hovered
    Shader glowShaderProgram;

    /*
    Ends
 
    Structure:
    There are 2 vertices
    The first vertice is red
    The last vertice is white

    First vertice belong to side giving electrons if thee is a side giving electrons

    Each vertice has x and y coordinate
    {
        x,y
        x,y
    }

    These vertices must be in world space, since the bond is basically just connecting 2 points
    */
    std::vector<glm::vec2> ends;

    //Model Matrix of Bond. Ngl never understood
    glm::mat4 model;

    //Z index used to placed bond object above other objects when selected
    GLfloat zIndex;

    //true if selected, false if not. Takes precedences over hovering. if true, glow shader is used with selection amount of glow
    bool isSelected;

    //true if hovered over, false if not. if true, glow shader is used with hover amount of glow
    bool isHovered; 

    /*
    Type of Bond
    0 means covalent
    1 means ionic
    2 means dative

    The first vertice always gives donating atom 
    */ 
    int type;
 
    //Updates model matrix according to ends
    void updateModel();

    public:
        //Not Allowed
        BondObject(const BondObject&) = delete;
        BondObject& operator=(const BondObject&) = delete;
        
        /*
        Constructor for Bond Object

        Pass in 2 vertices each with x,y and bond type
        These vertices are in world space

        First vertices belong to side giving electrons 

        0 means covalent
        1 means ionic
        2 means dative 

        Note: The reason why i didnt use -1 and -2 is cause shader doesnt work that way
    
        Throws std::invalid_argument("Vertices are Invalid") if invalid vertices are passed in
        Throws std::invalid_argument("Invalid Bond Type") if invalid bond type is passed in
        */
        BondObject(std::vector<glm::vec2> ends,std::vector<ElementObject*> els,int type);

        // Move constructor and assignment
        BondObject(BondObject&& other) noexcept;
        BondObject& operator=(BondObject&& other) noexcept;
        
        //Deletes VAO,VBO,EBO and removes from bonds vector
        ~BondObject();

        //Used by Render to render bond
        void render();

        /*
        Moves bond by delta passed in
        It moves the end whose index is passed in. i must be 0 or 1
        */
        void move(glm::vec2 delta, int i);

        //Checks if bondObject covers the world position passed in 
        bool contains(glm::vec2 pos);

        /*
        Pass in: true if selecting
                 false if unselecting

        Note: passing in false or true twice in a row is fine

        This causes a selection level glow to surround the element by allowing the glowShader to be used and increases the z index to Z_SELECTED
        Takes precedence over hover in any behaviour
        */
        void select(bool b);

        /*
        Pass in: true if hovering
                 false if unhovering

        Note: passing in false or true twice in a row is fine

        This causes a hover level glow to surround the element by allowing the glowShader to be used and increases the z index to Z_HOVERED
        */
        void hover(bool b);

        /*
        Pass in: Z Index you want bond object to have
        Changes Z index of bond object to value passed in. Used to put the bond object in front or below other objects
        */
        void shift(GLfloat i);

        //Returns type of bond
        int getType();

        //Returns elements that this bond object is bonding
        std::vector<ElementObject*> getElements();

        //Returns vector of all bond objects
        static std::vector<BondObject*> getAllBondObjects();
};  
#endif  