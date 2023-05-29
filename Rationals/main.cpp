/*
	Test main for Rational and Integer
*/

#include <iostream>
using namespace std;

#include "Integer.h"
#include "Rational.h"

using namespace cosc326;

int main() {
	bool running = true;
	while(running){
		Integer lhs;	//This will be used for the tests that require only 1 number
		std::cout << "Pick a number for LHS:";
		std::cin >> lhs;
		Integer rhs;
		std::cout << "Pick a number for RHS:";
		std::cin >> rhs;
		//--------------------------------------------------
		std::cout << "LHS = " << lhs << ", RHS = " << rhs << std::endl;
		try{
			std::cout << "lhs.toInt() = ";
			std::cout << lhs.toInt() << std::endl;
		}catch(const std::exception& e){	//Couldn't convert to int
			std::cerr << e.what() << '\n';
		}
		std::cout << std::endl << "Addition:" << std::endl;
		std::cout << lhs << " + " << rhs << " = ";
		std::cout << (lhs + rhs) << std::endl;
		
		std::cout << "-" << lhs << " + " << rhs << " = ";
		std::cout << ((-lhs) + rhs) << std::endl;

		std::cout << lhs << " + (-" << rhs << ") = ";
		std::cout << (lhs + (-rhs)) << std::endl;

		std::cout << "-(" << lhs << ") + (-" << rhs << ") = ";
		std::cout << ((-lhs) + (-rhs)) << std::endl;
		
		std::cout << std::endl << "Subtraction:" << std::endl;

		std::cout << lhs << " - " << rhs << " = ";
		std::cout << (lhs - rhs) << std::endl;
		
		std::cout << "-(" << lhs << ") - " << rhs << " = ";
		std::cout << ((-lhs) - rhs) << std::endl;
			
		std::cout << lhs << " - (-" << rhs << ") = ";
		std::cout << (lhs - (-rhs)) << std::endl;
			
		std::cout << "-(" << lhs << ") - (-" << rhs << ") = ";
		std::cout << ((-lhs) - (-rhs)) << std::endl;

		std::cout << std::endl << "Multiplication:" << std::endl;

		std::cout << lhs << " * " << rhs << " = ";
		std::cout << (lhs * rhs) << std::endl;

		std::cout << "-(" << lhs << ") * " << rhs << " = ";
		std::cout << ((-lhs) * rhs) << std::endl;

		std::cout << lhs << " * (-" << rhs << ") = ";
		std::cout << (lhs * (-rhs)) << std::endl;

		std::cout << "-(" << lhs << ") * (-" << rhs << ") = ";
		std::cout << ((-lhs) * (-rhs)) << std::endl;

		
		std::cout << std::endl << "Division:" << std::endl;
		
		std::cout << lhs << " / " << rhs << " = ";
		std::cout << (lhs / rhs) << std::endl;

		std::cout << "-(" << lhs << ") / " << rhs << " = ";
		std::cout << ((-lhs) / rhs) << std::endl;

		std::cout << lhs << " / (-" << rhs << ") = ";
		std::cout << (lhs / (-rhs)) << std::endl;

		std::cout << "-(" << lhs << ") / (-" << rhs << ") = ";
		std::cout << ((-lhs) / (-rhs)) << std::endl;

		std::cout << std::endl;

		std::cout << lhs << " % " << rhs << " = ";
		std::cout << (lhs % rhs) << std::endl;

		std::cout << "-(" << lhs << ") % " << rhs << " = ";
		std::cout << ((-lhs) % rhs) << std::endl;

		std::cout << lhs << " % (-" << rhs << ") = ";
		std::cout << (lhs % (-rhs)) << std::endl;

		std::cout << "-(" << lhs << ") % (-" << rhs << ") = ";
		std::cout << ((-lhs) % (-rhs)) << std::endl;

		std::cout << std::endl << "Boolean operators:" << std::endl;

		std::cout << lhs << " < " << rhs << ": ";
		std::cout << (lhs < rhs) << std::endl;

		std::cout << lhs << " > " << rhs << ": ";
		std::cout << (lhs > rhs) << std::endl;

		std::cout << lhs << " <= " << rhs << ": ";
		std::cout << (lhs <= rhs) << std::endl;

		std::cout << lhs << " >= " << rhs << ": ";
		std::cout << (lhs >= rhs) << std::endl;

		std::cout << lhs << " == " << rhs << ": ";
		std::cout << (lhs == rhs) << std::endl;

		std::cout << lhs << " != " << rhs << ": ";
		std::cout << (lhs != rhs) << std::endl;

		std::cout << std::endl << "Greatest common divisor:" << std::endl;

		std::cout << "gcd(" << lhs << ", " << rhs << ") = ";
		std::cout << gcd(lhs, rhs) << std::endl;

		std::cout << std::endl << "Rationals:" << std::endl;
		std::cout << "Give me a string for a rational: ";
		Rational r;
		std::cin >> r;
		std::cout << r << std::endl; 

		std::cout << std::endl << "Do you wanna try again? (Type '1' for yes, and '0' for no.)" << std::endl;
		Integer answer;
		std::cin >> answer;
		if(answer == Integer()){
			running = false;
		}
	}
	return 0;
}
