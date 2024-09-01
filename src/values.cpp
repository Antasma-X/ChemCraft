#include <string>
#include <vector>
#include <iostream>


std::vector<std::string> symbols={"H","He","Li","Be","B","C","N","O","F","Ne","Na","Mg","Al","Si","P","S","Cl","Ar","K","Ca","Sc"
,"Ti","V","Cr","Mn","Fe","Co","Ni","Cu","Zn","Ga","Ge","As","Se","Br","Kr","Rb","Sr","Y","Zr","Nb","Mo","Tc","Ru","Rh","Pd","Ag",
"Cd","In","Sn","Sb","Te","I","Xe","Cs","Ba","La","Ce","Pr","Nd","Pm","Sm","Eu","Gd","Tb","Dy","Ho","Er","Tm","Yb","Lu","Hf","Ta",
"W","Re","Os","Ir","Pt","Au","Hg","Tl","Pb","Bi","Po","At","Rn","Fr","Ra","Ac","Th","Pa","U","Np","Pu","Am","Cm","Bk","Cf","Es",
"Fm","Md","No","Lr","Rf","Db","Sg","Bh","Hs","Mt","Ds","Rg","Cn","Nh","Fl","Mc","Lv","Ts","Og"};

std::vector<std::string> names={"Hydrogen", "Helium", "Lithium", "Beryllium", "Boron", "Carbon", "Nitrogen", "Oxygen", "Fluorine",
 "Neon", "Sodium", "Magnesium", "Aluminum", "Silicon", "Phosphorus", "Sulfur", "Chlorine", "Argon", "Potassium", "Calcium", "Scandium",
  "Titanium", "Vanadium", "Chromium", "Manganese", "Iron", "Cobalt", "Nickel", "Copper", "Zinc", "Gallium", "Germanium", "Arsenic",
   "Selenium", "Bromine", "Krypton", "Rubidium", "Strontium", "Yttrium", "Zirconium", "Niobium", "Molybdenum", "Technetium", "Ruthenium", 
   "Rhodium", "Palladium", "Silver", "Cadmium", "Indium", "Tin", "Antimony", "Tellurium", "Iodine", "Xenon", "Cesium", "Barium", "Lanthanum", 
   "Cerium", "Praseodymium", "Neodymium", "Promethium", "Samarium", "Europium", "Gadolinium", "Terbium", "Dysprosium", "Holmium", "Erbium", 
   "Thulium", "Ytterbium", "Lutetium", "Hafnium", "Tantalum", "Tungsten", "Rhenium", "Osmium", "Iridium", "Platinum", "Gold", "Mercury", "Thallium", 
   "Lead", "Bismuth", "Polonium", "Astatine", "Radon", "Francium", "Radium", "Actinium", "Thorium", "Protactinium", "Uranium", "Neptunium", "Plutonium", 
   "Americium", "Curium", "Berkelium", "Californium", "Einsteinium", "Fermium", "Mendelevium", "Nobelium", "Lawrencium", "Rutherfordium", "Dubnium", "Seaborgium", 
   "Bohrium", "Hassium", "Meitnerium", "Darmstadtium", "Roentgenium", "Copernicium", "Nihonium", "Flerovium", "Moscovium", "Livermorium", "Tennessine", "Oganesson"};

//2 decimal places(I rounded some off because theyre small). Source: https://pubchem.ncbi.nlm.nih.gov/ptable/atomic-mass/
std::vector<double> masses={1,4,7,9.,10.81,12,14,16,19,20,23,24,27,28,31,32,35.5,40,39,40,44.95,47.87,50.94,52,54.94,55.84,58.93,58.69,63.55,65.4,69.72,72.63,74.92,78.97,79.9,
83.8,85.46,87.62,88.9,91.22,92.91,95.95,96.91,101.1,102.9,106.42,107.87,112.41,114.82,118.71,121.76,127.6,126.9,131.29,132.9,137.33,138.9,140.12,140.91,144.24,144.91,150.4,151.96,
157.2,158.92,162.5,164.93,167.26,168.93,173.05,174.97,178.49,180.95,183.84,186.21,190.2,192.22,195.08,196.97,200.59,204.38,207,208.98,208.98,209.99,222.02,223.02,226.02,227.03,232.04,
231.03,238.03,237.05,244.06,243.06,247.07,247.07,251.08,252.08,257.09,258.1,259.1,266.12,267.12,268.13,269.13,270.13,269.133,277.15,282.17,282.17,286.18,286.18,290.19,290.2,293.20,294.21,295.22};





