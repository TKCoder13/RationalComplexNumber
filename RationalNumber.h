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
        RationalNumber(uint64_t numerator, uint64_t denominator);
        // -- Copy Constructor
        RationalNumber(const RationalNumber &src);
        // -- Deconstructor
        ~RationalNumber();
        
        /* METHODS */

        string toString();
        bool equals(RationalNumber rhs);

        uint64_t getNumerator();
        uint64_t getDenominator();
    
        void setNumerator(uint64_t num);
        void setDenominator(uint64_t num);

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
