
#ifndef RationalNumber_h
#define RationalNumber_h
#include "RationalNumber.cpp"

#include <string>
#include <cmath>
#include <iostream>
#include <cinttypes>

using namespace std;

class RationalNumber {

    public:
        // -- Default Constructor
        RationalNumber();
        // -- Overload Constructor
        RationalNumber(int numerator, int denominator);
        // -- Copy Constructor
        RationalNumber(const RationalNumber &src);
        // -- Deconstructor
        ~RationalNumber();
        
        /* METHODS */

        string toString();
        bool equals(RationalNumber rhs);

        const int getNumerator();
        const int getDenominator();
    
        void setNumerator(int num);
        void setDenominator(int num);

        RationalNumber add(RationalNumber rhs);
        RationalNumber sub(RationalNumber rhs);
        RationalNumber mult(RationalNumber rhs);
        RationalNumber div(RationalNumber rhs);
        double sqrt();

    private:

        /* VARIABLES */
        uint64_t numerator;
        uint64_t denominator;

    protected:
        const uint64_t PRECISION = 100000;
        uint64_t getGCD(uint64_t num1, uint64_t num2);
};

#endif /* RationalNumber_h */