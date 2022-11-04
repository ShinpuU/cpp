#include <iostream>

class Complex{
    double re, im;
public:
    Complex (double r = 0.0, double i = 0.0) : re(r), im(i){}
    operator int (){
        return int(re);
    }
    double getIm();
    double getRe();
    friend Complex operator+ (double, Complex);
    friend Complex operator+ (Complex, double);
    friend Complex operator+(Complex, Complex);

    friend Complex operator*(double, Complex);
    friend Complex operator*(Complex, double);
    friend Complex operator*(Complex, Complex);
};

double Complex::getIm(){
    return im;
}

double Complex::getRe(){
    return re;
}

//Addition
Complex operator+ (Complex a1, Complex a2){
    return Complex(a1.re + a2.re, a1.im + a2.im);
}

Complex operator+ (Complex a1, double a2){
    return Complex(a1.getRe() + a2, a1.getIm() + a2);
}

Complex operator+ (double a1, Complex a2){
    return Complex(a1+ a2.getRe(), a1+ a2.getIm());
}

//Multiplication
Complex operator* (Complex a1, Complex a2){
    return Complex(a1.re * a2.re - a1.im + a2.im,
                   a1.re * a2.im + a1.im * a2.re);
}

Complex operator*(double a1, Complex a2){
    return Complex(a1 * a2.getRe() - a2.getIm(),
                   a1 * a2.getIm() + a2.getRe());
}

Complex operator*(Complex a1, double a2){
    return Complex(a1.getRe() * a2 - a1.getIm(),
                   a1.getRe() + a1.getIm() * a2);
}

std::ostream& operator<<(std::ostream& out, Complex& toDisp){
    return out << toDisp.getRe() << " " << toDisp.getIm();
}


int main() {
    Complex Z1(3, 5), Z2(7.0, 5.3), sum;
    double num1 = 4.5;

    sum = Z1+num1;

    std::cout<<sum<<std::endl;


    return 0;
}
