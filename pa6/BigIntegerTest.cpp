#include "BigInteger.h"
#include <iostream>
#include <cassert>

void testConstructors() {
    BigInteger B("+13378008135");
    assert(B.to_string() == "13378008135"); // Corrected value
    std::cout << "B to string okay\n";

    std::cout << "B sign before MakeZero: " << B.sign() << std::endl;
    std::cout << "B before MakeZero: " << B << std::endl;
    B.makeZero();
    std::cout << "B After MakeZero: " << B << std::endl;
    std::cout << "B sign after MakeZero: " << B.sign() << std::endl;

    BigInteger A = BigInteger();

    if (A == B) std::cout << "equal" << std::endl;

    std::cout << "Constructor tests passed.\n";
}

void testArithmetic() {
    BigInteger A("123456789");
    BigInteger B("987654321");
    BigInteger C = A + B;
    assert(C.to_string() == "1111111110");

    BigInteger D = B - A;
    assert(D.to_string() == "864197532");

    BigInteger E = A * B;
    assert(E.to_string() == "121932631112635269");

    BigInteger F = A - A;
    assert(F.to_string() == "0");

    std::cout << "Arithmetic tests passed.\n";
}

void testComparison() {
    BigInteger A("123456789");
    BigInteger B("987654321");
    BigInteger C("123456789");

    assert(A < B);
    assert(B > A);
    assert(A == C);
    assert(A <= C);
    assert(B >= A);

    std::cout << "Comparison tests passed.\n";
}

void testEdgeCases() {
    BigInteger A("0");
    BigInteger B("0");
    BigInteger C = A + B;
    assert(C.to_string() == "0");

    BigInteger D("1");
    BigInteger E("-1");
    BigInteger F = D + E;
    assert(F.to_string() == "0");

    std::cout << "Edge case tests passed.\n";
}

int main() {
     	testConstructors();
    	testArithmetic();
    	testComparison();
    	testEdgeCases();

    std::cout << "All BigInteger tests passed!\n";
    return 0;
}


