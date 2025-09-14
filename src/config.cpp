#include "config.h"

using json = nlohmann::json;

//orderm of map doesnt matter but compoundNumber is order you want displayed in documentation

const char* windowName="ChemCraft";

const ImWchar ranges[] = {
    0x0020, 0x007E,  //ASCII
    0x2070, 0x209F,  //Superscripts and subscripts
    0
};

std::string currentFile="Unknown";
const char* elementTitle="Elements";
const char* compoundTitle="Common Compounds";
const char* disallowedCharCompoundString="!@#$%^";
 
const char* helpLink="github.com/Antasma-X/ChemCraft";

const char* SearchGlass="assets/searchGlass.png";
const char* searchBarLabel="Search..";

const char* disallowedCharSearchBar="!@#$%^&*\n\t0123456789";

 
std::string elementVertShaderFilePath="shaders/texture.vert";
std::string elementFragShaderFilePath="shaders/texture.frag";
std::string glowElementVertShaderFilePath="shaders/glowElement.vert";
std::string glowElementFragShaderFilePath="shaders/glowElement.frag";
std::string electronVertShaderFilePath="shaders/electron.vert";
std::string electronFragShaderFilePath="shaders/electron.frag";
std::string glowElectronVertShaderFilePath="shaders/glowElectron.vert";
std::string glowElectronFragShaderFilePath="shaders/glowElectron.frag";
std::string numberVertShaderFilePath="shaders/texture.vert";
std::string numberFragShaderFilePath="shaders/texture.frag";
std::string signVertShaderFilePath="shaders/texture.vert";
std::string signFragShaderFilePath="shaders/texture.frag";
 
std::string covalentVertShaderFilePath="shaders/covalent.vert";
std::string covalentFragShaderFilePath="shaders/covalent.frag";
std::string ionicVertShaderFilePath="shaders/ionic.vert";
std::string ionicFragShaderFilePath="shaders/ionic.frag";
std::string dativeVertShaderFilePath="shaders/dative.vert"; 
std::string dativeFragShaderFilePath="shaders/dative.frag";
std::string glowBondVertShaderFilePath="shaders/glowBond.vert";
std::string glowBondFragShaderFilePath="shaders/glowBond.frag";

std::map<std::string,Shader> shaders;

bool openContMenu=false;

std::string elementFilePath1="assets/elements/";
std::string elementFilePath2=".png";

std::string numberBlueFilePath="assets/numberAtlasBlue.png";
std::string numberRedFilePath="assets/numberAtlasRed.png";

std::string plusFilePath="assets/plusBlue.png";
std::string minusFilePath="assets/minusRed.png";

const char* disallowedCharCompoundNames="!@#$%^&*\n\t0123456789";
 
std::map<std::string,std::string> molecules;
std::vector<std::string> compoundNames;
std::map<std::string,std::string> molecularFormulae;

std::vector<std::string> searchBarArray={
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

//Element PNG and Texture sizes
GLfloat elementTextureHeight;
GLfloat elementSingleTextureWidth;
GLfloat elementDoubleTextureWidth;

GLfloat elementHoveredGlowLevel;
GLfloat elementSelectedGlowLevel;

GLfloat electronDistanceDirect;
GLfloat electronDistanceAdjust;
GLfloat electronRadius;
GLfloat electronSelectionBuffer;

GLfloat electronHoveredGlowLevel;
GLfloat electronSelectedGlowLevel;

GLfloat electronToDativePullFactor;
GLfloat minElectronSeparation;

GLfloat electronShiftDuration;
GLfloat electronShiftDelay;
GLfloat electronCornerRadius;

//Sign
GLfloat plusSignTextureWidth;
GLfloat plusSignTextureHeight;
GLfloat minusSignTextureWidth;
GLfloat minusSignTextureHeight;
 
ImVec4 contextMenuPopUpTextColor;
ImVec4 contextMenuPopUpBackgroundColor;
ImVec4 contextMenuPopUpTitleBarColor;
ImVec4 contextMenuPopUpActiveTitleBarColor;
ImVec4 contextMenuPopUpCollapsedTitleBarColor;

//Camera
float minZoom;
float maxZoom;
int minCamMovement;
float zoomShift;
float elementSpacingAmount;

glm::vec2 defaultSpawnLocation;

GLfloat signLength;
GLfloat bondThickness;
GLfloat signThickness;

GLfloat bondHoveredGlowLevel;
GLfloat bondSelectedGlowLevel;

GLfloat numberTextureWidth;
GLfloat numberTextureHeight;
 
double sideMenuWidthPerCentCopy;
 

void to_json(json& js, const ImVec4& vec){
    js=json{{"x",vec.x},{"y",vec.y},{"z",vec.z},{"w",vec.w}};
}

void from_json(const json&js, ImVec4& vec){
    js.at("x").get_to(vec.x);
    js.at("y").get_to(vec.y);
    js.at("z").get_to(vec.z);
    js.at("w").get_to(vec.w);
}

void glm::to_json(json& js, const glm::vec2& vec){
    js=json{{"x",vec.x},{"y",vec.y}};
}

void glm::from_json(const json&js, glm::vec2& vec){
    js.at("x").get_to(vec.x);
    js.at("y").get_to(vec.y);
}

void to_json(json& js, const ImU32& vec){
    js=json{{"R",(vec >> IM_COL32_R_SHIFT) & 0xFF},{"G",(vec >> IM_COL32_G_SHIFT) & 0xFF},{"B",(vec >> IM_COL32_B_SHIFT) & 0xFF},{"A",(vec >> IM_COL32_A_SHIFT) & 0xFF}};
}

void from_json(const json& js, ImU32& vec){
    uint8_t R = js.at("R").get<uint8_t>();
    uint8_t G = js.at("G").get<uint8_t>();
    uint8_t B = js.at("B").get<uint8_t>();
    uint8_t A = js.at("A").get<uint8_t>();
    vec = IM_COL32(R, G, B, A);
}
 
void to_json(json& js, const ImVec2& vec){
    js=json{{"x",vec.x},{"y",vec.y}};
}

void from_json(const json&js, ImVec2& vec){
    js.at("x").get_to(vec.x);
    js.at("y").get_to(vec.y);
}

ImU32 RGBAtoImU32(const nlohmann::json& js){
    return IM_COL32(js.at("R"), js.at("G"), js.at("B"), js.at("A"));
}

std::vector<ImU32> RGBAVectortoImU32(const nlohmann::json& js){
    std::vector<ImU32> objs;

    for (const auto& item: js) {
        objs.push_back(RGBAtoImU32(item));
    }
    return objs;
}

int Config(){
    //for now default
    //try finding default if fail go to default
    //ngl im a genius
    json configData;

    std::ifstream defaultConfigFile("config/defaultConfig.json");
    std::ifstream customConfigFile("config/config.json");
    if (!defaultConfigFile.is_open() && !customConfigFile.is_open()) {
        std::cerr << "Could not find any config file\n";
        return 0;
    } 
    else if(!customConfigFile.is_open()){
        defaultConfigFile>> configData;
    }
    else if(!defaultConfigFile.is_open()){
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

    // Element Compound Child Windows
    childWindowSmallFontSize = configData.at("childWindowSmallFontSize").get<double>();
    childWindowLargeFontSize = configData.at("childWindowLargeFontSize").get<double>();

    elementWindowColor = configData.at("elementWindowColor").get<ImVec4>();
    elementWindowBorderColor = configData.at("elementWindowBorderColor").get<ImVec4>();
    elementWindowBorderShadowColor = configData.at("elementWindowBorderShadowColor").get<ImVec4>();
    elementWindowTextColor = configData.at("elementWindowTextColor").get<ImVec4>();

    elementButtonSize = configData.at("elementButtonSize").get<ImVec2>();

    //imu32 is problem
    elementButtonColor = RGBAtoImU32(configData.at("elementButtonColor"));
    elementButtonBorderColor = RGBAtoImU32(configData.at("elementButtonBorderColor"));
    elementButtonHoveredColor = RGBAtoImU32(configData.at("elementButtonHoveredColor"));
    elementButtonClickedColor = RGBAtoImU32(configData.at("elementButtonClickedColor"));
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

    atomicNumberColor = RGBAtoImU32(configData.at("atomicNumberColor"));
    atomicMassColor = RGBAtoImU32(configData.at("atomicMassColor"));
    atomicSymbolColor = RGBAtoImU32(configData.at("atomicSymbolColor"));
    atomicNameColor = RGBAtoImU32(configData.at("atomicNameColor"));

    compoundButtonSize = configData.at("compoundButtonSize").get<ImVec2>();
    compoundButtonColors =RGBAVectortoImU32( configData.at("compoundButtonColors"));
    compoundButtonHoveredColors =RGBAVectortoImU32(configData.at("compoundButtonHoveredColors"));
    compoundButtonClickedColors =RGBAVectortoImU32(configData.at("compoundButtonClickedColors"));

    compoundButtonBorderColor = RGBAtoImU32(configData.at("compoundButtonBorderColor"));
    compoundButtonBorderThickness = configData.at("compoundButtonBorderThickness").get<double>();
    compoundButtonCurve = configData.at("compoundButtonCurve").get<double>();
    compoundNameSize = configData.at("compoundNameSize").get<double>();
    molecularFormulaSize = configData.at("molecularFormulaSize").get<double>();

    compoundNameColor = RGBAtoImU32(configData.at("compoundNameColor"));
    molecularFormulaColor = RGBAtoImU32(configData.at("molecularFormulaColor"));
    compoundWindowColor = configData.at("compoundWindowColor").get<ImVec4>();
    compoundWindowBorderColor = configData.at("compoundWindowBorderColor").get<ImVec4>();
    compoundWindowBorderShadowColor = configData.at("compoundWindowBorderShadowColor").get<ImVec4>();
    compoundWindowTextColor = configData.at("compoundWindowTextColor").get<ImVec4>();
    scrollBarColor = RGBAtoImU32(configData.at("scrollBarColor"));
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

    elementHoveredGlowLevel = configData.at("elementHoveredGlowLevel").get<GLfloat>();
    elementSelectedGlowLevel = configData.at("elementSelectedGlowLevel").get<GLfloat>();

    electronDistanceDirect=configData.at("electronDistanceDirect").get<double>();
    electronDistanceAdjust=configData.at("electronDistanceAdjust").get<double>();
    electronRadius=configData.at("electronRadius").get<double>();
    electronSelectionBuffer=configData.at("electronSelectionBuffer").get<double>();

    electronHoveredGlowLevel=configData.at("electronHoveredGlowLevel").get<double>();
    electronSelectedGlowLevel=configData.at("electronSelectedGlowLevel").get<double>();

    electronToDativePullFactor=configData.at("electronToDativePullFactor").get<double>();
    minElectronSeparation=configData.at("minElectronSeparation").get<double>();

    electronShiftDuration=configData.at("electronShiftDuration").get<double>();
    electronShiftDelay=configData.at("electronShiftDelay").get<double>();
    electronCornerRadius=configData.at("electronCornerRadius").get<double>();
 
    numberTextureWidth=configData.at("numberTextureWidth").get<double>();
    numberTextureHeight=configData.at("numberTextureHeight").get<double>();

    plusSignTextureWidth=configData.at("plusSignTextureWidth").get<double>();
    plusSignTextureHeight=configData.at("plusSignTextureHeight").get<double>();
    minusSignTextureWidth=configData.at("minusSignTextureWidth").get<double>();
    minusSignTextureHeight=configData.at("minusSignTextureHeight").get<double>();

    contextMenuPopUpTextColor = configData.at("contextMenuPopUpTextColor").get<ImVec4>();
    contextMenuPopUpBackgroundColor = configData.at("contextMenuPopUpBackgroundColor").get<ImVec4>();
    contextMenuPopUpTitleBarColor = configData.at("contextMenuPopUpTitleBarColor").get<ImVec4>();
    contextMenuPopUpActiveTitleBarColor = configData.at("contextMenuPopUpActiveTitleBarColor").get<ImVec4>();
    contextMenuPopUpCollapsedTitleBarColor = configData.at("contextMenuPopUpCollapsedTitleBarColor").get<ImVec4>();

    //Camera
    minZoom=configData.at("minZoom").get<float>();; 
    maxZoom=configData.at("maxZoom").get<float>();
    minCamMovement=configData.at("minCamMovement").get<int>();
    zoomShift=configData.at("zoomShift").get<float>();
    elementSpacingAmount=configData.at("elementSpacingAmount").get<float>();

    // Spawn location 
    defaultSpawnLocation = configData.at("defaultSpawnLocation").get<glm::vec2>();

    signLength=configData.at("signLength").get<GLfloat>();
    bondThickness=configData.at("bondThickness").get<GLfloat>();
    signThickness=configData.at("signThickness").get<GLfloat>();

    bondHoveredGlowLevel=configData.at("bondHoveredGlowLevel").get<GLfloat>();
    bondSelectedGlowLevel=configData.at("bondSelectedGlowLevel").get<GLfloat>();

    compoundNames= configData.at("compoundNames").get<std::vector<std::string>>();
    molecules=configData.at("molecules").get<std::map<std::string,std::string>>();

    if(configData.contains("additionalCompoundNames") && configData.contains("additionalMolecules")){
        std::vector<std::pair<std::string,int>> additionals=configData.at("additionalCompoundNames").get<std::vector<std::pair<std::string,int>>>();
        std::map<std::string,std::string> additonalStrings=configData.at("additionalMolecules").get<std::map<std::string,std::string>>();

        if(additonalStrings.size()!=additionals.size()){
            error->push("Additional Compounds could not be Inserted");
            std::cerr<<"Additional Compounds could not be Inserted"<<std::endl;
        }
        else{
            for(auto it: additionals){
                compoundNames.insert(compoundNames.begin()+it.second,it.first);
            }
            for(auto [key,value]: additonalStrings){
                molecules[key]=value;
            }
        }
    }

    for(auto it:compoundNames){
        std::string name=it;
        std::transform(name.begin(),name.end(),name.begin(),::tolower);
        searchBarArray.push_back(name);
    }

    for(auto [key,value]: molecules){
        Compound comp(value);
        molecularFormulae[key]=comp.getMolecularFormula();
    }
    
    sideMenuWidthPerCentCopy=initialSideMenuWidthPerCent;
    return 1;
}

int addCompoundToConfigFile(std::string name, std::string compoundString){

    json configData;

    std::ifstream customConfigFile("config/config.json");
    if (!customConfigFile.is_open()) {
        error->push("Could not find custom config file");
        std::cerr << "Could not find any config file\n";
        return 0;
    }

    customConfigFile>>configData;
    customConfigFile.close();

    if(!configData.contains("additionalCompoundNames")||!configData["additionalCompoundNames"].is_array()){
        configData["additionalCompoundNames"]=json::array();
    }

    if (std::find(configData["additionalCompoundNames"].begin(),configData["additionalCompoundNames"].end(), name)!=configData["additionalCompoundNames"].end()||std::find(compoundNames.begin(),compoundNames.end(), name)!=compoundNames.end()) {
        error->push("Compound Name already exists. Please choose another");
        return 0;
    } 

    if (!configData.contains("molecules")||!configData["molecules"].is_object()) {
        configData["molecules"]=json::object();
    }

    configData["additionalCompoundNames"].push_back(name);
    configData["molecules"][name]= compoundString;

    compoundNames.push_back(name);
    molecules[name]=compoundString;

    std::transform(name.begin(),name.end(),name.begin(),::tolower);
    searchBarArray.push_back(name);

    std::ofstream outFile("config/config.json");
    if (!outFile.is_open()) {
        error->push("Could not find custom config file");
        std::cerr << "Could not find any config file\n";
        return 0;
    }

    outFile<<configData.dump(4);
    outFile.close();

    return 1;
}

//template