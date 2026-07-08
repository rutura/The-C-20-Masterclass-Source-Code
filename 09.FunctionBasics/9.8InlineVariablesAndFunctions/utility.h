#include <iostream>

 inline double threashold {11.1}; // Definition


//Defintion
 inline double add(double a, double b){
	if( (a > 11.1) && (b > 11.1)){
		return a + b;
	}else{
		return threashold;
	}
}