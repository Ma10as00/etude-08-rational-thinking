/*
	Test main for Rational and Integer
*/

#include <iostream>
using namespace std;

#include "Integer.h"
#include "Integer.cpp"
#include "Rational.h"

using namespace cosc326;

int main() {


	std::cout << "Kia ora World" << std::endl;

	//Change these to test operators on differen numbers
	std::string left = "1230000";
	std::string right = "500003045";
	//--------------------------------------------------

	std::cout << "Constructing default Integer: ";
	cosc326::Integer test = cosc326::Integer();
	std::cout << test.toString() << std::endl;

	std::cout << "Constructing Integer from string '" + left + "': ";
	test = cosc326::Integer(left);
	std::cout << test.toString() << std::endl;
		
	std::cout << "Copying integer: ";
	test = cosc326::Integer(test);
	std::cout << test.toString() << std::endl;

	std::cout << "j = ";
	cosc326::Integer i = cosc326::Integer(left);
	test = i;
	std::cout << test.toString() << std::endl;
	
	std::cout << "+j = ";
	std::cout << (+test).toString() << std::endl;

	std::cout << "-j = ";
	std::cout << (-test).toString() << std::endl;

	std::cout << "j.toInt() = ";
	std::cout << test.toInt() << std::endl;	

	std::cout << std::endl;
	cosc326::Integer lhs = cosc326::Integer(left);
	cosc326::Integer rhs = cosc326::Integer(right);
	std::cout << "LHS = " + left + ", RHS = " + right << std::endl;
	left = lhs.toString(); //Updating from input to the processed numbers, e.g. "00" -> "0"
	right = rhs.toString();

	std::cout << std::endl << "Addition:" << std::endl;
	std::cout << left + " + " + right + " = ";
	std::cout << (lhs + rhs).toString() << std::endl;
	
	std::cout << "-" + left + " + " + right + " = ";
	std::cout << ((-lhs) + rhs).toString() << std::endl;

	std::cout << left + " + (-" + right + ") = ";
	std::cout << (lhs + (-rhs)).toString() << std::endl;

	std::cout << "-(" + left + ") + (-" + right + ") = ";
	std::cout << ((-lhs) + (-rhs)).toString() << std::endl;
	
	std::cout << std::endl << "Subtraction:" << std::endl;

	std::cout << left + " - " + right + " = ";
	std::cout << (lhs - rhs).toString() << std::endl;
	
	std::cout << "-(" + left + ") - " + right + " = ";
	std::cout << ((-lhs) - rhs).toString() << std::endl;
		
	std::cout << left + " - (-" + right + ") = ";
	std::cout << (lhs - (-rhs)).toString() << std::endl;
		
	std::cout << "-(" + left + ") - (-" + right + ") = ";
	std::cout << ((-lhs) - (-rhs)).toString() << std::endl;

	std::cout << std::endl << "Multiplication:" << std::endl;

	std::cout << left + " * " + right + " = ";
	std::cout << (lhs * rhs).toString() << std::endl;

	// std::cout << left + " / " + right + " = ";
	// std::cout << (lhs / rhs).toString() << std::endl;


	return 0;
}
