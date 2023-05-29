#include "Rational.h"
#include <sstream>

namespace cosc326 {

	const Integer null;
	const Integer one = Integer("1");
	const Rational rNull;

	Rational::Rational() {
		this->numerator = null;
		this->denominator = one;
		this->ones = null;
		this->positive = true;
	}

	Rational::Rational(const std::string& str) {
		std::string rStr = "";
		char first = str.at(0);
		switch (first){		//Remove signs (+/-) from string
		case '+': 
			positive = true;
			rStr = str.substr(1);
			break;
		case '-':
			positive = false;
			rStr = str.substr(1);
			break;
		default:
			positive = true;
			rStr = str;
			break;
		}

		int dotPos = rStr.find('.');
		int slashPos = rStr.find('/');

		std::string oneStr = rStr.substr(0, dotPos);
		std::string numStr = rStr.substr(dotPos + 1, slashPos - dotPos - 1);
		std::string denomStr = rStr.substr(slashPos + 1);

		this->numerator = Integer(numStr);
		this->denominator = Integer(denomStr);
		this->ones = Integer(oneStr);
		this->scaleDown();
		this->extractOnes();
	}

	Rational::Rational(const Rational& r) {
		this->numerator = r.numerator;
		this->denominator = r.denominator;
		this->ones = r.ones;
		this->positive = r.positive;
	}

	Rational::Rational(const Integer& a) {
		this->numerator = a;
		this->denominator = one;
		this->ones = null;
		this->positive = a.prop.positive;
	}

	Rational::Rational(const Integer& a, const Integer& b) {
		this->numerator = a;
		this->denominator = b;
		this->ones = null;
		//Positive if numerator and denominator have same sign (+/-)
		if(a.prop.positive == b.prop.positive){
			this->positive = true;
		}else{
			this->positive = false;
		}
	}

	Rational::Rational(const Integer& a, const Integer& b, const Integer& c) {
		this->numerator = a;
		this->denominator = b;
		this->ones = c;
		//Same sign as ones if numerator and denominator have same sign (+/-)
		if(a.prop.positive == b.prop.positive){
			this->positive = ones.prop.positive;
		}else{
			this->positive = !ones.prop.positive;
		}
	}

	Rational::~Rational() {

	}

	Rational& Rational::operator=(const Rational& r) {
		this->numerator = r.numerator;
		this->denominator = r.denominator;
		this->ones = r.ones;
		this->positive = r.positive;
		return *this;
	}

	Rational Rational::operator-() const {
		Rational r;
		if(r == rNull){
			return r;	//0 should always be positive
		}
		r.positive = !this->positive;
		return r;
	}

	Rational Rational::operator+() const {
		return *this;
	}

	Rational& Rational::operator+=(const Rational& r) {
		*this = *this + r;
		return *this;
	}

	Rational& Rational::operator-=(const Rational& r) {
		*this = *this - r;
		return *this;
	}

	Rational& Rational::operator*=(const Rational& r) {
		*this = *this * r;
		return *this;
	}

	Rational& Rational::operator/=(const Rational& r) {
		*this = *this / r;
		return *this;
	}

	Rational& Rational::scaleBy(const Integer scalar){
		this->numerator *= scalar;
		this->denominator *= scalar;
		return *this;
	}

	Rational& Rational::scaleDown(){
		const Integer divisor = gcd(this->numerator, this->denominator);
		this->numerator /= divisor;
		this->denominator /= divisor;
		return *this;
	}

	Rational& Rational::extractOnes(){
		this->ones += (this->numerator / this->denominator);
		this->numerator = (this->numerator % this->denominator);
		return *this;
	}

	Rational operator+(const Rational& lhs, const Rational& rhs) {

		Integer ones = lhs.ones + rhs.ones;
		//This formula gives lcm(lhs, rhs), the least common multiplier, which is our new denominator:
		Integer denominator = (lhs.denominator * rhs.denominator) / gcd(lhs.denominator, rhs.denominator);

		//Scaling lhs:
		Integer scalar = denominator / lhs.denominator;
		Rational lhsScaled = lhs;
		lhsScaled.scaleBy(scalar);

		//Scaling rhs:
		scalar = denominator / rhs.denominator;
		Rational rhsScaled = rhs;
		rhsScaled.scaleBy(scalar);
		
		Integer numerator = lhsScaled.numerator + rhsScaled.numerator;

		Rational result;
		result.numerator = numerator;
		result.denominator = denominator;
		result.ones = ones;
		result.scaleDown();
		result.extractOnes();
		return result;
	}

	Rational operator-(const Rational& lhs, const Rational& rhs) { //TODO This is just a copy of the operator+

		Integer ones = lhs.ones + rhs.ones;
		//This formula gives lcm(lhs, rhs), the least common multiplier, which is our new denominator:
		Integer denominator = (lhs.denominator * rhs.denominator) / gcd(lhs.denominator, rhs.denominator);

		//Scaling lhs:
		Integer scalar = denominator / lhs.denominator;
		Rational lhsScaled = lhs;
		lhsScaled.scaleBy(scalar);

		//Scaling rhs:
		scalar = denominator / rhs.denominator;
		Rational rhsScaled = rhs;
		rhsScaled.scaleBy(scalar);
		
		Integer numerator = lhsScaled.numerator + rhsScaled.numerator;

		Rational result;
		result.numerator = numerator;
		result.denominator = denominator;
		result.ones = ones;
		result.scaleDown();
		result.extractOnes();
		return result;
	}

	Rational operator*(const Rational& lhs, const Rational& rhs) {
		return lhs;
	}

	Rational operator/(const Rational& lhs, const Rational& rhs) {
		return lhs;
	}

	std::ostream& operator<<(std::ostream& os, const Rational& r) {
		std::stringstream ss;
		if(!r.positive){
			ss << '-';	//Add sign if r is negative
		}
		int onesSize = r.ones.nDigits();
		for(int i = 0; i < onesSize; i++){
			int index = onesSize - i - 1;	//Read vector backwards (read number from the left)
			ss << r.ones.prop.digits[i];	//print digit
		}
		ss << '.';
		int numSize = r.numerator.nDigits();
		for(int i = 0; i < numSize; i++){
			int index = numSize - i - 1;		//Read vector backwards (read number from the left)
			ss << r.numerator.prop.digits[i];	//print digit
		}
		ss << '/';
		int denomSize = r.denominator.nDigits();
		for(int i = 0; i < denomSize; i++){
			int index = denomSize - i - 1;	//Read vector backwards (read number from the left)
			ss << r.denominator.prop.digits[i];	//print digit
		}
		os << ss.str();
		return os;
	}

	std::istream& operator>>(std::istream& is, Rational& r) {
		std::string input;
		is >> input;
		r = Rational(input);
		return is;
	}

	bool operator<(const Rational& lhs, const Rational& rhs) {
		return true;
	}

	bool operator> (const Rational& lhs, const Rational& rhs) {
		return true;
	}

	bool operator<=(const Rational& lhs, const Rational& rhs) {
		return true;
	}

	bool operator>=(const Rational& lhs, const Rational& rhs) {
		return true;
	}

	bool operator==(const Rational& lhs, const Rational& rhs) {
		return true;
	}

	bool operator!=(const Rational& lhs, const Rational& rhs) {
		return true;
	}

}
