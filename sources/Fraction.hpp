#ifndef FRACTION_HPP
#define FRACTION_HPP
#include <iostream>
using namespace std;
namespace ariel{}


class Fraction{

    private:
    int up;
    int down;

    public:
    Fraction(int number1 , int number2);
    Fraction(float fraction);
    Fraction();
    int getNumerator();
    int getDenominator();
    Fraction operator +(const Fraction& fraction) const;
    Fraction operator +(float fraction) const;
    friend Fraction operator +(float number , const Fraction& fraction);
    friend Fraction operator +(double number , const Fraction& fraction);
    Fraction operator -(const Fraction& fraction) const;
    Fraction operator -(int num) const;
    Fraction operator -(double number) const;
    friend Fraction operator -(float number , const Fraction& fraction);
    friend Fraction operator -(double number , const Fraction& fraction);
    Fraction operator *(const Fraction& fraction) const;
    friend Fraction operator *(float number , const Fraction& fraction);
    Fraction operator /(const Fraction& fraction) const;
    friend Fraction operator /(float number , const Fraction& fraction);
    bool operator ==(const Fraction& fraction) const;
    bool operator ==(float number) const;
    friend bool operator ==(double number , const Fraction& fraction);
    bool operator !=(const Fraction& fraction) const;
    bool operator >(const Fraction& fraction) const;
    friend bool operator >(double number , const Fraction& fraction);
    bool operator >(float number) const;
    bool operator >=(const Fraction& fraction) const;
    friend bool operator >=(double number , const Fraction& fraction);
    bool operator <(const Fraction& fraction) const;
    friend bool operator <(double number , const Fraction& fraction);
    bool operator <=(const Fraction& fraction) const;
    friend bool operator <=(double number , const Fraction& fraction);
    Fraction operator ++();
    Fraction operator ++(int dummy);
    Fraction operator --();
    Fraction operator --(int dummy);
    friend ostream& operator <<(ostream& output , const Fraction& fraction);
    friend istream& operator >>(istream& input , Fraction& fraction);
    int find_gcd(int number1 , int number2) const;
    int find_lcm(int number1 , int number2) const;
    Fraction reduce(const Fraction& fraction) const;
};

#endif