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

	//The two numbers that we test the operations on
	std::string lStr = "200";
	std::string rStr = "3204";

	std::cout << "Constructing default Integer: " << std::endl;
	cosc326::Integer test = cosc326::Integer();
	std::cout << test.toString() << std::endl;

	std::cout << "Constructing Integer from string: " << std::endl;
	test = cosc326::Integer(lStr);
	std::cout << test.toString() << std::endl;
		
	std::cout << "Copying integer: " << std::endl;
	test = cosc326::Integer(test);
	std::cout << test.toString() << std::endl;

	std::cout << "j = ";
	cosc326::Integer i = cosc326::Integer(lStr);
	test = i;
	std::cout << test.toString() << std::endl;
	
	std::cout << "+j = ";
	std::cout << (+test).toString() << std::endl;

	std::cout << "-j = ";
	std::cout << (-test).toString() << std::endl;

	std::cout << std::endl;
	std::cout << "LHS = " + lStr + ", RHS = " + rStr << std::endl;
	cosc326::Integer lhs = cosc326::Integer(lStr);
	cosc326::Integer rhs = cosc326::Integer(rStr);
	std::cout << std::endl;

	std::cout << lStr + " + " + rStr + " = ";
	std::cout << (lhs + rhs).toString() << std::endl;
	
	std::cout << "-" + lStr + " + " + rStr + " = ";
	std::cout << ((-lhs) + rhs).toString() << std::endl;

	std::cout << lStr + " + (-" + rStr + ") = ";
	std::cout << (lhs + (-rhs)).toString() << std::endl;

	std::cout << "-(" + lStr + ") + (-" + rStr + ") = ";
	std::cout << ((-lhs) + (-rhs)).toString() << std::endl;
	
	std::cout << lStr + " - " + rStr + " = ";
	std::cout << (lhs - rhs).toString() << std::endl;
	
	std::cout << "-(" + lStr + ") - " + rStr + " = ";
	std::cout << ((-lhs) - rhs).toString() << std::endl;
		
	std::cout << lStr + " - (-" + rStr + ") = ";
	std::cout << (lhs - (-rhs)).toString() << std::endl;
		
	std::cout << "-(" + lStr + ") - (-" + rStr + ") = ";
	std::cout << ((-lhs) - (-rhs)).toString() << std::endl;

	std::cout << lStr + " * " + rStr + " = ";
	std::cout << (lhs * rhs).toString() << std::endl;

	return 0;
}
