#include "ComplexNumber.h"
#include "RationalNumber.h"

#include <string>
#include <typeinfo>
#include <cmath>

using namespace std;

RationalNumber real;
RationalNumber imag;


ComplexNumber::ComplexNumber(): real(), imag() {}

ComplexNumber::ComplexNumber(double real, double imag) {
    this->setReal(real);
    this->setImag(imag);
}

ComplexNumber::ComplexNumber(const ComplexNumber &src) {
    this->real.setNumerator(src.real.getNumerator());
    this->real.setDenominator(*src.real.getDenominator());
    this->imag.setNumerator(&src.imag.getNumerator());
    this->imag.setDenominator(*src->imag.getDenominator());
}

ComplexNumber::~ComplexNumber() {}

void ComplexNumber::setReal(double num) {
    this->real.setNumerator(num * RationalNumber::PRECISION);
    this->real.setDenominator(PRECISION);
}

void ComplexNumber::setImag(double num) {
    this->imag.setNumerator(num * RationalNumber::PRECISION);
    this->imag.setDenominator(PRECISION);
}

double ComplexNumber::getReal() {
    return (double) this->real.getNumerator() / this->real.getDenominator();
}

double ComplexNumber::getImag() {
    return (double) this->imag.getNumerator() / this->imag.getDenominator();
}

string ComplexNumber::toString() {
    bool realNegative = false;
    bool imagNegative = false;
    if (this->getReal() < 0) realNegative = true;
    if (this->getImag() < 0) imagNegative = true;
    
    double realOutput = std::abs(this->getReal());
    double imagOutput = std::abs(this->getImag());

    if (realOutput == 0.0 && imagOutput == 0.0) {
        return "0";
    } else if (realOutput != 0.0 && imagOutput == 0.0) {
        if (realNegative) 
            return "-" + to_string(realOutput);
        return to_string(realOutput);
    } else if (realOutput == 0.0 && imagOutput != 0.0) {
        if (imagNegative)
            return "0 - " + to_string(imagOutput) + "i";
        return to_string(imagOutput) + "i";
    }
    if (realNegative && imagNegative) {
        return "-" + to_string(realOutput) + " - " + to_string(imagOutput) + "i";
    } else if (realNegative) {
        return "-" + to_string(realOutput) + " + " + to_string(imagOutput) + "i";
    } else if (imagNegative) {
        return to_string(realOutput) + " - " + to_string(imagOutput) + "i";
    } else {
        return to_string(realOutput) + " + " + to_string(imagOutput) + "i";
    }
}

ComplexNumber ComplexNumber::add(ComplexNumber rhs) {
    double realOutput = this->getReal() + rhs.getReal();
    double imagOutput = this->getImag() + rhs.getImag();
    ComplexNumber output(realOutput, imagOutput);
    return output;
}

ComplexNumber ComplexNumber::sub(ComplexNumber rhs) {
    double realOutput = this->getReal() - rhs.getReal();
    double imagOutput = this->getImag() - rhs.getImag();
    ComplexNumber output(realOutput, imagOutput);
    return output;
}

ComplexNumber ComplexNumber::mult(ComplexNumber rhs) {
    double realOutput = this->getReal() * rhs.getReal();
    double imagOutput = this->getImag() * rhs.getImag();
    ComplexNumber output(realOutput, imagOutput);
    return output;
}

ComplexNumber ComplexNumber::div(ComplexNumber rhs) {
    char divZeroMessage[] = "Cannot be divisible by 0";
    char *divZeroException = divZeroMessage;
    double realOutput = 0;
    double imagOutput = 0;
    try {
        if (rhs.getReal() == 0 || rhs.getImag() == 0) {
            throw divZeroException;
        } else {
            realOutput = this->getReal() / rhs.getReal();
            imagOutput = this->getImag() / rhs.getImag();
        }
    } catch (const char* exception) {
        cout << "Exception: " << exception << endl;
    }
    ComplexNumber output(realOutput, imagOutput);
    return output;
} 

double ComplexNumber::mag() {
    double realOutput = this->real;
    double imagOutput = this->imag;
    double output = std::sqrt(std::pow(realOutput, 2) + std::pow(imagOutput, 2));
    return output;
}

ComplexNumber ComplexNumber::conj() {
    double imagOutput = 0 - this->imag;
    ComplexNumber output(this->real, imagOutput);
}

ComplexNumber ComplexNumber::sqrt() {
    // -- sqrt(-1) = i
    // -- sqrt(i) = -1
    if (this->real < 0 && this->imag < 0) {
        double realOutput = std::sqrt(std::abs(this->imag));
        double imagOutput = std::sqrt(std::abs(this->real));
        ComplexNumber output(realOutput, imagOutput);
        return output;
    } else if (this->real < 0) {
        double realOutput = 0;
        double imagOutput = std::sqrt(abs(this->real)) + std::sqrt(this->imag);
        ComplexNumber output(realOutput, imagOutput);
        return output;
    } else if (this->imag < 0) {
        double realOutput = std::sqrt(this->real) + std::sqrt(std::abs(this->imag));
        double imagOutput = 0;
        ComplexNumber output(realOutput, imagOutput);
        return output;
    }
    double realOutput = std::sqrt(this->real);
    double imagOutput = std::sqrt(this->imag);
    ComplexNumber output(realOutput, imagOutput);
    return output;
}

bool ComplexNumber::equals(ComplexNumber& rhs) {
    if (typeid(*this) != typeid(rhs))
        return false;
    if (this->real == rhs.real && this->imag == rhs.imag)
        return true;
    return false;
}