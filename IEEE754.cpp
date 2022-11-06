#include<iostream>
#include <cmath>
using namespace std;

bool evaluateSign(string &input);

int evaluateExponent(string &input); 
bool isNumber(const string &str_num);

float evaluateMantissa(string &input);
bool isFloat(const string &str_num);

class IEEEnum{
  private:
    bool mSign;
    int mExponent;
    float mMantissa;
    
    int calculateExponent(float &num){
        
        int exponent = 0;
        while(num>=2){
            num/=2;
            exponent++;
        }
        
        while(num<1){
            num*=2;
            exponent--;
        }
        return exponent;
    }
    
  public:
    float mNum;
    
    IEEEnum(){}; //default constructor;
    
    IEEEnum(bool sign, int exponent, float mantissa)
        : mSign(sign), mExponent(exponent), mMantissa(mantissa)
    {
        
        int sign_multiplier;
        if (mSign) {
            sign_multiplier = 1;
        } else {
            sign_multiplier = -1;
        }
        
        mNum = pow(2, mExponent-127) * sign_multiplier * mMantissa;
        
    }
    
    
    IEEEnum(float num){
        floatToIEEE(num);
    }
    
    void floatToIEEE(float num){
        mNum = num;

        if(num >= 0)
            mSign = true;
        else{
            mSign = false;
            num *= -1;
        }


        mExponent = calculateExponent(num);
        mExponent+127;

        mMantissa = num;
    }
    
    bool operator+=(IEEEnum &myIEEE){
        float addedNumber = mNum + myIEEE.mNum;
        floatToIEEE(addedNumber);
        return true;
    }
    
    bool operator-=(IEEEnum &myIEEE){
        float subNumber = mNum - myIEEE.mNum;
        floatToIEEE(subNumber);
        return true;
    }
    

};

IEEEnum operator+(IEEEnum a, IEEEnum b){
    return IEEEnum(a.mNum + b.mNum);
}

IEEEnum operator-(IEEEnum a, IEEEnum b){
    return IEEEnum(a.mNum - b.mNum);
}

std::ostream& operator<<(std::ostream &out, const IEEEnum &toDisp){
    return out<<toDisp.mNum;
}

//VALIDATION OF INPUT BELOW

bool evaluateSign(string &input){
    do{
        cin>>input;
    }while(input.length() != 1 || (input[0] != '+' && input[0] != '-') );
    
    bool sign = true;
    if(input[0] == '-'){
        sign=false;
    }
    input=""; //clear input after each validation
    return sign;
}

//=============EXPONENT============

int evaluateExponent(string &input){
    do{
        cin>>input;
    }while(isNumber(input)==false);
    
    int myInt = stoi(input);
    input="";
    
    return myInt;
}

bool isNumber(const string &str_num){
    
    for( const char &zn : str_num ){
        if(isdigit(zn) == 0){
            return false;
        }
    }
    return true;
}

//==========MANTISSA=================
float evaluateMantissa(string &input){
    do{
        cin>>input;
    }while(isFloat(input)==false);
    
    float myFloat = stof(input);
    input="";
    return myFloat;
}
 
bool isFloat(const string &str_num){
    int dots = 0;
    for(const char &zn : str_num){
        if( (isdigit(zn)==0 and zn!='.') or dots > 1 )
            return false;
            
        if(zn=='.'){
            dots++;
        }
    }
    return true;
}


int main() {
    
    string input;
    
    //calculating values of x0
    bool sign = evaluateSign(input);
    int exponent = evaluateExponent(input);
    float mantissa = evaluateMantissa(input);
    
    IEEEnum x0(sign, exponent, mantissa);
    
    sign = evaluateSign(input);
    exponent = evaluateExponent(input);
    mantissa = evaluateMantissa(input);
    
    IEEEnum x1(sign, exponent, mantissa);
    
    
    IEEEnum x2(evaluateMantissa(input));
    IEEEnum x3(evaluateMantissa(input));
    
    x0+=x1;
    x3-=x2;
    IEEEnum x4 = x1 + x3;
    IEEEnum x5 = x4 - x2;
    cout<<x0<<" "<<x1<<" "<<x2<<" "<<x3<<" "<<x4<<" "<<x5;
    
    
    
    
    
    return 0;
}

