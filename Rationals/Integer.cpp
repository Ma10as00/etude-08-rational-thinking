#include "Integer.h"
#include <sstream>
#include <vector>

namespace cosc326 {

	Integer::Integer() {						//integer i;
		prop = BIGINT_ZERO;
	}

	const Integer null;

	Integer::Integer(const Integer& i) {		//integer j(i);
		this->prop = i.prop;
	}

	Integer::Integer(const std::string& s) {	//integer k("123");

		std::string numStr = "";
		char first = s.at(0);
		switch (first){		//Remove signs (+/-) from string
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
		int length = strlen(values); //length of string
		int digCount = 0; //For finding number of digits, which should be (length - leadingZeroes)

		if(length != 0){ //If string was empty, skip iterating through it
			prop.digits.resize(length);
			bool firstDigitIsFound = false;	//True when first nonzero digit is found

			//Loop through array and add each digit in prop.digits
			for(int i = 0; i < length; i++){
				char c = values[i];
				int digit = c - '0'; //numerical value of the char
				if (digit >= 0 && digit <= 9){
					if(firstDigitIsFound){
						//Store the digits backwards for arithmetical purposes:
						prop.digits[(length-1) - i] = digit;
					}else if(digit != 0){ //When we find the first nonzero digit
						firstDigitIsFound = true;
						digCount = length - i; //subtract the number of leading zeroes
						prop.digits[(length-1) - i] = digit;
					}
				}else{
					//TODO - Handle invalid input
				}
			}
			prop.nDigits = digCount; //Set number of digits
		}

		if(digCount == 0){
			prop = BIGINT_ZERO; //Return 0 if string was empty or all zeroes
		}
	}

	Integer::~Integer() {
	
	}

	Integer Integer::MaxInteger() const{
		Integer max;
		max.prop = MAX_INT;
		return max;
	}

	std::string Integer::toString() const{
		bool sign = (*this).prop.positive;
		int nDig = (*this).prop.nDigits;
		const std::vector<int> digs = (*this).prop.digits;
		std::stringstream ss;

		if(!sign){
			ss << '-';
		}
		
		for(int i = 0; i < nDig; i++){
			int index = nDig - 1 - i; // Vector of digits must be read backwards
			ss << digs.at(index);
		}

		return ss.str();
	}

	int Integer::toInt() const{
		bool sign = (*this).prop.positive;
		int nDig = (*this).prop.nDigits;
		const std::vector<int> digs = (*this).prop.digits;
		int result = 0;
		for(int i = 0; i < nDig; i++){
			result += digs[i] * 10^i;
		}
		return result;
	}

	Integer& Integer::operator=(const Integer& i) {			// j = i;
		this->prop = i.prop;
		return *this;
	}

	Integer Integer::operator-() const { 					// -j;
		Integer null;
		Integer i = *this; 						// r = j
		if(i == null){
			return i;	//0 should always be positive
		}
		i.prop.positive = !this->prop.positive; // r = -r
		return i;								// return r
	}

	Integer Integer::operator+() const {					// +j;
		return *this;							// return j
	}

	Integer& Integer::operator+=(const Integer& i) {		// j += i;
		*this = *this + i;
		return *this;
	}

	Integer& Integer::operator-=(const Integer& i) {		// j -= i;
		*this = *this - i;
		return *this;
	}

	Integer& Integer::operator*=(const Integer& i) {		// j *= i;
		*this = *this * i;
		return *this;
	}

	Integer& Integer::operator/=(const Integer& i) {		// j /= i;
		*this = *this / i;
		return *this;
	}

	Integer& Integer::operator%=(const Integer& i) {		// j %= i;
		*this = *this % i;
		return *this;
	}

	Integer operator+(const Integer& lhs, const Integer& rhs) {	// lhs + rhs;

		Integer null;
		if(lhs == null){ //If lhs is 0
			return rhs;
		}
		if(rhs == null){ //If rhs is 0
			return lhs;
		}

		Integer result; //Sum to return in the end

		if(lhs.prop.positive && rhs.prop.positive){ //If both numbers are positive
			//Find the number of digits in lhs and rhs:
			const int lDigits = lhs.prop.nDigits;
			const int rDigits = rhs.prop.nDigits;

			//Result can have at maximum one digit more than the biggest of lhs and rhs:
			const int maxDigits = (lDigits > rDigits)? (lDigits + 1) : (rDigits + 1);
			result.prop.digits.resize(maxDigits); //Making enough space for the resulting digits

			int passingTen = 0; //Used for moving value to next index
			int digCount = 0;	//Counting how many digits the resulting number has

			//Adding rhs onto lhs
			for(int i = 0; i < maxDigits; i++){ //TODO try to make i an Integer instead of int
				//Starter på enerplassen: TODO oversett

				int l; //digit from lhs
				if(i < lDigits){
					l = lhs.prop.digits[i];
				}else{
					l = 0;					//0 if we ran out of digits in lhs
				}

				int r; //digit from lhs
				if(i < rDigits){
					r = rhs.prop.digits[i];	
				}else{
					r = 0;					//0 if we ran out of digits in rhs
				}
				
				int res = l + r;	//Add digits
				res += passingTen;	//Add collected 10s from last index
				passingTen = 0;		//Reset collected 10s

				//If res is to big, pass 10 to next index:
				if(res > 9){
					res -= 10;
					passingTen++;
				}

				// Update digitCount unless digit is (leading) zero.
				// If this digit is a non-leading zero, digCount will be updated by the next digit.
				if(res != 0){	 
					digCount = i+1;	
				}

				result.prop.digits[i] = res; //Store resulting digit
			}

			result.prop.digits.resize(digCount); //Remove redundant space from the vector
			result.prop.nDigits = digCount;
		}else if(!lhs.prop.positive && !rhs.prop.positive){ //Adding two negatives
			// (-j) + (-i) = -(j + i)
			result = (-lhs) + (-rhs); 			// result = j + i
			result.prop.positive = false;		// result = -(j + i)
		}else if(lhs.prop.positive && !rhs.prop.positive){
			result = lhs - (-rhs);				// j + (-i) = j - i
		}else if(!lhs.prop.positive && rhs.prop.positive){
			result = rhs - (-lhs);				// (-j) + i = i - j
		}

		return result;
	}

	Integer operator-(const Integer& lhs, const Integer& rhs) { // lhs - rhs;

		Integer null;
		if(lhs == null){ //If lhs is 0
			return -rhs;
		}
		if(rhs == null){ //If rhs is 0
			return lhs;
		}

		Integer result; //return value

		if(lhs.prop.positive && rhs.prop.positive){ //If both numbers are positive
			if(lhs == rhs){
				return result;	//return 0 (which is the default value of result)
			}else if(lhs > rhs){
				//Find the number of digits in lhs and rhs:
				const int lDigits = lhs.prop.nDigits;
				const int rDigits = rhs.prop.nDigits;

				//Result can have at maximum as many digits as lhs:
				result.prop.digits.resize(lDigits); //Making enough space for the resulting digits

				int borrowedTen = 0; //Used for borrowing value from next index
				int digCount = 0;	 //Counting how many digits the resulting number has

				//Subtracting rhs from lhs
				for(int i = 0; i < lDigits; i++){ //TODO try to make i an Integer instead of int
					//Starter på enerplassen: TODO oversett

					int res = lhs.prop.digits[i];	//use lhs as starting point
					int r;		//digit to subtract

					if (i < rDigits){
						r = rhs.prop.digits[i];
					}else{
						r = 0;	//subtract 0 if rhs have <(i+1) digits
					}					
					
					res -= r;			//Subtract rhs from lhs
					res -= borrowedTen;	//Subtract 10s that was borrowed to previous index
					borrowedTen = 0;	//Reset borrowed 10s

					//If res is negative, borrow 10 from next index:
					if(res < 0){
						res += 10;
						borrowedTen++;
					}

					// Update digitCount unless digit is (leading) zero.
					// If this digit is a non-leading zero, digCount will be updated by the next digit.
					if(res != 0){	 
						digCount = i+1;	
					}

					result.prop.digits[i] = res; //Store resulting digit
				}

				result.prop.digits.resize(digCount); //Remove redundant space from the vector
				result.prop.nDigits = digCount;
			}else{ //If (lhs < rhs)
				result = -(rhs - lhs);		// j - i = -(i - j)
			}
		}else if(!lhs.prop.positive && !rhs.prop.positive){ 
			result = (-rhs) - (-lhs);		// (-j) - (-i) = i - j
		}else if(lhs.prop.positive && !rhs.prop.positive){
			result = lhs + (-rhs);			// j - (-i) = j + i
		}else if(!lhs.prop.positive && rhs.prop.positive){
			result = -((-lhs) + rhs);			// (-j) - i = -(j + i)
		}

		return result;
	}

	/** 
	 * Traditional way of doing multiplication. This method is assuming that lhs has only 1 digit.
	 */
	Integer Integer::traditionalMult(const Integer& lhs, const Integer& rhs) {

		Integer null;
		if(lhs == null || rhs == null){ //If lhs or rhs is 0
			return null;
		}

		int rDig = rhs.prop.nDigits;	//number of digits in rhs
		int l = lhs.prop.digits[0];		//The only digit in lhs

		Integer result;
		result.prop.digits.resize(rDig + 1); //Result can have at most (rDig + 1) digits
		int passingTens = 0;	//Used for passing excess value
		int digCount = rDig;	//Result has at least as many digits as rhs
	
		for(int i=0; i<rDig; i++){
			int r = rhs.prop.digits[i];
			int res = l * r; 		//multiply with lhs
			res += passingTens;		//add excess value from last index
			passingTens = res / 10;	//update passingTens
			result.prop.digits[i] = res % 10;
			if (i == rDig - 1){	//If this is the last digit in rhs, put excess value in next index
				if (passingTens > 0){
					result.prop.digits[i+1] = passingTens;
					digCount++; //Result has one more digit than rhs
				}
			}
		}
		result.prop.nDigits = digCount;
		if(lhs.prop.positive != rhs.prop.positive){
			result.prop.positive = false;	//Result is negative if the factors have different signs (+/-)
		}
		return result;
	}

	Integer operator*(const Integer& lhs, const Integer& rhs) { // lhs * rhs;

		Integer null;
		if(lhs == null || rhs == null){ //If lhs or rhs is 0
			return null;
		}
		
		int lDig = lhs.prop.nDigits;
		int rDig = rhs.prop.nDigits;
		
		//Karatsuba's algorithm:
		//----------------------

		//Base case: if a factor has only one digit
		if(lDig == 1){
			return traditionalMult(lhs,rhs);
		}
		if (rDig == 1){
			return traditionalMult(rhs,lhs);
		}

		// n = number of digits in the biggest factor
		// m = number of digits in b and d
		int n = max(lDig,rDig);
		int smallest = min(lDig,rDig);
		int m = min((n / 2), (smallest - 1)); //This ensures that a and c have at least one digit
		int maxDigits = lDig + rDig; //Result can have maximum (lDig + rDig) digits

		//We are constructing a, b, c, d from strings, so that any leading zeroes will be removed
		std::string lStr = lhs.toString();
		std::string aStr = lStr.substr(0, lStr.length() - m);
		Integer a = Integer(aStr); //First half of lhs

		std::string bStr = lStr.substr(lStr.length() - m);
		Integer b = Integer(bStr); //Second half of lhs
		
		std::string rStr = rhs.toString();
		std::string cStr = rStr.substr(0,rStr.length() - m);
		Integer c = Integer(cStr); //First half of rhs

		std::string dStr = rStr.substr(rStr.length() - m);
		Integer d = Integer(dStr); //Second half of rhs

		//Recursive calls:
		Integer ac = a*c;
		Integer bd = b*d;
		Integer ad_plus_bc = (((a+b) * (c+d)) - ac) - bd;
		
		Integer result;
		result.prop.digits.resize(maxDigits);	//Make enough space for result's digits
		int passingTens = 0;
		int leadingZeroes = 0;

		//Build resulting Integer:
		for(int i = 0; i < maxDigits; i++){
			int res = 0;
			if(passingTens > 0){
				res += passingTens;		//Value passed from previous index
				passingTens = 0;		//Reset passingTens
			}
			if (i < bd.prop.nDigits) {
				res += bd.prop.digits[i];
			}
			if (i >= m && (i - m) < ad_plus_bc.prop.nDigits) {
				res += ad_plus_bc.prop.digits[i - m];
			}
			if (i >= 2 * m && (i - (2 * m)) < ac.prop.nDigits) {
				res += ac.prop.digits[i - 2 * m];
			}
			passingTens = res / 10;  		// Count how many 10s should be passed to next index
			res %= 10;						// Remove passed 10s from this digit
			result.prop.digits[i] = res;  	// Store the digit in the result
			if(res == 0){
				leadingZeroes++;	//Count leading zero
			}else{
				leadingZeroes = 0;	//Reset count of leadingZeroes if this digit is not 0
			}
		}
		result.prop.nDigits = maxDigits - leadingZeroes;
		//Result is negative if the factors have different signs (+/-):
		if(lhs.prop.positive != rhs.prop.positive){
			result.prop.positive = false;	
		}		
		return result;
	}

		/** This method is quite fast for division when the divisor is big, but slow when rhs is a lot smaller than rhs.*/
	Integer slowDivision(const Integer& lhs, const Integer& rhs) { // lhs / rhs;
		const Integer null;
		if(lhs < rhs){
			return null;	//return 0 if (lhs < rhs)
		}
		if(rhs == null){	//No division by 0
			throw std::runtime_error("Division by zero is not permitted.");
		}
		const Integer one = Integer("1");
		Integer result = one;	//Since lhs >= rhs, result is at least 1.
		result.prop.digits.resize(lhs.prop.nDigits); //result can have maximum as many digits as lhs
		Integer n = rhs;
		Integer lastN;	
		Integer lastRes;
		//Square n until it gets too big
		while(n <= lhs){
			lastRes = result;
			lastN = n;
			result *= n;
			n *= n;
		}
		//Go back to the values we had before n went bigger than lhs:
		n = lastN;
		result = lastRes;
		//Multiply n with rhs until it gets too big
		while(n <= lhs){	//Runs loglhs(rhs) times, where loglhs is log with base lhs
			lastN = n;
			lastRes = result;
			n *= rhs;
			result *= rhs;
		}
		//Go back to the values we had before n went bigger than lhs:
		n = lastN;
		result = lastRes;
		while(n <= lhs){
			lastRes = result;
			n += rhs; 
			result += one;
		}
		//Go back to the values we had before n went bigger than lhs:
		result = lastRes;
		return result;
	}

	Integer operator/(const Integer& lhs, const Integer& rhs) { // lhs / rhs;
		if(lhs < rhs){
			return null;	//return 0 if (lhs < rhs)
		}
		if(rhs == null){	//No division by 0
			throw std::runtime_error("Division by zero is not permitted.");
		}

		Integer result;
		Integer max = Integer();
		int maxDigits = lhs.prop.nDigits;
		result.prop.digits.resize(maxDigits);	//Make enough space to fill in resulting digits
		Integer passingTens;

		for(int i = 0; i < maxDigits; i++){
			int index = maxDigits - 1 - i;	//iterate thorugh lhs's vector backwards (read number from the left)
			int digit = lhs.prop.digits[index];
			Integer tempDividend = Integer(std::to_string(digit));
			tempDividend += passingTens * Integer("10");
			passingTens = null;
			Integer res = slowDivision(tempDividend,rhs);
			Integer subtrahend = res*rhs;
			passingTens = tempDividend - subtrahend;
			result.prop.digits[i] = res;
		}
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

		//Check first if numbers are positive or not
		bool lPos = lhs.prop.positive;
		bool rPos = rhs.prop.positive;

		if(lPos && !rPos){
			return false;
		}
		else if(!lPos && rPos){
			return true;
		}
		
		//If both are positive, check how many digits they have
		else if(lPos && rPos){
			int lDig = lhs.prop.nDigits;
			int rDig = rhs.prop.nDigits;

			if(lDig > rDig){
				return false;
			}
			if(lDig < rDig){
				return true;
			}
			//If they have equally many digits, check every digit, starting from the highest valued index.
			else{
				for(int i = lDig - 1; i > -1; i--){ //Read number from the left, i.e., read vector backwards
					int l = lhs.prop.digits.at(i);
					int r = rhs.prop.digits.at(i);
					if(l != r){
						return l < r;
					}
				}
			}
		}
		//If both are negative, make them positive, and negate the answer
		else if(!lPos && !rPos){
			return !(-lhs < -rhs);
		}
		//This line will only be reached if lhs = rhs:
		return false;
	}

	bool operator> (const Integer& lhs, const Integer& rhs) {	// lhs > rhs
		return !(lhs <= rhs);
	}

	bool operator<=(const Integer& lhs, const Integer& rhs) {	// lhs <= rhs
		if(lhs == rhs){
			return true;
		}else{
			return lhs < rhs;
		}
	}

	bool operator>=(const Integer& lhs, const Integer& rhs) {	// lhs >= rhs
		return !(lhs < rhs);
	}

	bool operator==(const Integer& lhs, const Integer& rhs) {	// lhs == rhs
		return lhs.prop.digits == rhs.prop.digits &&
			lhs.prop.nDigits == rhs.prop.nDigits &&
			lhs.prop.positive == rhs.prop.positive;
	}

	bool operator!=(const Integer& lhs, const Integer& rhs) {	// lhs != rhs
		return !(lhs == rhs);
	}


	Integer gcd(const Integer& a, const Integer& b) {			// i = gcd(a, b);		Greatest common divisor
		return a;
	}

}
