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
#include "bondObject.h"
 
class Element; 

class ElementObject{

    //A map mapping all Elements to its element object
    static std::map<Element*,ElementObject*> elementObjects;

    //A map mapping dative objects to the electron objects it's in between
    static std::map<ElectronObject*,std::array<ElectronObject*,2>> dativeToElectrons;

    //A map mapping electron and dative objects to its element object
    static std::map<ElectronObject*,ElementObject*> electronOrDativeToElementObject;

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
    std::vector<GLfloat> vertices;

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

    //Shader for the glow surrounding element when selected or hovered
    Shader glowShaderProgram;

    //Position vector of center of element in world space
    glm::vec2 position;

    //Model Matrix of Element. Ngl never understood
    glm::mat4 model;
 
    //Width of the texture
    GLfloat width;
 
    //Z index used to placed element object above other objects when selected
    GLfloat zIndex;

    //true if selected, false if not. Takes precedences over hovering. if true, glow shader is used with selection amount of glow
    bool isSelected;

    //true if hovered over, false if not. if true, glow shader is used with hover amount of glow
    bool isHovered;

    //Electrons array. Depending on how many there are some will be invisible. Goes through same order as vertices. Bottom Left,Top Left,Top Right,Bottom Right
    std::array<ElectronObject,8> electrons; 

    //Datives Array. All invisible. Used to select and create dative bonds
    std::array<ElectronObject,4> datives;

    //Charge Object for element at top right
    ChargeObject charge;

    //Electron shifting variables
    float electronAnimationProgress=0.0f;

    bool isShifting=false;

    int shiftingFrom=-1;

    int shiftingTo=-1;

    float shiftTimer=0.0f;

    glm::vec2 shiftStartPos=glm::vec2(0.0f);

    glm::vec2 shiftEndPos=glm::vec2(0.0f);

    double lastShiftUpdateTime=0.0; 

    //Generates Electron Objects. Some Electrons will be invisible for valency
    void generateElectrons();

    //Generate Dative Objects. These Objects will be used to make dative bonds
    void generateDatives();

    //Generate Charge Object so it spawns on the top right corner of the element
    void generateCharge();

    //Called by ElementObject::Render() to update any electrons that are shifting around. Ngl used chatgpt a lot for this when i started seeing the word bezier curves
    void updateElectronShift();

    public:
        //Not Allowed
        ElementObject(const ElementObject&) = delete;
        ElementObject& operator=(const ElementObject&) = delete;
        
        /*
        Constructor for Element Object

        Takes in a vector(x,y) which is the center of the object in world space

        Takes in pointer to element being rendered

        Throws std::invalid_argument("Vertices are Invalid") if invalid vertices are passed in
        Throws std::runtime_error("Electron Generation went Wrong") when Electrons are not generated properly
        Throws std::runtime_error("Dative Generation went Wrong") when Datives are not generated properly
        */
        ElementObject(glm::vec2 pos, Element* el);

        // Move constructor and assignment
        ElementObject(ElementObject&& other) noexcept;
        ElementObject& operator=(ElementObject&& other) noexcept;

        /*
        Destructor for Element Object

        Destroys Element associated with the object and the vao stuff
        Electrons, datives and charges are destroyed automatically i think
        */
        ~ElementObject();

        //Used by Render to render element
        void render();

        //Moves elementObject and its electrons, datives and chargeObject by delta passed in
        void move(glm::vec2 delta);
    
        //Checks if elementObject covers the world position passed in 
        bool contains(glm::vec2 pos);

        //Checks if chargeObject that elementObject has covers world position passed in
        bool chargeObjectContains(glm::vec2 pos);
 
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
        Both electrons passed in must belong to the elementObject
        The first electron passed in will be shifted in position to the second electron passed in
        If the second electron is opaque then that electron will be shifted to the next electron counter clockwise
        The cycle goes on until the transparent electron is filled

        I tried making it a Recursive function but i didnt want everyting to happen at once
        */
        void shiftElectronToNewElectron(ElectronObject* electron,ElectronObject* otherElectron);

        /* 
        Based on the element owned by the ElementObject
        It updates the properties of the element such as its charge and electrons
        */
        void update();

        //Returns Element associated with this Element Object
        Element* getElement();

        //Returns postion of this Element Object
        glm::vec2 getPosition();
        
        //Returns Vector of all electron positions
        std::vector<glm::vec2> getElectronPositions();

        //Returns Vector of all dative positions
        std::vector<glm::vec2> getDativePositions();

        //Returns Charge Object position
        glm::vec2 getChargePosition();

        //Returns the original position on the elementObject of the electron or dative passed in 
        glm::vec2 getOriginalElectronOrDativePosition(ElectronObject* electron);

        //Returns a vector of electron objects on the world coordinates passed in. I know that only one electron should ideally be returned but i still wanted a vector cause a lot of my app's behaviour is based on vectors and sets
        std::vector<ElectronObject*> getElectronObjectsOn(glm::vec2 mousePos);

        //Returns a vector of dative objects on the world coordinates passed in. I know that only one dative should ideally be returned but i still wanted a vector cause a lot of my app's behaviour is based on vectors and sets
        std::vector<ElectronObject*> getDativeObjectsOn(glm::vec2 mousePos);

        //Returns map of elements associated with their element objects. Used in Render mainly
        static std::map<Element*,ElementObject*> getAllElementObjects();

        //Returns array of 2 electron objects the dative object passed in is in between
        static std::array<ElectronObject*,2> getElectronsOfDative(ElectronObject* dative);

        //Returns element object the electron object passed in belongs to
        static ElementObject* getElementObjectOfElectronOrDative(ElectronObject* electron);
};
#endif 