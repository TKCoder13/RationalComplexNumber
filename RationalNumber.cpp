#include "RationalNumber.h"

#include <string>
#include <cmath>
#include <typeinfo>
#include <cinttypes>
#include <iostream>

using namespace std;

uint64_t numerator;
uint64_t denominator;

/* CONSTRUCTORS */

// -- Default Constructor
RationalNumber::RationalNumber() {
    this->numerator = 0;
    this->denominator = 1;
}

// -- Overload Constructor
RationalNumber::RationalNumber(uint64_t num, uint64_t denom) {
    this->numerator = num;
    this->denominator = denom;
}

// -- Copy Constructor
RationalNumber::RationalNumber(const RationalNumber &src) {
    this->numerator = src.numerator;
    this->denominator = src.denominator;
}

// -- Deconstructor
RationalNumber::~RationalNumber() {}

/* METHODS */

const uint64_t RationalNumber::getNumerator() {
    return this->numerator;
}

const uint64_t RationalNumber::getDenominator() {
    return this->denominator;
}

void RationalNumber::setNumerator(uint64_t num) {
    this->numerator = num;
}

void RationalNumber::setDenominator(uint64_t num) {
    char exception[] = "Denominator cannot be 0";
    char* zeroException = exception;
    try {
        if (num != 0) {
            this->denominator = num;
            return;
        } else {
            throw zeroException;
        }
    } catch (std::exception& e) {
        cout << "exception caught: " << e.what() << endl;
    }
}



bool RationalNumber::equals(RationalNumber rhs) {
    if (typeid(*this) == typeid(rhs))
        if (this->numerator == rhs.numerator && this->denominator == rhs.denominator) 
            return true;
    return false;
}

string RationalNumber::toString() {
    uint64_t currentNumerator = this->getNumerator();
    uint64_t currentDenominator = this->getDenominator();

    // -- Checks for negative values
    bool isNegative = false;
    if (currentNumerator < 0) isNegative = !isNegative;
    if (currentDenominator < 0) isNegative = !isNegative;

    currentNumerator = (uint64_t) std::abs((double) currentNumerator);
    currentDenominator = (uint64_t) std::abs((double) currentDenominator);

    uint64_t wholeNumber = (uint64_t) std::abs((double) (currentNumerator / currentDenominator));
    uint64_t remainder = (uint64_t) std::abs((double) (currentNumerator % currentDenominator));

    // -- Reduce improper fractions
    uint64_t gcd = getGCD(remainder, currentDenominator);
    if (gcd > 1) {
        remainder = remainder / gcd;
        currentDenominator = currentDenominator / gcd;
    }

    if (isNegative) {
        if (wholeNumber == 0) {
            if (remainder == 0) {
                return "-" + to_string(wholeNumber);
            } else {
                return "-" + to_string(remainder) + "/" + to_string(currentDenominator);
            }
        } else {
            if (remainder == 0) {
                return "-" + to_string(wholeNumber);
            } else {
                return "-" + to_string(wholeNumber) + " " + to_string(remainder) + "/" + to_string(currentDenominator);
            }
        }
    } else {
        if (wholeNumber == 0) {
            if (remainder == 0) {
                return to_string(wholeNumber);
            } else {
                return to_string(remainder) + "/" + to_string(currentDenominator);
            }
        } else {
            if (remainder == 0) {
                return to_string(wholeNumber);
            } else {
                return to_string(wholeNumber) + " " + to_string(remainder) + "/" + to_string(currentDenominator);
            }
        }
    }
}

uint64_t RationalNumber::getGCD(uint64_t num1, uint64_t num2) {
    uint64_t gcd = 1;
    for (uint64_t i = 1; i <= num1 && i <= num2; i++) {
        if (num1 % i == 0 && num2 % i == 0) 
            gcd = i;
    }
    return gcd;
}

RationalNumber RationalNumber::add(RationalNumber rhs) {
    uint64_t leftNumerator = this->getNumerator() * rhs.getDenominator();
    uint64_t rightNumerator = rhs.getNumerator() * this->getDenominator();

    uint64_t tempNumerator = leftNumerator + rightNumerator;
    uint64_t tempDenominator = this->getDenominator() * rhs.getDenominator();
    
    uint64_t endNumerator;
    uint64_t endDenominator;

    // -- Simplify
    uint64_t gcd = getGCD(tempNumerator, tempDenominator);
    if (gcd == 1) {
        RationalNumber output(tempNumerator, tempDenominator);
        return output;
    } else {
        tempNumerator = tempNumerator / gcd;
        tempDenominator = tempDenominator / gcd;
        RationalNumber output(tempNumerator, tempDenominator);
        return output;
    }
}

RationalNumber RationalNumber::sub(RationalNumber rhs) {
    uint64_t leftNumerator = this->getNumerator() * rhs.getDenominator();
    uint64_t rightNumerator = rhs.getNumerator() * this->getDenominator();

    uint64_t tempNumerator = leftNumerator - rightNumerator;
    uint64_t tempDenominator = this->getDenominator() * rhs.getDenominator();
    
    uint64_t endNumerator;
    uint64_t endDenominator;

    uint64_t gcd = getGCD(tempNumerator, tempDenominator);
    if (gcd == 1) {
        RationalNumber output(tempNumerator, tempDenominator);
        return output;
    } else {
        tempNumerator = tempNumerator / gcd;
        tempDenominator = tempDenominator / gcd;
        RationalNumber output(tempNumerator, tempDenominator);
        return output;
    }
}

RationalNumber RationalNumber::mult(RationalNumber rhs) {
    uint64_t currentNumerator = this->getNumerator() * rhs.getNumerator();
    uint64_t currentDenominator = this->getDenominator() * rhs.getDenominator();
    RationalNumber output(currentNumerator, currentDenominator);
    return output;
}

RationalNumber RationalNumber::div(RationalNumber rhs) {
    char divZeroMessage[] = "Not divisible by 0";
    char *divZeroException = divZeroMessage;
    try {
        uint64_t outNumerator = this->getNumerator() * rhs.getDenominator();
        uint64_t outDenominator = this->getDenominator() * rhs.getNumerator();
        if (outDenominator != 0) {
            RationalNumber output(outNumerator, outDenominator);
            return output;
        } else {
            throw divZeroException;
        }
    } catch (const char* exception) {
        cout << exception << endl;
    }
}

double RationalNumber::sqrt() {
    double sqrtOutput;
    char negativeNumErrorMessage[] = "You cannot square root a negative number";
    char *negativeNumError = negativeNumErrorMessage;
    if (std::sqrt((double) this->getNumerator() / (double) this->getDenominator()) < 0) {
        throw negativeNumError;
    } else {
        sqrtOutput = std::sqrt((double) this->getNumerator() / (double) this->getDenominator());
    }
    return sqrtOutput;
}