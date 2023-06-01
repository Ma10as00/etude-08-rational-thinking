#include "Rational.h"
#include <sstream>

namespace cosc326 {

	const Integer null;
	const Integer one = Integer("1");
	const Rational rNull;	// null.null/one

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
		bool hasDot = (dotPos != std::string::npos);
		int slashPos = rStr.find('/');
		bool hasSlash = (slashPos != std::string::npos);

		std::string oneStr;
		std::string numStr;
		std::string denomStr;

		if(hasDot && hasSlash){
			oneStr = rStr.substr(0, dotPos);
			numStr = rStr.substr(dotPos + 1, slashPos - dotPos - 1);
			denomStr = rStr.substr(slashPos + 1);
		}
		else if(!hasDot && hasSlash){
			oneStr = "0";	//Ones is set to 0 by default.
			numStr = rStr.substr(0,slashPos);
			denomStr = rStr.substr(slashPos + 1);
		}
		else if(hasDot && !hasSlash){
			oneStr = rStr.substr(0, dotPos);
			numStr = rStr.substr(dotPos + 1);
			denomStr = "1"; //Denominator is set to 1 by default.
		}
		else{
			oneStr = rStr;	//The string is just an integer
			numStr = "0";	//Numerator is 0 by default
			denomStr = "1";	//Denominator is 1 by default
		}

		this->ones = Integer(oneStr);
		this->numerator = Integer(numStr);
		this->denominator = Integer(denomStr);
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
		Rational r = *this;
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

	/* Scales both the numerator and the dominator by the same scalar.
	This does not change the value of the Rational. */
	Rational& Rational::scaleBy(const Integer scalar){
		this->numerator *= scalar;
		this->denominator *= scalar;
		return *this;
	}

	/* Scales the Rational, so the numerator and the denominator are as small as possible. */
	Rational& Rational::scaleDown(){
		if(numerator == null){
			this->denominator = one; // 0/x = 0/1
		}else{
			const Integer divisor = gcd(this->numerator, this->denominator);
			this->numerator /= divisor;
			this->denominator /= divisor;
		}
		return *this;
	}

	/* If the fraction >= 1, this puts the 1 in front of the fraction and reduces the numerator. */
	Rational& Rational::extractOnes(){
		this->ones += (this->numerator / this->denominator);
		this->numerator = (this->numerator % this->denominator);
		return *this;
	}

	/* Puts all the ones into the fraction, so that ones = null, but the Rational hasn't changed value. */
	Rational& Rational::fractionizeOnes(){
		this->numerator += this->ones * this->denominator;
		this->ones = null;
		return *this;
	}

	/* Raises the rational to the power of -1. Useful for division. */
	Rational& Rational::flip(){
		this->fractionizeOnes();
		//Numerator and denominator swap places:
		Integer newNum = this->denominator;
		this->denominator = this->numerator;
		this->numerator = newNum;
		//Simplify:
		this->scaleDown();
		this->extractOnes();
		return *this;
	}

	/* Finds the lowest common multiplier, i.e. the lowest number that is divisible by both lhs and rhs. 
	This is particularly useful when adding rationals together. 
	*/
	Integer lcm(const Integer& lhs, const Integer& rhs){
		const Integer lcm = (lhs * rhs) / gcd(lhs, rhs);
		return lcm;
	}

	void scaleToCommonDenominator(Rational& lhs, Rational& rhs){
		Integer denom = lcm(lhs.denominator, rhs.denominator);
		//Scale LHS:
		Integer scalar = denom / lhs.denominator;
		lhs.scaleBy(scalar);
		//Scale RHS:
		scalar = denom / rhs.denominator;
		rhs.scaleBy(scalar);
	};

	Rational operator+(const Rational& lhs, const Rational& rhs) {

		if(lhs == rNull){ //If lhs is 0
			return rhs;
		}
		if(rhs == rNull){ //If rhs is 0
			return lhs;
		}

		Rational result;
		//If both LHS and RHS are positive:
		if(lhs.positive && rhs.positive){
			Integer ones = lhs.ones + rhs.ones;

			Rational lhsScaled = lhs;
			Rational rhsScaled = rhs;
			scaleToCommonDenominator(lhsScaled, rhsScaled);
			
			Integer numerator = lhsScaled.numerator + rhsScaled.numerator;
			Integer denominator = lhsScaled.denominator; // = rhsScaled.denominator

			result.numerator = numerator;
			result.denominator = denominator;
			result.ones = ones;
			result.scaleDown();
			result.extractOnes();
		}
		else if(!lhs.positive && !rhs.positive){ //Adding two negatives
			// (-j) + (-i) = -(j + i)
			result = (-lhs) + (-rhs); 	// result = j + i
			result.positive = false;	// result = -(j + i)
		}
		else if(lhs.positive && !rhs.positive){
			result = lhs - (-rhs);				// j + (-i) = j - i
		}
		else if(!lhs.positive && rhs.positive){
			result = rhs - (-lhs);				// (-j) + i = i - j
		}

		return result;
	}

	Rational operator-(const Rational& lhs, const Rational& rhs) {

		if(lhs == rNull){ //If lhs is 0
std::cout << std::endl << "lhs was 0" << std::endl;
			return -rhs;
		}
		if(rhs == rNull){ //If rhs is 0
std::cout << std::endl << "rhs was 0" << std::endl;
			return lhs;
		}

		Rational result;
		
		if(lhs.positive && rhs.positive){
			if(lhs == rhs){
				result = rNull;
			}
			else if (lhs < rhs){
				result = -(rhs - lhs);
			}
			else{
				Rational modifiableLHS = lhs;
				Rational modifiableRHS = rhs;

				modifiableLHS.fractionizeOnes();
				modifiableRHS.fractionizeOnes();
				scaleToCommonDenominator(modifiableLHS, modifiableRHS);

				result.numerator = modifiableLHS.numerator - modifiableRHS.numerator;
				result.denominator = modifiableLHS.denominator; // = modifiableRHS.denominator
				result.scaleDown();
				result.extractOnes();
			}
		}
		else if(!lhs.positive && !rhs.positive){ 
			result = (-rhs) - (-lhs);		// (-j) - (-i) = i - j
		}
		else if(lhs.positive && !rhs.positive){
			result = lhs + (-rhs);			// j - (-i) = j + i
		}
		else if(!lhs.positive && rhs.positive){
			result = -((-lhs) + rhs);			// (-j) - i = -(j + i)
		}
		return result;
	}

	Rational operator*(const Rational& lhs, const Rational& rhs) {

		if(lhs == rNull || rhs == rNull){ //If lhs or rhs is 0
			return rNull;
		}
		Rational modifiableLHS = lhs;
		Rational modifiableRHS = rhs;

		modifiableLHS.fractionizeOnes();
		modifiableRHS.fractionizeOnes();
		
		Rational result;
		//Result is negative if LHS and RHS have different signs (+/.)
		if(lhs.positive != rhs.positive){ 
			result.positive = false;	
		}
		result.numerator = modifiableLHS.numerator * modifiableRHS.numerator;
		result.denominator = modifiableLHS.denominator * modifiableRHS.denominator;
		result.scaleDown();
		result.extractOnes();
		return result;
	}

	Rational operator/(const Rational& lhs, const Rational& rhs) {
		Rational modifiableRHS = rhs;
		modifiableRHS.flip();
		return lhs * modifiableRHS;
	}

	std::ostream& operator<<(std::ostream& os, const Rational& r) {
		std::stringstream ss;
		if(!r.positive){
			ss << '-';	//Add sign if r is negative
		}
		if(r.ones != null){ //Unless ones is 0, add ones to string
			int onesSize = r.ones.nDigits();
			for(int i = 0; i < onesSize; i++){
				int index = onesSize - i - 1;	//Read vector backwards (read number from the left)
				ss << r.ones.prop.digits[index];	//print digit
			}
			if(r.numerator != null){
				ss << '.';	//Add dot if a fraction follows
			}
		}
		if(r.numerator != null){ //Unless numerator is 0, add fraction to string
			int numSize = r.numerator.nDigits();
			for(int i = 0; i < numSize; i++){
				int index = numSize - i - 1;		//Read vector backwards (read number from the left)
				ss << r.numerator.prop.digits[index];	//print digit
			}
			ss << '/';
			int denomSize = r.denominator.nDigits();
			for(int i = 0; i < denomSize; i++){
				int index = denomSize - i - 1;	//Read vector backwards (read number from the left)
				ss << r.denominator.prop.digits[index];	//print digit
			}
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
		Rational modifiableLHS = lhs;
		Rational modifiableRHS = rhs;

		modifiableLHS.fractionizeOnes();
		modifiableRHS.fractionizeOnes();
		scaleToCommonDenominator(modifiableLHS, modifiableRHS);

		return modifiableLHS.numerator < modifiableRHS.numerator;
	}

	bool operator> (const Rational& lhs, const Rational& rhs) {
		return !(lhs < rhs || lhs == rhs);
	}

	bool operator<=(const Rational& lhs, const Rational& rhs) {
		return (lhs < rhs || lhs == rhs);
	}

	bool operator>=(const Rational& lhs, const Rational& rhs) {
		return !(lhs < rhs) || (lhs == rhs);
	}

	bool operator==(const Rational& lhs, const Rational& rhs) {
		Rational modifiableLHS = lhs;
		Rational modifiableRHS = rhs;
		modifiableLHS.fractionizeOnes();
		modifiableRHS.fractionizeOnes();
		scaleToCommonDenominator(modifiableLHS, modifiableRHS);

		return modifiableLHS.numerator == modifiableRHS.numerator;
	}

	bool operator!=(const Rational& lhs, const Rational& rhs) {
		return !(lhs == rhs);
	}

}
