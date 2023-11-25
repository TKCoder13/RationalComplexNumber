#pragma once

#include <string>
#include <iostream>

using namespace std;

class ComplexNumber : public RationalNumber {
    public:
        // -- Constructors
        ComplexNumber();
        ComplexNumber(double real, double imag);
        ComplexNumber(const ComplexNumber &src);
        ~ComplexNumber();

        // -- Methods
        void setReal(double num);
        void setImag(double num);

        double getReal();
        double getImag();

        string toString();

        ComplexNumber add(ComplexNumber rhs);
        ComplexNumber sub(ComplexNumber rhs);
        ComplexNumber mult(ComplexNumber rhs);
        ComplexNumber div(ComplexNumber rhs);

        double mag();
        ComplexNumber conj();
        ComplexNumber sqrt();

        bool equals(ComplexNumber& rhs);
        
        ComplexNumber& operator=(const ComplexNumber& rhs){ 
            this->real.setNumerator(rhs.real.getNumerator()); 
            this->real.setDenominator(rhs.real.getDenominator()); 
            this->imag.setNumerator(rhs.imag.getNumerator()); 
            this->imag.setDenominator(rhs.imag.getDenominator()); 
            return *this; 
        }

    private:
        RationalNumber real;
        RationalNumber imag;
};