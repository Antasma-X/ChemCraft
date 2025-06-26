#ifndef UIGENERATION_H
#define UIGENERATION_H

#include "StdLibDependencies.h"
#include "GUIDependencies.h"
#include"compound.h"

#include "config.h"
#include "values.h" 
#include "render.h"
#include "error.h"
namespace UI
{
    /*
    Generates Top Menu Main Menu Bar

    Note: The main menu bar also contains buttons

    There are many fonts you can use for various submenues

    Uses bools to open or not open widgets
    Settings:
        Used to change properties such as window color and text color
        Any changed property in settings is saved to customConfigFile

    Edit:
        Can add hydrogen atoms to all unstable atoms to fulfil atom valencies
        Can copy all current compound strings on screen
        Can paste any compound string
        Can Cut Too

        i will figure out undo and redo one day

    Insert:
        A drop down menu where you can paste from a file or paste into a textbox. It adds to the current compounds and doesn't replace them
        The new file does not become the current file

    Open:
        Opens a file from NFD and removes all current compounds on screen. The file opened becomes the current file

    Save:
        Saves the compounds' strings to the current file or to a new file(SaveAs()) using NFD if no file is being used right now

    Save as:
        Uses NFD to find a file and saves compounds to it. Makes the file selected the current file

    Help:
        Opens github link

    */
    void TopMenu();

    /*
    Copies current compounds' strings on screen and then removes them
    */
    static void Cut();

    /*
    Copies current compounds' strings on screen 
    */
    static void Copy();
    
    /*
    Pastes compounds from clipBoard
    */
    static void Paste();

    /*
    Filter for Input from text
    */
    static int FilterLettersCompoundString(ImGuiInputTextCallbackData* data);
    
    /*
    Opens a file from NFD and removes all current compounds on screen. The file opened becomes the current file
    */
    static void open();

    /*
    Saves the compounds' strings to the current file 
    */
    static void save();

    /*
    Opens NFD to open a file and then saves all the compounds' strings to the file. The file selected becomes the current file
    */
    static void saveAs();

    /*
    Opens github page using the platform's CLI command
    */
    static void openHelpLink();

    /*
    Creates Side Menu of elements and compounds
    It automatically resizes with the window
    It calls ElementAndCompoundMenu() and SearchBar()

    You pass in the various fonts required which are generated before loop
    */
    void SideMenu( ImFont* searchFontSmall, ImFont* searchFontLarge,ImFont* childWindowFontSmall, ImFont* childWindowFontLarge,ImFont* numberFont,ImFont* symbolFont,ImFont* nameFont,ImFont* massFont,ImFont* compoundNameFont,ImFont* molecularFormulaFont);

    /*
    Generates the overall look and relationship between element and compound child menus
    Uses a splitter to adjust size of each child window
    Resizes child windows with window
    Calls the button functions for compounds and elements

    Note: For the element menu we can have a vector of initial elemnts to show up first

    You pass in the small and large fonts for both child windows

    You also pass in search bar filtered words
    */
    static void ElementAndCompoundMenu(ImFont* childWindowFontSmall, ImFont* childWindowFontLarge,ImFont* numberFont,ImFont* symbolFont,ImFont* nameFont,ImFont* massFont,ImFont* compoundNameFont,ImFont* molecularFormulaFont,const std::vector<std::string>& currentSearchArray);

    /*
    Generates an element button in the element child window
    You can left click to create default element 
    You can right click to open up popup to adjusts mass and charge
    */
    static void GenerateElementButton(int atomicNumber, double sizeChange,ImFont* numberFont,ImFont* symbolFont,ImFont* nameFont,ImFont* massFont,bool isFirstBox);
    
    /*
    Generates a compound button in compound child window with their name and moleculor formula
    */
    static void GenerateCompoundButton(int compoundNumber, double sizeChange,ImFont* compoundNameFont,ImFont* molecularFormulaFont,bool isFirstBox);

    /*
    Creates search bar at bottom of side menu
    Typing in it filters the elements and compounds
    Calls Search glass image and search placeholder creation functions

    It alters currentSearchArray to filter elements and compounds
    */
    static void SearchBar(ImFont* searchFontSmall, ImFont* searchFontLarge,std::vector<std::string>& currentSearchArray);

    /*
    Loads Magnifying glass pic
    */
    static void LoadMagnifyingGlass(double searchBarHeightPerCent);

    /*
    Filters characters allowed in search bar
    */
    static int FilterCharactersSearchBar(ImGuiInputTextCallbackData* data);


} 




#endif