#include <iostream>
#include "LinkedList.h"
#include <cmath>

const double euler = std::exp(1.0);

static class Calculations{
public:
	double xAvg;
	double yAvg;	
	double xSum;
	double ySum;	
	double xSqrSum;
	double ySqrSum;
	double xySum;
	double b1;
	double b0;
	double stdDeviationX;
	double stdDeviationY;
	double correlationCoeficient;

	Calculations(){
		xAvg = 0;
		yAvg = 0;		
		xSum = 0;
		ySum = 0;		
		xSqrSum = 0;
		ySqrSum = 0;
		xySum = 0;
		b1 = 0;
		b0 = 0;
		stdDeviationX = 0;
		stdDeviationY = 0;
		correlationCoeficient = 0;
	}
	Calculations(LinkedList& l){
		for ( int i = 0; i < l.Length(); i++){
			xSum += l[i]->X();
			ySum += l[i]->Y();

			xSqrSum += (l[i]->X() * l[i]->X());
			ySqrSum += (l[i]->Y() * l[i]->Y());

			xySum += (l[i]->X() * l[i]->Y());
		}
	}

	void Mean(LinkedList& l, bool ln){
		for (int i = 0; i < l.Length(); i++){
			if (ln){
				xSum += log(l[i]->X());
				ySum += log(l[i]->Y());
			}
		}
		xAvg = xSum / l.Length();
		yAvg = ySum / l.Length();
	}
	void StdDeviation(LinkedList& l, bool ln){	
		double total = 0; 
		double accumX = 0; 
		double accumY = 0;
		double x, y =0;
		for ( int i = 0; i < l.Length(); i++ ) {
			
			if (!ln){
				x = l[i]->X();
				y = l[i]->Y();
			}else{
				x = log(l[i]->X());
				y = log(l[i]->Y());
			}
			accumX += (x - xAvg) * (x- xAvg);
			accumY += (y - yAvg) * (y - yAvg);
		}

		stdDeviationX = sqrt(accumX / (l.Length()-1));
		stdDeviationY = sqrt(accumY / (l.Length()-1));
	}
	void LinearRegression(LinkedList& l, double xk){				
		double CorCoeSqr = 0;

		xAvg = xSum / l.Length();
		yAvg = ySum / l.Length();

		b1 = ( xySum - ( l.Length() * xAvg * yAvg ) ) / ( xSqrSum - ( l.Length() * xAvg * xAvg ) );
		b0 = yAvg - b1 * xAvg;
	}	
	
	double Correlation(LinkedList& l){
		correlationCoeficient = (l.Length() * xySum - xSum * ySum) / sqrt( (l.Length() * xSqrSum - xSum * xSum ) * ( l.Length() * ySqrSum - ySum * ySum ) );
		return correlationCoeficient;
	}

	double PredictNext(double x){
		return b0 + b1 * x;
	}

	void CalculateRanges(){
		double lVS = xAvg - 2 * stdDeviationX;
		double lS  = xAvg - stdDeviationX;
		double lM  = xAvg;
		double lL  = xAvg + stdDeviationX;
		double lVL = xAvg + 2 * stdDeviationX;
		std::cout << "Ranges are as follow: \n";
		std::cout << "===========================\n";
		std::cout << "Very Small :" << pow(euler,lVS) << "\n";
		std::cout << "Small      :" << pow(euler,lS)  << "\n";
		std::cout << "Medium     :" << pow(euler,lM)  << "\n";
		std::cout << "Big        :" << pow(euler,lL)  << "\n";
		std::cout << "Very Big   :" << pow(euler,lVL) << "\n";
		std::cout << "===========================\n";
	}

};
