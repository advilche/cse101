#include "BigInteger.h"
#include "List.h"

int power = 9;
long base = 1000000000;

BigInteger::BigInteger() {
    	signum = 0;
    	digits = List();
}

BigInteger::BigInteger(std::string str) {
    	if (str.length() == 0) throw std::invalid_argument("BigInteger: Constructor: empty string");
    	signum = (str[0] == '-') ? -1 : 1;
    	if (str[0] == '+' || str[0] == '-') str = str.substr(1);
    	for (char ch : str) {
		if (!isdigit(ch)) throw std::invalid_argument("BigInteger: Constructor: non-numeric string");
    	}
    	int offset = str.length() % power;
    	if (offset) digits.insertBefore(stol(str.substr(0, offset)));
    	for (offset = str.length() % power; offset < (int)str.length(); offset += power) {
		digits.insertBefore(stol(str.substr(offset, power)));
    	}
}

BigInteger::BigInteger(const BigInteger& obj) {
    	this->signum = obj.signum;
    	this->digits = obj.digits;
}

int BigInteger::sign() const {
    	return this->signum;
}

int BigInteger::compare(const BigInteger& obj) const {
	if (this->signum != obj.signum) return this->signum > obj.signum ? 1 : -1;
    	if (this->signum == 0) return 0;

	List tmpA = this->digits;
    	List tmpB = obj.digits;

	int cmp = 0;

	if (tmpA.length() != tmpB.length()) {
		cmp = tmpA.length() > tmpB.length() ? 1 : -1;
    	} else {
		tmpA.moveFront();
		tmpB.moveFront();

		while (tmpA.position() < tmpA.length() && cmp == 0) {
	    		cmp = tmpA.peekNext() > tmpB.peekNext() ? 1 : (tmpA.peekNext() < tmpB.peekNext() ? -1 : 0);
	    		tmpA.moveNext();
	    		tmpB.moveNext();
		}
    	}
    	return this->signum == 1 ? cmp : -cmp;
}

void negateList(List& lst) {
    	for (lst.moveFront(); lst.position() < lst.length(); lst.moveNext()) {
		lst.setAfter(lst.peekNext() * -1);
    	}
}

void sumList(List& lst, List A, List B, int sgn) {
    	lst.clear();
    
	for (B.moveFront(); B.position() < B.length(); B.moveNext()) {
		B.setAfter(sgn * B.peekNext());
    	}

    	A.moveBack();
	B.moveBack();

	while (A.position() > 0 || B.position() > 0) {
		lst.insertAfter((A.position() > 0 ? A.peekPrev() : 0) + (B.position() > 0 ? B.peekPrev() : 0));
		if (A.position() > 0) A.movePrev();
		if (B.position() > 0) B.movePrev();
    	}
    	lst.moveFront();
    	while (lst.front() == 0 && lst.length() > 1) {
		lst.eraseAfter();
    	}
}

int normalizeList(List& lst) {
    	if (lst.front() == 0) return 0;


	int res = 1;
    	if (lst.front() < 0) {
		res = -1;
		negateList(lst);
    	}

    	lst.moveBack();
    	int carry = 0;
	ListElement temp = 0;

	while (lst.position() > 0) {
		temp = lst.peekPrev() + carry;
		carry = 0;
		if (temp < 0) {
	    		carry = -1;
	    		temp += base;
		}
		lst.setBefore(temp % base);
		carry += temp / base;
		lst.movePrev();
    	}
    	if (carry > 0) {
		lst.moveFront();
		lst.insertAfter(carry);
    }

    	return res;
}

void shiftList(List& lst, int cnt) {
    	lst.moveBack();
    	for (int i = 0; i < cnt; i++) {
		lst.insertAfter(0);
    	}
}

void scalarMultList(List& lst, ListElement mult) {
    	for (lst.moveFront(); lst.position() < lst.length(); lst.moveNext()) {
		lst.setAfter(lst.peekNext() * mult);
    	}
}

void BigInteger::makeZero() {
    	signum = 0;
    	digits.clear();
}

void BigInteger::negate() {
    	signum *= -1;
}

BigInteger BigInteger::add(const BigInteger& obj) const {
    	BigInteger result;
    	BigInteger tempA = *this;
    	BigInteger tempB = obj;
    	int signFactor = 1;
    	if (this->signum == -1) negateList(tempA.digits);
    	if (obj.signum == -1) signFactor = -1;
    	sumList(result.digits, tempA.digits, tempB.digits, signFactor);
    	result.signum = normalizeList(result.digits);
    	if (normalizeList(result.digits) == -1) negateList(result.digits);
    	return result;
}

BigInteger BigInteger::sub(const BigInteger& obj) const {
    	BigInteger tempObj = obj;
    	negateList(tempObj.digits);
    	BigInteger result = add(tempObj);
    	return result;
}

BigInteger BigInteger::mult(const BigInteger& obj) const {
    	BigInteger result;
    	if (this->signum == 0 || obj.signum == 0) return result;
    	List sum;
    	List tempObj = obj.digits;
    	List temp;
    	for (int shift = 0; tempObj.position() > 0; ++shift, tempObj.movePrev()) {
		temp = this->digits;
		scalarMultList(temp, tempObj.peekPrev());
		shiftList(temp, shift);
		List tempSum = sum;
		sumList(sum, tempSum, temp, 1);
		normalizeList(sum);
    	}
    	result.digits = sum;
    	result.signum = (this->signum == obj.signum) ? 1 : -1;
    	return result;
}

std::string BigInteger::to_string() {
    	if (this->signum == 0) return "0";
    	std::string str = (this->signum == -1) ? "-" : "";
    	digits.moveFront();
    	for (; digits.front() == 0 && digits.length() > 1; digits.eraseAfter()) {}
    	for (digits.moveFront(); digits.position() < digits.length(); digits.moveNext()) {
		std::string val = std::to_string(digits.peekNext());
		std::string zeros = "";
		for (; (int)zeros.length() + (int)val.length() < power && digits.position() > 0; zeros += '0') {}
		str += zeros + val;
    	}
    	return str;
}

std::ostream& operator<<(std::ostream& stream, BigInteger obj) {
    	return stream << obj.to_string();
}

bool operator==(const BigInteger& A, const BigInteger& B) {    	
	return A.compare(B) == 0;
}

bool operator<(const BigInteger& A, const BigInteger& B) {
    	return A.compare(B) < 0;
}

bool operator<=(const BigInteger& A, const BigInteger& B) {
    	return A.compare(B) <= 0;
}

bool operator>(const BigInteger& A, const BigInteger& B) {
    	return A.compare(B) > 0;
}

bool operator>=(const BigInteger& A, const BigInteger& B) {
    	return A.compare(B) >= 0;
}

BigInteger operator+(const BigInteger& A, const BigInteger& B) {
    	return A.add(B);
}

BigInteger operator+=(BigInteger& A, const BigInteger& B) {
    	A = A.add(B);
    	return A;
}

BigInteger operator-(const BigInteger& A, const BigInteger& B) {
    	return A.sub(B);
}

BigInteger operator-=(BigInteger& A, const BigInteger& B) {
    	A = A.sub(B);
    	return A;
}

BigInteger operator*(const BigInteger& A, const BigInteger& B) {
    	return A.mult(B);
}

BigInteger operator*=(BigInteger& A, const BigInteger& B) {
    	A = A.mult(B);
    	return A;
}

