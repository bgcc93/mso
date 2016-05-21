#define _USE_MATH_DEFINES
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
	double functionArea;

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
		functionArea = 0;
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
			}else{
				xSum += l[i]->X();
				ySum += l[i]->Y();
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
	static double Gamma(double x){
		if ( x - 1 < 0){
			return sqrt(M_PI)/2;
		}
		else if( x - 1 == 0){
			return 1;
		}else{
			return ( x * Gamma(x-1) );
		}
	}
	static double  IntegrateDistributionT(double x, double dof){
		return ( Gamma( ( (double)(dof+1) / 2 ) -1 ) / ( pow( ((double)dof * M_PI), .5) * Gamma( ((double)dof/2) - 1 ) ) ) * pow((1 + (x*x)/dof), -1 * (double)(dof+1)/2);
	}
	double CalculateFunctionArea(double xStart, double xEnd, int dof, int segs, double error, double(*f)(double,double) ){
		double g = 0;
		double totalX = xEnd - xStart;
		double w = totalX / segs;
		double w2 = totalX / (segs * 2);
		double area = 0;

		area += f(xStart, dof);
		area += f(xEnd, dof);

		functionArea += area;

		for(int i = 1 ; i < segs; i ++){
			if ( i % 2 == 0 ){area += f( ( totalX / segs * i ), dof) * 2;}
			else{area += f( ( totalX / segs * i ), dof) * 4;}				
		}

		for(int i = 1 ; i < segs * 2; i ++){
			if ( i % 2 == 0 ){functionArea += f( ( totalX / (segs * 2 ) * i ), dof) * 2;}
			else{functionArea += f( ( totalX / (segs * 2) * i) , dof) * 4;}				
		}
		
		area *= w/3;
		functionArea *= w2/3;

		if ( (functionArea - area) > error) {
			functionArea = CalculateFunctionArea(xStart, xEnd, dof, segs*2, error, f);
		}

		return functionArea;
	}
	double round(double value, int precision){
		int adjustment = pow(10,precision);
		return floor( value*(adjustment) + 0.5 )/adjustment;
	}
	double SearchX(double p, int dof, double error){
		double step = 1;
		double x = 1;
		bool add = false;
		bool subtract = false;
		double area = 0;
		do{
			area = CalculateFunctionArea(0,x,dof,20,error,Calculations::IntegrateDistributionT);
			if( area > p ){
				if(add){
					step /= 2;
					add = false;
				}
				x -= step;
				subtract = true;
			}else if ( area < p ){				
				if(subtract){
					step /= 2;
					subtract = false;
				}
				x += step;
				add = true;
			}
			
		}while( round(area,4) != round(p,4) );
		return x;
	}
};
