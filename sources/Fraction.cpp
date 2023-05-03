#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <algorithm>
#include <cmath>
#include "Fraction.hpp" 
#include <limits>
using namespace std;

Fraction::Fraction(int number1 , int number2){
    if(number2 == 0){
        throw invalid_argument ("denominator can not be zero");
    }
    else{
        up = number1;
        down = number2;
    }
    if(number2 < 0){
        up = up*-1;
        down = down*-1;
    }
    
}
Fraction::Fraction(float fraction): up(fraction*1000) , down(1000){}
Fraction::Fraction(): up(0) , down(1){}
Fraction Fraction::operator +(const Fraction& fraction) const{ //Fraction + Fraction 
    Fraction f1(this->up , this->down);
    Fraction reduced1 = reduce(f1);
    Fraction reduced2 = reduce(fraction);
    //overflow checking
    int max_int = numeric_limits<int>::max();
    int min_int = numeric_limits<int>::min();
    long long _up = reduced1.up;
    long long _down = reduced1.down;
    long long _up2 = reduced2.up;
    long long _down2 = reduced2.down;
    if (reduced2.up == 0){
        return reduced1;
    }
    else if (_up == 0){
        return reduced2;
    }
    int lcm = find_lcm(_down , _down2); 
    long long long_lcm = lcm;
    long long result = (long_lcm/_down *_up) + (long_lcm/_down2 *_up2);
    if( result > max_int || result < min_int) throw overflow_error("overflow");
    int new_up = (lcm/_down *_up) + (lcm/_down2 *_up2);
    //reduce Fraction to minimal
    Fraction temp(new_up , lcm);
    return reduce(temp);
}
Fraction Fraction::operator +(float number) const{ //Fraction + float
    Fraction f1(this->up , this->down);
    Fraction f2(number*1000 , 1000);
    return f1 + f2;
}
Fraction operator +(double number , const Fraction& f2){ // double + Fraction
    Fraction f1(number*1000 , 1000);
    return f1+f2;
}
Fraction operator +(float number , const Fraction& fraction){ // float + Fraction
    Fraction f2(number*1000 , 1000);
    return fraction + f2;
}
Fraction Fraction::operator-(const Fraction &fraction) const {
        Fraction a(this->up , this->down);
        Fraction b(fraction.up , fraction.down);
        Fraction reduced1 = reduce(a);
        Fraction reduced2 = reduce(b);
        int64_t num = (int64_t ) reduced1.up * reduced2.down - (int64_t )reduced2.up * reduced1.down;
        int64_t denom = (int64_t) reduced1.down * reduced2.down;
        if (num > std::numeric_limits<int>::max() || num < std::numeric_limits<int>::min() || 
        denom > std::numeric_limits<int>::max() || denom < std::numeric_limits<int>::min()) {
            throw std::overflow_error("Overflow occurred during subtraction");
        }
        num = (int) num;
        denom = (int) denom;

        int g = find_gcd(num, denom);
        return Fraction(num / g, denom / g);
    }
// Fraction Fraction::operator -(const Fraction& fraction) const{ //Fraction - Fraction
//     Fraction f1(this->up , this->down);
//     Fraction reduced1 = reduce(f1);
//     Fraction reduced2 = reduce(fraction);
//     if (reduced2.up == 0){
//         return reduced1;
//     }
//     else if (this->up == 0){
//         reduced2.up = reduced2.up * -1;
//         return reduced2;
//     }
//     int lcm = find_lcm(reduced1.down , reduced2.down);
//     int new_up = (lcm/reduced1.down*reduced1.up) - (lcm/reduced2.down*reduced2.up);
//     //reduce Fraction to minimal
//     Fraction temp(new_up , lcm);
//     return reduce(temp);
// }
Fraction Fraction::operator -(int num) const{ //Fraction - int
    Fraction f1 (this->up , this->down);
    Fraction f2 (num , 1);
    return f1-f2;
}
Fraction Fraction::operator -(double number) const { // Fraction - double
    Fraction f1(this->up , this->down);
    Fraction f2(number*1000 , 1000);
    return f1 - f2;
}
Fraction operator -(float number , const Fraction& f2){ //float - Fraction
    Fraction f1 (number*1000 , 1000);
    return f1-f2;
}
Fraction operator -(double number , const Fraction& f2){ // double - Fraction
    Fraction f1(number*1000 , 1000);
    return f1-f2;
}
Fraction Fraction::operator *(const Fraction& fraction) const{ //Fraction * Fraction
    Fraction f1(this->up , this->down);
    Fraction reduced1 = reduce(f1);
    Fraction reduced2 = reduce(fraction);
    //overflow checking
    int max_int = numeric_limits<int>::max();
    int min_int = numeric_limits<int>::min();
    long long _up = reduced1.up;
    long long _down = reduced1.down;
    long long _up2 = reduced2.up;
    long long _down2 = reduced2.down;
    if(_up*_up2 > max_int || _up*_up2 < min_int || _down*_down2 > max_int || _down*_down2 < min_int)
    throw overflow_error("overflow");
    int new_up = reduced1.up * reduced2.up;
    int new_down = reduced1.down * reduced2.down;
    //reduce Fraction to minimal
    Fraction temp(new_up , new_down);
    return reduce(temp);
}
Fraction operator *(float number ,const Fraction& fraction){ //float * Fraction
    Fraction multi(number*1000 , 1000);            
    return multi * fraction;
} 
Fraction Fraction::operator/(const Fraction &fraction) const {
    if (fraction.up == 0) {
        throw std::runtime_error("Division by zero");
    }
    if (this->up == 0){
        Fraction zero(0,1);
        return zero;
    }
    Fraction a(this->up , this->down);
    Fraction b(fraction.up , fraction.down);
    Fraction reduced1 = reduce(a);
    Fraction reduced2 = reduce(b);
    int64_t num = (int64_t) reduced1.up * reduced2.down;
    int64_t denom = (int64_t) reduced1.down * reduced2.up;
    if (num > std::numeric_limits<int>::max() || denom > std::numeric_limits<int>::max()) {
        throw std::overflow_error("Overflow occurred during division");
    }
    num = (int) num;
    denom = (int) denom;
    int g = find_gcd(num, denom);
    return Fraction(num / g, denom / g);
}
// Fraction Fraction::operator /(const Fraction& fraction) const{ //Fraction / Fraction
//     if(fraction.up == 0 || fraction.down == 0 || this->down == 0){
//     throw runtime_error("can not divide by 0!");
//     }
//     else if(this->up == 0){
//         Fraction s(0 , 1);
//         return s;
//     }
//     int new_up = this->up * fraction.down;
//     int new_down = fraction.up * this->down;
//     //reduce Fraction to minimal
//     Fraction temp(new_up , new_down);
//     return reduce(temp);
// }
Fraction operator /(float number , const Fraction& fraction){ //float / Fraction
    Fraction f1(number*1000 , 1000);
    return f1/fraction;
}

bool Fraction::operator ==(const Fraction& fraction) const{ // Fraction == Fraction
    if(this->up == 0){
        if(fraction.up == 0){
            return true;
            }
        else return false;
    }
    float up1 = this->up;
    float down1 = this->down;
    float up2 = fraction.up;
    float down2 = fraction.down;
    float fraction_a = up1/down1;
    float fraction_b = up2/down2;
    Fraction f1(fraction_a * 1000 , 1000);
    Fraction f2(fraction_b * 1000 , 1000);
    if(f1.up == f2.up) return true;
    return false;
    }
bool operator ==(double number , const Fraction& fraction){ // double == Fraction
    Fraction f1(number*1000 , 1000);
    return f1 == fraction;
}
bool Fraction::operator ==(float number) const{ // Fraction == float
    Fraction f1(this->up , this->down);
    Fraction f2(number*1000 , 1000);
    return  f1 == f2;
}
bool Fraction::operator !=(const Fraction& fraction) const{ // Fraction != Fraction
float up1 = this->up;
float down1 = this->down;
float up2 = fraction.up;
float down2 = fraction.down;
if(up1/down1 != up2/down2) return true;
return false;
}
bool Fraction::operator >(const Fraction& fraction) const{ // Fraction > Fraction
    float up1 = this->up;
    float down1 = this->down;
    float up2 = fraction.up;
    float down2 = fraction.down;
    if(up1/down1 > up2/down2) return true;
    return false;
    }
bool operator >(double number , const Fraction& fraction){ // double > Fraction
    Fraction f1(number*1000 , 1000);
    return f1 > fraction;
}
bool Fraction::operator >(float number) const{ // Fraction > float
    float up = this->up;
    float down = this->down;
    if((up/down) > number) return true;
    return false;
    }
bool Fraction::operator >=(const Fraction& fraction) const{ // Fraction >= Fraction
    float up1 = this->up;
    float down1 = this->down;
    float up2 = fraction.up;
    float down2 = fraction.down;
    if(up1/down1 >= up2/down2) return true;
    return false;
    }
bool operator >=(double number , const Fraction& fraction){ // double >= Fraction
    Fraction f1(number*1000 , 1000);
    return f1 >= fraction;
}
bool Fraction::operator <(const Fraction& fraction) const{ // Fraction < Fraction
    float up1 = this->up;
    float down1 = this->down;
    float up2 = fraction.up;
    float down2 = fraction.down;
    if(up1/down1 < up2/down2) return true;
    return false;
    }
bool operator <(double number , const Fraction& fraction){ // double < Fraction
    Fraction f1(number*1000 , 1000);
    return f1<fraction;
}
bool Fraction::operator <=(const Fraction& fraction) const{ // Fraction <= Fraction
    float up1 = this->up;
    float down1 = this->down;
    float up2 = fraction.up;
    float down2 = fraction.down;
    if(up1/down1 <= up2/down2) return true;
    return false;
    }
bool operator <=(double number , const Fraction& fraction){ // double <= Fraction
    Fraction f1(number*1000 , 1000);
    return f1 <= fraction;
}
Fraction Fraction::operator ++(){
    this->up = this->up+this->down;
    Fraction temp(this->up, this->down);
    return reduce(temp);
}
Fraction Fraction::operator ++(int dummy){
    Fraction temp(this->up , this->down);
    this->up = this->up+this->down;
    return reduce(temp);
}
Fraction Fraction::operator --(){
    this->up = this->up - this->down;
    Fraction temp(this->up , this->down);
    return reduce(temp);
}
Fraction Fraction::operator --(int dummy) {
    Fraction temp(this->up , this->down);
    this->up = this->up - this->down;
    return reduce(temp);}
ostream& operator <<(ostream& os , const Fraction& fraction){
    Fraction dummy; //to call reduce function
    Fraction f1 = dummy.reduce(fraction);
    os << f1.up << '/' << f1.down;
    return os;
    } //friend
istream& operator >>(istream& input , Fraction& fraction){
    int up , down;
    if((input >> up >> down) && down!=0){
        int gcd = fraction.find_gcd(up,down);
        fraction.up = up/gcd;
        fraction.down = down/gcd;
    } else {
        throw runtime_error("one input only");
    }
    return input;
    } //friend
// int Fraction::find_gcd(int number1 , int number2) const{          
//     number1 = abs(number1);
//     number2 = abs(number2);
//     while(number1 != number2){
//     if(number1 > number2)
//         number1 -= number2;
//     else
//         number2 -= number1;
//     }
//     return number1;
// }
int Fraction::find_gcd(int left, int right) const{
    if (right == 0) {  return left;
    } else { return find_gcd(right, left % right); }
}
int Fraction::find_lcm(int number1 , int number2) const{ //lcm took from https://www.programiz.com/cpp-programming/examples/lcm
    number1 = abs(number1);
    number2 = abs(number2);
    int lcm = (number1 > number2) ? number1 : number2; 
    do
    {
        if (lcm % number1 == 0 && lcm % number2 == 0)
        {
            break;
        }
        else
            ++lcm;
    } while (true);
    return lcm;
}
Fraction Fraction::reduce(const Fraction& fraction) const{
    if(fraction.up == 0){
        Fraction zero(0,1);
        return zero;
    }
    int temp_up = fraction.up;
    int temp_down = fraction.down;
    if(fraction.down < 0){
        int temp_down = fraction.down * -1;
        int temp_up = fraction.up * -1;
    }
    int gcd = find_gcd(fraction.up , fraction.down); 
    return Fraction(temp_up/gcd , temp_down/gcd);
}
int Fraction::getNumerator(){
    return this->up;
}
int Fraction::getDenominator(){
    return this->down;
}