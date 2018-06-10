#include<math.h>
#include "complex.h"

Complex::Complex()
{

}
void Complex::set(float real, float imaginary){
    this->real=real;
    this->imaginary=imaginary;
}

QString Complex::get(){
    QString ss;
    ss = QString::number(this->real);
    if (this->imaginary>=0){
        ss = ss + " + " + QString::number(this->imaginary);
    }else{
        this->imaginary=this->imaginary*(-1);
        ss = ss + " - " + QString::number(this->imaginary);
    }
    ss = ss+"i";
    return ss;
}

Complex Complex::operator + (Complex & number) const{
    Complex num;
    num.set(number.real+this->real, number.imaginary+this->imaginary);
    return num;
}

Complex Complex::operator - (Complex & number) const{
    Complex num;
    num.set(number.real-this->real, number.imaginary-this->imaginary);
    return num;
}

Complex Complex::operator * (Complex & number) const{
    Complex num;
    num.set(((number.real*this->real)-(number.imaginary*this->imaginary)),((number.real*this->imaginary)+(number.imaginary*this->real)));
    return num;
}

Complex Complex::operator / (Complex & number) const{
    Complex num;
    num.set(((number.real*this->real)+(number.imaginary*this->imaginary))/((pow(this->real,2))+(pow(this->imaginary,2))),((number.imaginary*this->real)-(number.real*this->imaginary))/(pow(this->real,2)+pow(this->imaginary,2)));
    return num;
}

void Complex::operator = (const Complex & number){
    this->real=number.real;
    this->imaginary=number.imaginary;
}

bool Complex::operator == (Complex & number){
    if((number.real==this->real) && (number.imaginary==this->imaginary)){
        return true;
    }
    else
        return false;
}

int Complex::operator | (Complex & number){
    if ((number.real!=this->real) && (number.imaginary==this->imaginary)){
        return 1;
    }else{
        if((number.real==this->real) && (number.imaginary!=this->imaginary))
            return 2;
        else{
            if ((number.real==this->real) && (number.imaginary==this->imaginary))
                return 3;
            else
                return 4;
        }
    }
}

Complex::~Complex(){

}
