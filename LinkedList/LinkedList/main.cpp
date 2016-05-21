#include "Calculations.h"

int main (int argc, char *argv[] ) { 
	Calculations c;
	//std::cout << "\n\n" << c.CalculateFunctionArea(0,1.1,9,10,0.00001,Calculations::IntegrateDistributionT) << "\n\n";
	//std::cout << "\n\n" << c.CalculateFunctionArea(0,1.182,10,10,0.00001,Calculations::IntegrateDistributionT) << "\n\n";
	std::cout << "\n\n" << c.CalculateFunctionArea(0,2.75,30,10,0.00001,Calculations::IntegrateDistributionT) << "\n\n";
	system("pause");
}	