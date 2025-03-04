#include "config.h"

using json = nlohmann::json;

//order of map doesnt matter but compoundNumber is order you want diplayed in documentation

const char* windowName="Nomenclature";

const ImWchar ranges[] = {
    0x0020, 0x007E,  //ASCII
    0x2070, 0x209F,  //Superscripts and subscripts
    0
};

std::string currentFile="Unknown";
const char* elementTitle="Elements";
const char* compoundTitle="Common Compounds";
const char* disallowedCharCompoundString="!@#$%^";

const char* helpLink="github.com/";

const char* SearchGlass="../Assets/SearchGlass.png";
const char* searchBarLabel="Search..";

const char* disallowedCharSearchBar="!@#$%^&*\n\t0123456789";

bool isError=false;
std::string errorMessage="";
 
std::string elementVertShaderFilePath="../shaders/texture.vert";
std::string elementFragShaderFilePath="../shaders/texture.frag";
std::string electronVertShaderFilePath="../shaders/electron.vert";
std::string electronFragShaderFilePath="../shaders/electron.frag";
std::string numberVertShaderFilePath="../shaders/texture.vert";
std::string numberFragShaderFilePath="../shaders/texture.frag";
std::string signVertShaderFilePath="../shaders/sign.vert";
std::string signFragShaderFilePath="../shaders/sign.frag";

std::string covalentVertShaderFilePath="../shaders/covalent.vert";
std::string covalentFragShaderFilePath="../shaders/covalent.frag";
std::string ionicVertShaderFilePath="../shaders/ionic.vert";
std::string ionicFragShaderFilePath="../shaders/ionic.frag";
std::string dativeVertShaderFilePath="../shaders/dative.vert"; 
std::string dativeFragShaderFilePath="../shaders/dative.frag";

std::map<std::string,Shader> shaders;

std::string elementFilePath1="../Assets/Elements/";
std::string elementFilePath2=".png";

std::vector<std::string> searchBar={
    "h", "he", "li", "be", "b", "c", "n", "o", "f", "ne", "na", "mg", "al", "si", "p", "s", "cl", "ar", "k", "ca", "sc", "ti", "v", "cr", "mn", "fe", "co", "ni", "cu", "zn", "ga", "ge", "as", "se", "br", "kr", "rb", "sr", "y", "zr", "nb", "mo", "tc", "ru", "rh", "pd", "ag",
    "cd", "in", "sn", "sb", "te", "i", "xe", "cs", "ba", "la", "ce", "pr", "nd", "pm", "sm", "eu", "gd", "tb", "dy", "ho", "er", "tm", "yb", "lu", "hf", "ta",
    "w", "re", "os", "ir", "pt", "au", "hg", "tl", "pb", "bi", "po", "at", "rn", "fr", "ra", "ac", "th", "pa", "u", "np", "pu", "am", "cm", "bk", "cf", "es",
    "fm", "md", "no", "lr", "rf", "db", "sg", "bh", "hs", "mt", "ds", "rg", "cn", "nh", "fl", "mc", "lv", "ts", "og",

    "hydrogen", "helium", "lithium", "beryllium", "boron", "carbon", "nitrogen", "oxygen", "fluorine", "neon", "sodium", "magnesium", "aluminum", "silicon", "phosphorus", "sulfur", "chlorine", "argon", "potassium", "calcium", "scandium",
    "titanium", "vanadium", "chromium", "manganese", "iron", "cobalt", "nickel", "copper", "zinc", "gallium", "germanium", "arsenic",
    "selenium", "bromine", "krypton", "rubidium", "strontium", "yttrium", "zirconium", "niobium", "molybdenum", "technetium", "ruthenium",
    "rhodium", "palladium", "silver", "cadmium", "indium", "tin", "antimony", "tellurium", "iodine", "xenon", "cesium", "barium", "lanthanum",
    "cerium", "praseodymium", "neodymium", "promethium", "samarium", "europium", "gadolinium", "terbium", "dysprosium", "holmium", "erbium",
    "thulium", "ytterbium", "lutetium", "hafnium", "tantalum", "tungsten", "rhenium", "osmium", "iridium", "platinum", "gold", "mercury", "thallium",
    "lead", "bismuth", "polonium", "astatine", "radon", "francium", "radium", "actinium", "thorium", "protactinium", "uranium", "neptunium", "plutonium",
    "americium", "curium", "berkelium", "californium", "einsteinium", "fermium", "mendelevium", "nobelium", "lawrencium", "rutherfordium", "dubnium", "seaborgium",
    "bohrium", "hassium", "meitnerium", "darmstadtium", "roentgenium", "copernicium", "nihonium", "flerovium", "moscovium", "livermorium", "tennessine", "oganesson",
};

//Window


ImVec4 windowColor;
int windowHeight;
int windowWidth;
int largeWindowHeight;

//what can i say im lazy
std::string fontFileString;
const char* fontFile;

std::string molecularFormulaFontFileString;
const char* molecularFormulaFontFile;

double windowSmallFontSize;
double windowLargeFontSize;

//Top Menu 

ImVec4 topMenuButtonColor;
ImVec4 topMenuHoveredButtonColor;
ImVec4 topMenuActiveButtonColor;
ImVec4 topMenuTextColor;

ImVec4 fileNameColor;

ImVec4 settingsColorPickersTextColor;
ImVec4 settingsColorPickersBackgroundColor;
ImVec4 settingsColorPickersTitleBarColor;
ImVec4 settingsColorPickersActiveTitleBarColor;
ImVec4 settingsColorPickersCollapsedTitleBarColor;

ImVec4 openFilePopUpTextColor;
ImVec4 openFilePopUpBackgroundColor;
ImVec4 openFilePopUpTitleBarColor;
ImVec4 openFilePopUpActiveTitleBarColor;
ImVec4 openFilePopUpCollapsedTitleBarColor;

ImVec4 insertDirectColor;
ImVec4 insertDirectHoveredColor;
ImVec4 insertDirectTypingColor;
ImVec4 insertDirectTextColor;

int topMenu_____Padding;

//Side Menu
ImVec4 sideMenuColor;
int minimumSideMenuWidth;
double initialSideMenuWidthPerCent;

//ElementCompound Child Windows
    double childWindowSmallFontSize;
    double childWindowLargeFontSize;

    ImVec4 elementWindowColor;
    ImVec4 elementWindowBorderColor;
    ImVec4 elementWindowBorderShadowColor;
    ImVec4 elementWindowTextColor;

    //Element Window
        ImVec2 elementButtonSize;
        ImU32 elementButtonColor;
        ImU32 elementButtonBorderColor;
        ImU32 elementButtonHoveredColor;
        ImU32 elementButtonClickedColor;

        double elementButtonCurve;
        double elementButtonBorderThickness;

        ImVec4 customElementPopUpTextColor;
        ImVec4 customElementPopUpBackgroundColor;
        ImVec4 customElementPopUpTitleBarColor;
        ImVec4 customElementPopUpActiveTitleBarColor;
        ImVec4 customElementPopUpCollapsedTitleBarColor;

        double numberFontSize;
        double symbolFontSize;
        double nameFontSize;
        double massFontSize;

        ImU32 atomicNumberColor;
        ImU32 atomicMassColor;
        ImU32 atomicSymbolColor;
        ImU32 atomicNameColor;

    //Compound Window
        ImVec2 compoundButtonSize;
 
        std::vector<ImU32> compoundButtonColors;
        std::vector<ImU32> compoundButtonHoveredColors;
        std::vector<ImU32> compoundButtonClickedColors;

        ImU32 compoundButtonBorderColor;

        double compoundButtonBorderThickness;
        double compoundButtonCurve;

        double compoundNameSize;
        double molecularFormulaSize;

        ImU32 compoundNameColor;
        ImU32 molecularFormulaColor;

        ImVec4 compoundWindowColor;
        ImVec4 compoundWindowBorderColor;
        ImVec4 compoundWindowBorderShadowColor;
        ImVec4 compoundWindowTextColor;


    ImU32 scrollBarColor;
    double scrollBarCurve;
    
    std::vector<int> initialElements;

    double initialElementHeightPerCent;
    double scrollerHeightPerCent;
    double minimumChildWindowPerCent;
    int adjustOffset;
    int elementCompound_____Padding;
    int IDKWhyOffset;

//Search Bar
    double searchSmallFontSize;
    double searchLargeFontSize;

    ImVec4 searchBarColor;
    ImVec4 searchBarHoveredColor;
    ImVec4 searchBarTypingColor;
    ImVec4 searchBarTextColor;

    double initialSearchBarHeightPerCent;
    ImVec4 searchGlassTransparency;
    ImVec4 searchBarLabelColor;
    int search___padding;

//Error
int errorMessageOffsetX;
int errorMessageOffsetY;


//Render

//Element PNG and Texture sizes
GLfloat elementTextureHeight;
GLfloat elementSingleTextureWidth;
GLfloat elementDoubleTextureWidth;

GLfloat electronDistanceDirect;
GLfloat electronDistanceAdjust;

glm::vec2 defaultSpawnLocation;

GLfloat signLength;
GLfloat bondThickness;
GLfloat signThickness;


 


void to_json(json& js, const ImVec4& vec){
    js=json{{"x",vec.x},{"y",vec.y},{"z",vec.z},{"w",vec.w}};
}

void from_json(json&js, ImVec4& vec){
    js.at("x").get_to(vec.x);
    js.at("y").get_to(vec.y);
    js.at("z").get_to(vec.z);
    js.at("w").get_to(vec.w);
}

void to_json(json& js, const glm::vec2& vec){
    js=json{{"x",vec.x},{"y",vec.y}};
}

void from_json(json&js, glm::vec2& vec){
    js.at("x").get_to(vec.x);
    js.at("y").get_to(vec.y);
}

void to_json(json& js, const ImU32& vec){
    js=json{{"R",(vec >> IM_COL32_R_SHIFT) & 0xFF},{"G",(vec >> IM_COL32_G_SHIFT) & 0xFF},{"B",(vec >> IM_COL32_B_SHIFT) & 0xFF},{"A",(vec >> IM_COL32_A_SHIFT) & 0xFF}};
}

void from_json(json& js, ImU32& vec){
    uint8_t R = js.at("R").get<uint8_t>();
    uint8_t G = js.at("G").get<uint8_t>();
    uint8_t B = js.at("B").get<uint8_t>();
    uint8_t A = js.at("A").get<uint8_t>();
    vec = IM_COL32(R, G, B, A);
}
 
void to_json(json& js, const ImVec2& vec){
    js=json{{"x",vec.x},{"y",vec.y}};
}

void from_json(json&js, ImVec2& vec){
    js.at("x").get_to(vec.x);
    js.at("y").get_to(vec.y);
}


int Config(){
    //for now default
    //try finding default if fail go to default
    //ngl im a genius
    json configData;

    std::ifstream defaultConfigFile("../config/defaultConfig.json");
    std::ifstream customConfigFile("../config/config.json");
    if (!defaultConfigFile && !customConfigFile) {
        std::cerr << "Could not find any config file\n";
        return 0;
    } 
    else if(!customConfigFile){
        defaultConfigFile>> configData;
    }
    else if(!defaultConfigFile){
        customConfigFile>> configData;
    }
    else{
        //custom takes priority
        json customConfigData;

        defaultConfigFile>> configData;
        customConfigFile>> customConfigData;

        configData.update(customConfigData);

    }

    //thnk you chatgpt i wont forget it
    // Window properties
    windowColor = configData.at("windowColor").get<ImVec4>();
    windowHeight = configData.at("windowHeight").get<int>();
    windowWidth = configData.at("windowWidth").get<int>();
    largeWindowHeight = configData.at("largeWindowHeight").get<int>();

    fontFileString=configData.at("fontFile").get<std::string>();
    fontFile=fontFileString.c_str();

    molecularFormulaFontFileString=configData.at("molecularFormulaFontFile").get<std::string>();
    molecularFormulaFontFile=molecularFormulaFontFileString.c_str();

    // Font sizes
    windowSmallFontSize = configData.at("windowSmallFontSize").get<double>();
    windowLargeFontSize = configData.at("windowLargeFontSize").get<double>();

    // Top Menu
    topMenuButtonColor = configData.at("topMenuButtonColor").get<ImVec4>();
    topMenuHoveredButtonColor = configData.at("topMenuHoveredButtonColor").get<ImVec4>();
    topMenuActiveButtonColor = configData.at("topMenuActiveButtonColor").get<ImVec4>();
    topMenuTextColor = configData.at("topMenuTextColor").get<ImVec4>();

    fileNameColor = configData.at("fileNameColor").get<ImVec4>();

    settingsColorPickersTextColor = configData.at("settingsColorPickersTextColor").get<ImVec4>();
    settingsColorPickersBackgroundColor = configData.at("settingsColorPickersBackgroundColor").get<ImVec4>();
    settingsColorPickersTitleBarColor = configData.at("settingsColorPickersTitleBarColor").get<ImVec4>();
    settingsColorPickersActiveTitleBarColor = configData.at("settingsColorPickersActiveTitleBarColor").get<ImVec4>();
    settingsColorPickersCollapsedTitleBarColor = configData.at("settingsColorPickersCollapsedTitleBarColor").get<ImVec4>();

    openFilePopUpTextColor = configData.at("openFilePopUpTextColor").get<ImVec4>();
    openFilePopUpBackgroundColor = configData.at("openFilePopUpBackgroundColor").get<ImVec4>();
    openFilePopUpTitleBarColor = configData.at("openFilePopUpTitleBarColor").get<ImVec4>();
    openFilePopUpActiveTitleBarColor = configData.at("openFilePopUpActiveTitleBarColor").get<ImVec4>();
    openFilePopUpCollapsedTitleBarColor = configData.at("openFilePopUpCollapsedTitleBarColor").get<ImVec4>();

    insertDirectColor = configData.at("insertDirectColor").get<ImVec4>();
    insertDirectHoveredColor = configData.at("insertDirectHoveredColor").get<ImVec4>();
    insertDirectTypingColor = configData.at("insertDirectTypingColor").get<ImVec4>();
    insertDirectTextColor = configData.at("insertDirectTextColor").get<ImVec4>();

    topMenu_____Padding = configData.at("topMenu_____Padding").get<int>();

    // Side Menu
    sideMenuColor = configData.at("sideMenuColor").get<ImVec4>();
    minimumSideMenuWidth = configData.at("minimumSideMenuWidth").get<int>();
    initialSideMenuWidthPerCent = configData.at("initialSideMenuWidthPerCent").get<double>();

    // ElementCompound Child Windows
    childWindowSmallFontSize = configData.at("childWindowSmallFontSize").get<double>();
    childWindowLargeFontSize = configData.at("childWindowLargeFontSize").get<double>();

    elementWindowColor = configData.at("elementWindowColor").get<ImVec4>();
    elementWindowBorderColor = configData.at("elementWindowBorderColor").get<ImVec4>();
    elementWindowBorderShadowColor = configData.at("elementWindowBorderShadowColor").get<ImVec4>();
    elementWindowTextColor = configData.at("elementWindowTextColor").get<ImVec4>();

    elementButtonSize = configData.at("elementButtonSize").get<ImVec2>();
    elementButtonColor = configData.at("elementButtonColor").get<ImU32>();
    elementButtonBorderColor = configData.at("elementButtonBorderColor").get<ImU32>();
    elementButtonHoveredColor = configData.at("elementButtonHoveredColor").get<ImU32>();
    elementButtonClickedColor = configData.at("elementButtonClickedColor").get<ImU32>();

    elementButtonCurve = configData.at("elementButtonCurve").get<double>();
    elementButtonBorderThickness = configData.at("elementButtonBorderThickness").get<double>();

    customElementPopUpTextColor = configData.at("customElementPopUpTextColor").get<ImVec4>();
    customElementPopUpBackgroundColor = configData.at("customElementPopUpBackgroundColor").get<ImVec4>();
    customElementPopUpTitleBarColor = configData.at("customElementPopUpTitleBarColor").get<ImVec4>();
    customElementPopUpActiveTitleBarColor = configData.at("customElementPopUpActiveTitleBarColor").get<ImVec4>();
    customElementPopUpCollapsedTitleBarColor = configData.at("customElementPopUpCollapsedTitleBarColor").get<ImVec4>();

    numberFontSize = configData.at("numberFontSize").get<double>();
    symbolFontSize = configData.at("symbolFontSize").get<double>();
    nameFontSize = configData.at("nameFontSize").get<double>();
    massFontSize = configData.at("massFontSize").get<double>();

    atomicNumberColor = configData.at("atomicNumberColor").get<ImU32>();
    atomicMassColor = configData.at("atomicMassColor").get<ImU32>();
    atomicSymbolColor = configData.at("atomicSymbolColor").get<ImU32>();
    atomicNameColor = configData.at("atomicNameColor").get<ImU32>();

    compoundButtonSize = configData.at("compoundButtonSize").get<ImVec2>();
    compoundButtonColors = configData.at("compoundButtonColors").get<std::vector<ImU32>>();
    compoundButtonHoveredColors = configData.at("compoundButtonHoveredColors").get<std::vector<ImU32>>();
    compoundButtonClickedColors = configData.at("compoundButtonClickedColors").get<std::vector<ImU32>>();

    compoundButtonBorderColor = configData.at("compoundButtonBorderColor").get<ImU32>();
    compoundButtonBorderThickness = configData.at("compoundButtonBorderThickness").get<double>();
    compoundButtonCurve = configData.at("compoundButtonCurve").get<double>();

    compoundNameSize = configData.at("compoundNameSize").get<double>();
    molecularFormulaSize = configData.at("molecularFormulaSize").get<double>();

    compoundNameColor = configData.at("compoundNameColor").get<ImU32>();
    molecularFormulaColor = configData.at("molecularFormulaColor").get<ImU32>();

    compoundWindowColor = configData.at("compoundWindowColor").get<ImVec4>();
    compoundWindowBorderColor = configData.at("compoundWindowBorderColor").get<ImVec4>();
    compoundWindowBorderShadowColor = configData.at("compoundWindowBorderShadowColor").get<ImVec4>();
    compoundWindowTextColor = configData.at("compoundWindowTextColor").get<ImVec4>();

    scrollBarColor = configData.at("scrollBarColor").get<ImU32>();
    scrollBarCurve = configData.at("scrollBarCurve").get<double>();

    initialElements = configData.at("initialElements").get<std::vector<int>>();

    initialElementHeightPerCent = configData.at("initialElementHeightPerCent").get<double>();
    scrollerHeightPerCent = configData.at("scrollerHeightPerCent").get<double>();
    minimumChildWindowPerCent = configData.at("minimumChildWindowPerCent").get<double>();
    adjustOffset = configData.at("adjustOffset").get<int>();
    elementCompound_____Padding = configData.at("elementCompound_____Padding").get<int>();
    IDKWhyOffset = configData.at("IDKWhyOffset").get<int>();

    // Search Bar
    searchSmallFontSize = configData.at("searchSmallFontSize").get<double>();
    searchLargeFontSize = configData.at("searchLargeFontSize").get<double>();

    searchBarColor = configData.at("searchBarColor").get<ImVec4>();
    searchBarHoveredColor = configData.at("searchBarHoveredColor").get<ImVec4>();
    searchBarTypingColor = configData.at("searchBarTypingColor").get<ImVec4>();
    searchBarTextColor = configData.at("searchBarTextColor").get<ImVec4>();

    initialSearchBarHeightPerCent = configData.at("initialSearchBarHeightPerCent").get<double>();
    searchGlassTransparency = configData.at("searchGlassTransparency").get<ImVec4>();
    searchBarLabelColor=configData.at("searchBarLabelColor").get<ImVec4>();
    search___padding = configData.at("search___padding").get<int>();

    //Error
    errorMessageOffsetX=configData.at("errorMessageOffsetX").get<int>();
    errorMessageOffsetY=configData.at("errorMessageOffsetY").get<int>();

    // Element PNG and Texture sizes
    elementTextureHeight = configData.at("elementTextureHeight").get<GLfloat>();
    elementSingleTextureWidth = configData.at("elementSingleTextureWidth").get<GLfloat>();
    elementDoubleTextureWidth = configData.at("elementDoubleTextureWidth").get<GLfloat>();

    electronDistanceDirect=configData.at("electronDistanceDirect").get<double>();
    electronDistanceAdjust=configData.at("electronDistanceAdjust").get<double>();


    // Spawn location
    defaultSpawnLocation = configData.at("defaultSpawnLocation").get<glm::vec2>();

    signLength=configData.at("signLength").get<GLfloat>();
    bondThickness=configData.at("bondThickness").get<GLfloat>();
    signThickness=configData.at("signThickness").get<GLfloat>();

    compoundNumbers= configData.at("compoundNumbers").get<std::vector<std::string>>();
    molecules=configData.at("molecules").get<std::map<std::string,std::string>>();

    if(configData.contains("additionalCompoundNumbers") && configData.contains("additionalCompoundStrings")){
        std::vector<std::pair<std::string,int>> additionals=configData.at("additonalCompoundNumbers").get<std::vector<std::pair<std::string,int>>>();
        std::map<std::string,std::string> additonalStrings=configData.at("additionalCompoundStrings").get<std::map<std::string,std::string>>();

        if(additonalStrings.size()!=additionals.size()){
            isError=true;
            errorMessage="Additional Compounds could not be Inserted";
            std::cerr<<"Additional Compounds could not be Inserted"<<std::endl;
        }
        else{
            for(auto it: additionals){
                compoundNumbers.insert(compoundNumbers.begin()+it.second,it.first);
            }
            for(auto [key,value]: additonalStrings){
                molecules[key]=value;
            }
        }


    }

    for(auto it:compoundNumbers){
        std::string name=it;
        std::transform(name.begin(),name.end(),name.begin(),::tolower);

        searchBar.push_back(name);
    }
}

//template
template <typename T> void changeCustomJSON(std::string variable,T var){
    std::ifstream customConfigFile("../config/config.json");

    if(!customConfigFile){
        std::cout<<variable<<" could not be saved to file"<<std::endl;
        return;
    }

    json customConfigData;
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

    json customConfigData;
    customConfigFile>> customConfigData;

    customConfigData.erase(variable);

    std::ofstream editingCustomConfigFile("../config/config.json");
    if(!editingCustomConfigFile){
        std::cout<<variable<<" could not be saved"<<std::endl;
        return;
    }
    editingCustomConfigFile<<customConfigData;

    json defaultConfigData;
    defaultConfigData<<defaultConfigFile;

    var=defaultConfigData.at(variable).get<T>();
}