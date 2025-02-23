#ifndef CONFIG_H
#define CONFIG_H

#include "StdLibDependencies.h"
#include "GUIDependencies.h"

//Window
    extern const char* windowName;
    extern ImVec4 windowColor;
    extern int windowHeight;
    extern int windowWidth;
    extern int largeWindowHeight;

    extern const char* fontFile;

    extern const ImWchar ranges[];

    extern const char* molecularFormulaFontFile;

    extern double windowSmallFontSize;
    extern double windowLargeFontSize;

    extern double elementCompoundButtonFontSize;
 



//Top Menu 
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

        //maybe black bakground





        extern ImU32 scrollBarColor;

            //change c olors for window tomorrow
        extern double scrollBarCurve;
        
        extern std::array<int,8> initialElements;

        extern double initialElementHeightPerCent;
        extern double scrollerHeightPerCent;
        extern double minimumWindowPerCent;
        extern int offset;
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






#endif