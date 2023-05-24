#include "Integer.h"

namespace cosc326 {

	Integer::Integer() {						//integer i;
		prop = BIGINT_ZERO;
	}

	Integer::Integer(const Integer& i) {		//integer j(i);
		this->prop = i.prop;
	}

	Integer::Integer(const std::string& s) {	//integer k("123");

		std::string numStr = "";
		char first = s.at(0);
		switch (first){
		case '+': 
			prop.positive = true;
			numStr = s.substr(1);
			break;
		case '-':
			prop.positive = false;
			numStr = s.substr(1);
			break;
		default:
			prop.positive = true;
			numStr = s;
			break;
		}

		const char* values = numStr.c_str(); //Convert the string into an array of chars
		prop.nDigits = strlen(values);

		if(prop.nDigits == 0){
			//For an empty array, construct Integer 0:
			Integer();
		}else{
			prop.digits.resize(prop.nDigits);
			//Loop through array and add each digit in prop.digits
			for(int i = 0; i < prop.nDigits; i++){
				char c = values[i];
				int digit = c - '0'; //numerical value of the char
				if (digit >= 0 && digit <= 9){
					//Store the digits backwards for arithmetical purposes:
					prop.digits[(prop.nDigits-1) - i] = digit; 
				}else{
					//TODO - Handle invalid input
				}
			}
		}
	}


	Integer::~Integer() {
	
	}

	Integer& Integer::operator=(const Integer& i) {			// j = i;
		this->prop = i.prop;
		return *this;
	}

	Integer Integer::operator-() const { 					// -j;
		Integer n = *this; 						// r = j
		n.prop.positive = !this->prop.positive; // r = -r
		return n;								// return r
	}

	Integer Integer::operator+() const {					// +j;
	return *this;							// return j
	}

	Integer& Integer::operator+=(const Integer& i) {		// j += i;
		return *this;
	}

	Integer& Integer::operator-=(const Integer& i) {		// j -= i;
		return *this;
	}

	Integer& Integer::operator*=(const Integer& i) {		// j *= i;
		return *this;
	}

	Integer& Integer::operator/=(const Integer& i) {		// j /= i;
		return *this;
	}

	Integer& Integer::operator%=(const Integer& i) {		// j %= i;
		return *this;
	}

	Integer operator+(const Integer& lhs, const Integer& rhs) {	// lhs + rhs;
		//Using lhs as starting point:
		Integer result;
		//Were are going to add rhs onto result, so we need the nDigits of rhs:
		const int rDigits = rhs.prop.nDigits;
		const int lDigits = lhs.prop.nDigits;

		//result can have at maximum one digit more than the biggest of lhs and rhs:
		const int resDigits = (lDigits > rDigits)? (lDigits + 1) : (rDigits + 1);
		result.prop.digits.resize(resDigits);

		int passingTen = 0; //Used for moving value to next index

		if(lhs.prop.positive && rhs.prop.positive){
			//Adding rhs onto lhs
			for(int i = 0; i < rDigits; i++){ //TODO try to make i an Integer instead of int
				//Starter på enerplassen: TODO oversett

				int res;
				try{
					res = lhs.prop.digits[i];
				}
				catch(const std::exception& e){ //If lhs has <=i digits
					res = 0;
				}
				
				int r = rhs.prop.digits[i];
				
				res += r;
				res += passingTen;	//Add collected 10s from last index
				passingTen = 0;			//Reset collected 10s

				//If res is to big, pass 10 to next index:
				if(res > 9){
					res -= 10;
					passingTen++;
				}

				result.prop.digits[i] = res;
			}
		}
		return result;
	}

	Integer operator-(const Integer& lhs, const Integer& rhs) { // lhs - rhs;
		return lhs;
	}

	Integer operator*(const Integer& lhs, const Integer& rhs) { // lhs * rhs;
		return lhs;
	}

	Integer operator/(const Integer& lhs, const Integer& rhs) { // lhs / rhs;
		return lhs;
	}

	Integer operator%(const Integer& lhs, const Integer& rhs) { // lhs % rhs;
		return lhs;
	}


	std::ostream& operator<<(std::ostream& os, const Integer& i) { // std::cout << i << std::endl;
		return os;
	}

	std::istream& operator>>(std::istream& is, Integer& i) { 	// std::cin >> i;
		return is;
	}

	bool operator<(const Integer& lhs, const Integer& rhs) {	// lhs < rhs
		return true;
	}

	bool operator> (const Integer& lhs, const Integer& rhs) {	// lhs > rhs
		return true;
	}

	bool operator<=(const Integer& lhs, const Integer& rhs) {	// lhs <= rhs
		return true;
	}

	bool operator>=(const Integer& lhs, const Integer& rhs) {	// lhs >= rhs
		return true;
	}

	bool operator==(const Integer& lhs, const Integer& rhs) {	// lhs == rhs
		return true;
	}

	bool operator!=(const Integer& lhs, const Integer& rhs) {	// lhs != rhs
		return true;
	}


	Integer gcd(const Integer& a, const Integer& b) {			// i = gcd(a, b);		Greatest common divisor
		return a;
	}

}
