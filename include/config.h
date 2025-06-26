#ifndef CONFIG_H
#define CONFIG_H

#include "StdLibDependencies.h"
#include "GUIDependencies.h"
#include "shader.h"
#include "camera.h"
#include "json.hpp"
#include "UIGeneration.h"
#include "error.h"

class Error;
//have global classes sec
extern Error error;
//Window

    extern const char* windowName;
    extern ImVec4 windowColor; 
    extern int windowHeight;
    extern int windowWidth;
    extern int largeWindowHeight;

    //what can i sa im laz
    extern std::string fontFileString;
    extern const char* fontFile;

    extern const ImWchar ranges[]; 

    extern std::string molecularFormulaFontFileString; 
    extern const char* molecularFormulaFontFile; 

    extern double windowSmallFontSize; 
    extern double windowLargeFontSize; 

//Top Menu 
    extern std::string currentFile;
    extern ImVec4 topMenuButtonColor;
    extern ImVec4 topMenuHoveredButtonColor;
    extern ImVec4 topMenuActiveButtonColor;
    extern ImVec4 topMenuTextColor;

    extern ImVec4 fileNameColor;

    extern ImVec4 settingsColorPickersTextColor;
    extern ImVec4 settingsColorPickersBackgroundColor;
    extern ImVec4 settingsColorPickersTitleBarColor;
    extern ImVec4 settingsColorPickersActiveTitleBarColor;
    extern ImVec4 settingsColorPickersCollapsedTitleBarColor;

    extern ImVec4 openFilePopUpTextColor;
    extern ImVec4 openFilePopUpBackgroundColor;
    extern ImVec4 openFilePopUpTitleBarColor;
    extern ImVec4 openFilePopUpActiveTitleBarColor;
    extern ImVec4 openFilePopUpCollapsedTitleBarColor;

    extern ImVec4 insertDirectColor;
    extern ImVec4 insertDirectHoveredColor;
    extern ImVec4 insertDirectTypingColor;
    extern ImVec4 insertDirectTextColor;

    extern const char* disallowedCharCompoundString;

    extern const char* helpLink;

    extern int topMenu_____Padding;

//Side Menu
    extern ImVec4 sideMenuColor;
    extern int minimumSideMenuWidth;
    extern double initialSideMenuWidthPerCent;

    //ElementCompound Child Windows
        extern double childWindowSmallFontSize;
        extern double childWindowLargeFontSize;

        extern ImVec4 elementWindowColor;
        extern ImVec4 elementWindowBorderColor;
        extern ImVec4 elementWindowBorderShadowColor;
        extern ImVec4 elementWindowTextColor;

        //Element Window
            extern ImVec2 elementButtonSize;
            extern ImU32 elementButtonColor;
            extern ImU32 elementButtonBorderColor;
            extern ImU32 elementButtonHoveredColor;
            extern ImU32 elementButtonClickedColor;

            extern double elementButtonCurve;
            extern double elementButtonBorderThickness;

            extern ImVec4 customElementPopUpTextColor;
            extern ImVec4 customElementPopUpBackgroundColor;
            extern ImVec4 customElementPopUpTitleBarColor;
            extern ImVec4 customElementPopUpActiveTitleBarColor;
            extern ImVec4 customElementPopUpCollapsedTitleBarColor;

            extern double numberFontSize;
            extern double symbolFontSize;
            extern double nameFontSize;
            extern double massFontSize;

            extern ImU32 atomicNumberColor;
            extern ImU32 atomicMassColor;
            extern ImU32 atomicSymbolColor;
            extern ImU32 atomicNameColor;

        //Compound Window
            extern ImVec2 compoundButtonSize;
     
            extern std::vector<ImU32> compoundButtonColors;
            extern std::vector<ImU32> compoundButtonHoveredColors;
            extern std::vector<ImU32> compoundButtonClickedColors;

            extern ImU32 compoundButtonBorderColor;

            extern double compoundButtonBorderThickness;
            extern double compoundButtonCurve;

            extern double compoundNameSize;
            extern double molecularFormulaSize;

            extern ImU32 compoundNameColor;
            extern ImU32 molecularFormulaColor;

            extern ImVec4 compoundWindowColor;
            extern ImVec4 compoundWindowBorderColor;
            extern ImVec4 compoundWindowBorderShadowColor;
            extern ImVec4 compoundWindowTextColor;

        extern const char* elementTitle;
        extern const char* compoundTitle;

        extern ImU32 scrollBarColor;
        extern double scrollBarCurve;
        
        extern std::vector<int> initialElements;

        extern double initialElementHeightPerCent;
        extern double scrollerHeightPerCent;
        extern double minimumChildWindowPerCent;
        extern int adjustOffset;
        extern int elementCompound_____Padding;
        extern int IDKWhyOffset;

    //Search Bar
        extern double searchSmallFontSize;
        extern double searchLargeFontSize;

        extern ImVec4 searchBarColor;
        extern ImVec4 searchBarHoveredColor;
        extern ImVec4 searchBarTypingColor;
        extern ImVec4 searchBarTextColor;

        extern double initialSearchBarHeightPerCent;
        extern const char* SearchGlass;
        extern ImVec4 searchGlassTransparency;
        extern const char* searchBarLabel;
        extern ImVec4 searchBarLabelColor;
        extern const char* disallowedCharSearchBar;
        extern int search___padding;

//Error
// extern bool isError;
// extern std::string errorMessage;
extern int errorMessageOffsetX;
extern int errorMessageOffsetY;


//Render

//Shader
extern std::string elementVertShaderFilePath;
extern std::string elementFragShaderFilePath;
extern std::string electronVertShaderFilePath;
extern std::string electronFragShaderFilePath;
extern std::string numberVertShaderFilePath;
extern std::string numberFragShaderFilePath;
extern std::string signVertShaderFilePath;
extern std::string signFragShaderFilePath;

extern std::string covalentVertShaderFilePath;
extern std::string covalentFragShaderFilePath;
extern std::string ionicVertShaderFilePath;
extern std::string ionicFragShaderFilePath;
extern std::string dativeVertShaderFilePath;
extern std::string dativeFragShaderFilePath;

extern std::map<std::string,Shader> shaders;

//Element Assets
extern std::string elementFilePath1;
extern std::string elementFilePath2;

//Element PNG and Texture sizes
extern GLfloat elementTextureHeight;
extern GLfloat elementSingleTextureWidth;
extern GLfloat elementDoubleTextureWidth;

extern GLfloat electronDistanceDirect;
extern GLfloat electronDistanceAdjust;

extern glm::vec2 defaultSpawnLocation;

extern GLfloat signLength;
extern GLfloat bondThickness;
extern GLfloat signThickness;

extern struct Camera cam; 


//Values
extern std::map<std::string,std::string> molecules;
extern std::vector<std::string> compoundNumbers;
extern std::vector<std::string> searchBar;

 
//JSON Conversions


    void to_json(nlohmann::json& js, const ImVec4& vec);

    void from_json(const nlohmann::json&js, ImVec4& vec);
    
    void to_json(nlohmann::json& js, const ImU32& vec);
    
    void from_json(const nlohmann::json& js, ImU32& vec);
    
    void to_json(nlohmann::json& js, const ImVec2& vec);
    
    void from_json(const nlohmann::json&js, ImVec2& vec);
    


namespace glm{
    void to_json(nlohmann::json& js, const glm::vec2& vec);

    void from_json(const nlohmann::json&js, glm::vec2& vec);
}


//Config Setting
int Config();

template <typename T> void changeCustomJSON(std::string variable, T var){
    std::ifstream customConfigFile("../config/config.json");

    if(!customConfigFile){
        std::cout<<variable<<" could not be saved to file"<<std::endl;
        return;
    }

    nlohmann::json customConfigData;
    customConfigFile>> customConfigData;

    customConfigData[variable]=var;

    std::ofstream editingCustomConfigFile("../config/config.json");

    if(!editingCustomConfigFile){
        std::cout<<variable<<" could not be saved to file"<<std::endl;
        return;
    }
    editingCustomConfigFile<<customConfigData;
}
//template
template <typename T> void restoreToDefault(std::string variable, T& var){
    std::ifstream defaultConfigFile("../config/defaultConfig.json");
    std::ifstream customConfigFile("../config/config.json");

    if(!customConfigFile){
        std::cout<<variable<<" could not be restored"<<std::endl;
        return;
    }

    nlohmann::json customConfigData;
    customConfigFile>> customConfigData;

    customConfigData.erase(variable);

    std::ofstream editingCustomConfigFile("../config/config.json");
    if(!editingCustomConfigFile){
        std::cout<<variable<<" could not be saved"<<std::endl;
        return;
    }
    editingCustomConfigFile<<customConfigData;

    nlohmann::json defaultConfigData;
    defaultConfigData<<defaultConfigFile;

    var=defaultConfigData.at(variable).get<T>();
}


#endif