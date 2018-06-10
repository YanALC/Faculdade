#ifndef COMPLEX_H
#define COMPLEX_H
#include <QString>
#include <string>
class Complex
{
public:
    Complex();
    ~Complex();
    void set(float real, float imaginary);
    QString get();
    Complex operator + (Complex & number) const;
    Complex operator - (Complex & number) const;
    Complex operator * (Complex & number) const;
    Complex operator / (Complex & number) const;
    void operator = (const Complex & number);
    bool operator == (Complex & number);
    int operator | (Complex & number);
private:
    float real=0;
    float imaginary=0;
};

#endif // COMPLEX_H
