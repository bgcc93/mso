#include "Calculations.h"

int main (int argc, char *argv[] ) { 
	//Calculations::MeanAndDeviation();
	LinkedList l;
	Calculations c;
	std::cout << "Insert a number or x to start the calculations\n";
	do{
		std::cin.clear();
		double val = 0;
		std::cout << "Number :";
		if ( !(std::cin >> val) ){
			break;
		}
		l.CreateNode(val);
	}while(true);

	c.Mean(l, true);
	c.StdDeviation(l, true);
	c.CalculateRanges();

	system("pause");

	/*
		l.CreateNode(591);
		l.CreateNode(114);
		l.CreateNode(229);
		l.CreateNode(230);
		l.CreateNode(270);
		l.CreateNode(128);
		l.CreateNode(1657);
		l.CreateNode(624);
		l.CreateNode(1503);
		*/
}	