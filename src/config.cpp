#include "config.h"

const char* windowName="Nomenclature";
ImVec4 windowColor=ImVec4(0.12f,0.06f,0.21f,1.00f);
int windowHeight=720;
int windowWidth=1280;
int largeWindowHeight = 950;

const char* fontFile="/mnt/c/Windows/Fonts/arial.ttf";

const ImWchar ranges[] = {
    0x0020, 0x007E,  // Basic ASCII
    0x2070, 0x209F,  // Superscripts and subscripts
    0
};

const char* molecularFormulaFontFile="/usr/share/fonts/truetype/noto/NotoSans-Regular.ttf";


double windowSmallFontSize=18.0f;
double windowLargeFontSize=25.0f;

double elementCompoundButtonFontSize=25.0f;



 
ImVec4 topMenuButtonColor=ImVec4(0.14f, 0.14f, 0.14f, 1.0f);
ImVec4 topMenuHoveredButtonColor=ImVec4(0.26f, 0.59f, 0.98f, 0.80f);
ImVec4 topMenuActiveButtonColor=ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
ImVec4 topMenuTextColor=ImVec4(0.90f, 0.90f, 0.90f, 1.00f);

ImVec4 fileNameColor=ImVec4(0.90f, 0.90f, 0.90f, 1.00f);

ImVec4 settingsColorPickersTextColor=ImVec4(0.90f, 0.90f, 0.90f, 1.00f);
ImVec4 settingsColorPickersBackgroundColor=ImVec4(0.06f, 0.06f, 0.06f, 0.94f);
ImVec4 settingsColorPickersTitleBarColor=ImVec4(0.098f, 0.098f, 0.439f, 1.0f);
ImVec4 settingsColorPickersActiveTitleBarColor=ImVec4(0.200f, 0.220f, 0.270f, 1.0f);
ImVec4 settingsColorPickersCollapsedTitleBarColor=ImVec4(0.098f, 0.098f, 0.439f, 1.0f);

ImVec4 openFilePopUpTextColor=ImVec4(0.90f, 0.90f, 0.90f, 1.00f);
ImVec4 openFilePopUpBackgroundColor=ImVec4(0.06f, 0.06f, 0.06f, 0.94f);
ImVec4 openFilePopUpTitleBarColor=ImVec4(0.098f, 0.098f, 0.439f, 1.0f);
ImVec4 openFilePopUpActiveTitleBarColor=ImVec4(0.200f, 0.220f, 0.270f, 1.0f);
ImVec4 openFilePopUpCollapsedTitleBarColor=ImVec4(0.098f, 0.098f, 0.439f, 1.0f);

ImVec4 insertDirectColor=ImVec4(0.16f, 0.29f, 0.48f, 0.54f);
ImVec4 insertDirectHoveredColor=ImVec4(0.26f, 0.59f, 0.98f, 0.40f);
ImVec4 insertDirectTypingColor=ImVec4(0.26f, 0.59f, 0.98f, 0.67f);
ImVec4 insertDirectTextColor=ImVec4(0.90f, 0.90f, 0.90f, 1.00f);

const char* disallowedCharCompoundString="!@#$%^";

const char* helpLink="github.com/";

int topMenu_____Padding=10;

ImVec4 sideMenuColor=ImVec4(0.1373f, 0.0392f, 0.3020f, 1.0f);
int minimumSideMenuWidth=200;
double initialSideMenuWidthPerCent=0.3;

double childWindowSmallFontSize=25.0f;
double childWindowLargeFontSize=35.0f;

ImVec4 elementWindowColor=ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
ImVec4 elementWindowBorderColor=ImVec4(0.43f, 0.43f, 0.50f, 0.50f);
ImVec4 elementWindowBorderShadowColor=ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
ImVec4 elementWindowTextColor=ImVec4(0.90f, 0.90f, 0.90f, 1.00f);

ImVec2 elementButtonSize=ImVec2(150,150);
ImU32 elementButtonColor=IM_COL32(255, 255,255, 255);
ImU32 elementButtonBorderColor=IM_COL32(0, 0, 0, 255);
ImU32 elementButtonHoveredColor=IM_COL32(100, 100,100, 100);
ImU32 elementButtonClickedColor=IM_COL32(255, 255,255, 255);

double elementButtonCurve=15.0f;
double elementButtonBorderThickness=10.0f;

ImVec4 customElementPopUpTextColor=ImVec4(0.90f, 0.90f, 0.90f, 1.00f);
ImVec4 customElementPopUpBackgroundColor=ImVec4(0.06f, 0.06f, 0.06f, 0.94f);
ImVec4 customElementPopUpTitleBarColor=ImVec4(0.098f, 0.098f, 0.439f, 1.0f);
ImVec4 customElementPopUpActiveTitleBarColor=ImVec4(0.200f, 0.220f, 0.270f, 1.0f);
ImVec4 customElementPopUpCollapsedTitleBarColor=ImVec4(0.098f, 0.098f, 0.439f, 1.0f);

double numberFontSize=25.0f;
double symbolFontSize=50.0f;
double nameFontSize=20.0f;
double massFontSize=25.0f;

ImU32 atomicNumberColor=IM_COL32(0, 0, 0, 255);
ImU32 atomicMassColor=IM_COL32(0, 0, 0, 255);
ImU32 atomicSymbolColor=IM_COL32(0, 0, 0, 255);
ImU32 atomicNameColor=IM_COL32(0, 0, 0, 255);

ImVec2 compoundButtonSize=ImVec2(150,100);

ImU32 compoundButtonBorderColor=IM_COL32(0, 0, 0, 255);








std::vector<ImU32> compoundButtonColors={IM_COL32(123, 45, 67, 255), IM_COL32(89, 234, 120, 255), IM_COL32(200, 50, 90, 255),
IM_COL32(30, 200, 255, 255), IM_COL32(240, 180, 60, 255), IM_COL32(180, 90, 200, 255),
IM_COL32(75, 150, 250, 255), IM_COL32(200, 140, 100, 255), IM_COL32(50, 220, 90, 255),
IM_COL32(180, 50, 180, 255), IM_COL32(100, 250, 100, 255), IM_COL32(255, 60, 90, 255),
IM_COL32(70, 170, 210, 255), IM_COL32(130, 200, 75, 255), IM_COL32(210, 120, 180, 255),
IM_COL32(255, 100, 50, 255), IM_COL32(120, 220, 60, 255), IM_COL32(90, 180, 255, 255),
IM_COL32(40, 250, 130, 255), IM_COL32(190, 90, 230, 255)};

std::vector<ImU32> compoundButtonHoveredColors= {   IM_COL32(255, 30, 70, 255), IM_COL32(80, 200, 255, 255), IM_COL32(180, 50, 100, 255),
IM_COL32(40, 220, 80, 255), IM_COL32(200, 150, 90, 255), IM_COL32(255, 100, 150, 255),
IM_COL32(75, 200, 90, 255), IM_COL32(100, 255, 200, 255), IM_COL32(130, 90, 250, 255),
IM_COL32(255, 60, 180, 255), IM_COL32(180, 130, 50, 255), IM_COL32(220, 80, 220, 255),
IM_COL32(50, 160, 255, 255), IM_COL32(200, 255, 40, 255), IM_COL32(90, 180, 200, 255),
IM_COL32(70, 250, 150, 255), IM_COL32(180, 75, 120, 255), IM_COL32(255, 90, 60, 255),
IM_COL32(40, 140, 220, 255), IM_COL32(100, 210, 180, 255)};
std::vector<ImU32> compoundButtonClickedColors={
IM_COL32(60, 255, 90, 255), IM_COL32(180, 80, 200, 255), IM_COL32(255, 100, 50, 255),
IM_COL32(120, 250, 180, 255), IM_COL32(40, 90, 255, 255), IM_COL32(190, 140, 75, 255),
IM_COL32(255, 80, 180, 255), IM_COL32(70, 200, 250, 255), IM_COL32(210, 50, 120, 255),
IM_COL32(100, 255, 70, 255), IM_COL32(230, 90, 190, 255), IM_COL32(80, 130, 255, 255),
IM_COL32(180, 255, 60, 255), IM_COL32(150, 75, 240, 255), IM_COL32(90, 200, 180, 255),
IM_COL32(40, 170, 220, 255), IM_COL32(120, 255, 130, 255), IM_COL32(255, 40, 90, 255),
IM_COL32(60, 210, 180, 255), IM_COL32(250, 120, 50, 255)};

double compoundButtonBorderThickness=10.0f;
double compoundButtonCurve=15.0f;

double compoundNameSize=20.0f;
double molecularFormulaSize=30.0f;

ImU32 compoundNameColor=IM_COL32(0, 0, 0, 255);
ImU32 molecularFormulaColor=IM_COL32(0, 0, 0, 255);

ImVec4 compoundWindowColor=ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
ImVec4 compoundWindowBorderColor=ImVec4(0.43f, 0.43f, 0.50f, 0.50f);
ImVec4 compoundWindowBorderShadowColor=ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
ImVec4 compoundWindowTextColor=ImVec4(0.90f, 0.90f, 0.90f, 1.00f);

const char* elementTitle="Elements";
const char* compoundTitle="Common Compounds";


ImU32 scrollBarColor=IM_COL32(255,255,255,255);

double scrollBarcurve=15.0f;

std::array<int,8> initialElements={1,2,6,7,8,9,11,17};

double initialElementHeightPerCent=0.6;
double scrollerHeightPerCent=0.025;
double minimumWindowPerCent=0.15;
int offset=2;
int elementCompound_____Padding=10;
int IDKWhyOffset=15;

double searchSmallFontSize=25.0f;
double searchLargeFontSize=35.0f;

ImVec4 searchBarColor=ImVec4(0.16f, 0.29f, 0.48f, 0.54f);
ImVec4 searchBarHoveredColor=ImVec4(0.26f, 0.59f, 0.98f, 0.40f);
ImVec4 searchBarTypingColor=ImVec4(0.26f, 0.59f, 0.98f, 0.67f);
ImVec4 searchBarTextColor=ImVec4(0.90f, 0.90f, 0.90f, 1.00f);

double initialSearchBarHeightPerCent=0.05;
const char* SearchGlass="../Assets/searchGlass.png";
ImVec4 searchGlassTransparency=ImVec4(1.0f, 1.0f, 1.0f, 0.3f);
const char* searchBarLabel="Search..";
ImVec4 searchBarLabelColor=ImVec4(0.9f, 0.9f, 0.9f, 0.2f);
const char* disallowedCharSearchBar="!@#$%^&*\n\t0123456789";
int search___padding=4;