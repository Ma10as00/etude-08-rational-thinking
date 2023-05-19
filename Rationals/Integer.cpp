#include "Integer.h"

namespace cosc326 {

	Integer::Integer() {
		value = 0;
		positive = true;
	}

	Integer::Integer(const Integer& i) {
		this->value = i.value;
		this->positive = i.positive;		
	}

	Integer::Integer(const std::string& s) {
		std::string numStr = "";
		char first = s.at(0);
		switch (first){
		case '+': 
			positive = true;
			numStr = s.substr(1);
			break;
		case '-':
			positive = false;
			numStr = s.substr(1);
			break;
		default:
			positive = true;
			numStr = s;
			break;
		}

		value = std::stoi(numStr);
	}


	Integer::~Integer() {
	
	}

	Integer& Integer::operator=(const Integer& i) {
		return *this;
	}

	Integer Integer::operator-() const {
		return Integer(*this);
	}

	Integer Integer::operator+() const {
		return Integer(*this);
	}

	Integer& Integer::operator+=(const Integer& i) {
		return *this;
	}

	Integer& Integer::operator-=(const Integer& i) {
		return *this;
	}

	Integer& Integer::operator*=(const Integer& i) {
		return *this;
	}

	Integer& Integer::operator/=(const Integer& i) {
		return *this;
	}

	Integer& Integer::operator%=(const Integer& i) {
		return *this;
	}

	Integer operator+(const Integer& lhs, const Integer& rhs) {
		return lhs;
	}

	Integer operator-(const Integer& lhs, const Integer& rhs) {
		return lhs;
	}

	Integer operator*(const Integer& lhs, const Integer& rhs) {
		return lhs;
	}

	Integer operator/(const Integer& lhs, const Integer& rhs) {
		return lhs;
	}

	Integer operator%(const Integer& lhs, const Integer& rhs) {
		return lhs;
	}


	std::ostream& operator<<(std::ostream& os, const Integer& i) {
		return os;
	}

	std::istream& operator>>(std::istream& is, Integer& i) {
		return is;
	}

	bool operator<(const Integer& lhs, const Integer& rhs) {
		return true;
	}

	bool operator> (const Integer& lhs, const Integer& rhs) {
		return true;
	}

	bool operator<=(const Integer& lhs, const Integer& rhs) {
		return true;
	}

	bool operator>=(const Integer& lhs, const Integer& rhs) {
		return true;
	}

	bool operator==(const Integer& lhs, const Integer& rhs) {
		return true;
	}

	bool operator!=(const Integer& lhs, const Integer& rhs) {
		return true;
	}


	Integer gcd(const Integer& a, const Integer& b) {
		return a;
	}

}
