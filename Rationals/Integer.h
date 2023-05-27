
// Most compilers understand the once pragma, but just in case...
#ifndef INTEGER_H_INCLUDED
#define INTEGER_H_INCLUDED

#include <iostream>
#include <string>
#include <vector>

namespace cosc326 {

	class Integer {

	public:

		//Defining the type BigInt
		typedef struct{
			unsigned int nDigits;		//Number of digits - the size of the array (digits)
			bool positive;				//true for positive numbers, false for negative
			std::vector<int> digits;	//An array containing all the digits, in reverse order
		} BigInt;

		BigInt prop;
		/** The BigInt representation of 0. */
		const BigInt BIGINT_ZERO = {1,true,{0}};

		Integer();                             // Integer i;
		Integer(const Integer& i);             // Integer j(i);
		Integer(const std::string& s);         // Integer k("123");

		~Integer();

		Integer& operator=(const Integer& i);  // j = i;

		// Unary operators
		Integer operator-() const;                   // -j;
		Integer operator+() const;                   // +j;

		// Arithmetic assignment operators
		Integer& operator+=(const Integer& i); // j += i;
		Integer& operator-=(const Integer& i); // j -= i;
		Integer& operator*=(const Integer& i); // j *= i;
		Integer& operator/=(const Integer& i); // j /= i;
		Integer& operator%=(const Integer& i); // j %= i;

		std::string toString();
		
		Integer traditionalMult(const Integer& lhs, const Integer& rhs);
		
		// lhs < rhs -- a 'friend' means operator isn't a member, but can access the private parts of the class.
		// You may need to make some other functions friends, but do so sparingly.
		friend bool operator<(const Integer& lhs, const Integer& rhs);

	private:
		// Can add internal storage or methods here
	};

	// Binary operators
	Integer operator+(const Integer& lhs, const Integer& rhs); // lhs + rhs;
	Integer operator-(const Integer& lhs, const Integer& rhs); // lhs - rhs;
	Integer operator*(const Integer& lhs, const Integer& rhs); // lhs * rhs;
	Integer operator/(const Integer& lhs, const Integer& rhs); // lhs / rhs;
	Integer operator%(const Integer& lhs, const Integer& rhs); // lhs % rhs;

	std::ostream& operator<<(std::ostream& os, const Integer& i);  // std::cout << i << std::endl;
	std::istream& operator>>(std::istream& is, Integer& i);        // std::cin >> i;

	bool operator> (const Integer& lhs, const Integer& rhs); // lhs > rhs
	bool operator<=(const Integer& lhs, const Integer& rhs); // lhs <= rhs
	bool operator>=(const Integer& lhs, const Integer& rhs); // lhs >= rhs
	bool operator==(const Integer& lhs, const Integer& rhs); // lhs == rhs
	bool operator!=(const Integer& lhs, const Integer& rhs); // lhs != rhs

	Integer gcd(const Integer& a, const Integer& b);  // i = gcd(a, b);
}

#endif
