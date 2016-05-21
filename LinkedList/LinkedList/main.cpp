#include "Calculations.h"

int main (int argc, char *argv[] ) { 
	Calculations c;
	std::cout << "\n\n" << c.SearchX(.45,15,0.00001) << "\n\n";
	std::cout << "\n\n" << c.SearchX(.495,4,0.00001) << "\n\n";
	std::cout << "\n\n" << c.SearchX(.2,6,0.00001) << "\n\n";
	system("pause");
}	