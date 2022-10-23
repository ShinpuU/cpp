#include<iostream>

using namespace std;
//enum TypeOfEngine {B, D, E, H};

class Car{
  public:


    Car() = default;
    Car(string regNum, int horsePower, double weight, char engineType)
        : mRegNum(regNum), mHorsePower(horsePower), mWeight(weight), mTypeOfEngine(engineType)
    {

    }

    string getRegNum(){
        return mRegNum;
    }

    int getHorsePower(){
        return mHorsePower;
    }

    double getWeight(){
        return mWeight;
    }

    char getTypeOfEngine(){
        return mTypeOfEngine;
    }


  private:
    string mRegNum;
    int mHorsePower;
    double mWeight;
    char mTypeOfEngine;


};

class CarCatalogue{
  public:
    static const unsigned int kSize = 6;
    Car mCars[kSize+1];


    CarCatalogue() = default; 
    void addCars(Car toAdd);
    void dispCars();
    void removeCars(Car toRemove);
    int minChild(int parent);

    unsigned int minChild(Car heap[], unsigned int heapElements, const unsigned int parent);
    //removes root by default
    void removeCars();

  private:
    unsigned int mCounter = 0;
    int heapSize {};


};

void CarCatalogue::addCars(Car toAdd){


    if(mCounter < 7){

        int child = ++heapSize;
        int parent = child/2;
        int localHorsePower = toAdd.getHorsePower();
        while (parent and mCars[parent].getHorsePower() > localHorsePower){
            mCars[child] = mCars[parent];
            child = parent;
            parent /= 2;
        }
        mCars[child] = toAdd;
        mCounter++;

    }
}

void CarCatalogue::dispCars(){
    //sort them?
    // void heapsort(double vector[], int size) {
    //     assert (size <= HEAP_MAX);
    //     for (int i = 0; i < size; i++)
    //         insert(vector[i]);
    //     for (int i = 0; i < size; i++){
    //         vector[i] = min();
    //         removeMin();
    //     }
    // }

    Car sortedCars[7];

    for(int i=1; i<=heapSize; i++){
        sortedCars[i] = mCars[i];
    }

    for(int i=1; i<=heapSize; i++){
        for(int j=2; j<=heapSize; j++){
            if(sortedCars[j-1].getHorsePower() > sortedCars[j].getHorsePower()){
                swap(sortedCars[j-1], sortedCars[j]);
            }
        }
    }

    for(int i=1; i<=heapSize; i++){
        cout<<sortedCars[i].getRegNum()<<" "<<sortedCars[i].getHorsePower()<<" ";
    }
}

int CarCatalogue::minChild(int parent) {
    int left = 2*parent;
    int right = left + 1;
    if (left > heapSize)return 0;
    if (right > heapSize or mCars[left].getHorsePower() < mCars[right].getHorsePower())return left;
    return right;
}

void CarCatalogue::removeCars(Car toRemove){

    int index {};
    for (int i = 1; i <= heapSize; i++) {
        if (mCars[i].getRegNum() == toRemove.getRegNum()) {
            index = i;
        }
    }
    
    Car last = mCars[heapSize--];

    int x{index}, c = minChild(index);

    while(c and mCars[c].getHorsePower() < last.getHorsePower()){
        mCars[x] = mCars[c];
        x = c;
        c = minChild(mCars, heapSize, c);
    }

    if(mCars[c].getHorsePower() == last.getHorsePower() and mCars[c].getWeight() < last.getWeight()){
        mCars[x] = mCars[c];
        mCars[c] = last;
    }else{
        mCars[x] = last;
    }

}

unsigned int CarCatalogue::minChild(Car heap[], unsigned int heapElements, const unsigned int parent){
    const unsigned int left = parent<<1, right = left + 1;
    if(left > heapElements) return 0;
    if(right > heapElements or heap[right].getHorsePower() > heap[left].getHorsePower()) return left;
    return right;
}

void CarCatalogue::removeCars(){
    //removes root by default
    
    Car last = mCars[heapSize--];

    int x{1}, c = minChild(1);

    while(c and mCars[c].getHorsePower() < last.getHorsePower()){
        mCars[x] = mCars[c];
        x = c;
        c = minChild(mCars, heapSize, c);
    }

    if(mCars[c].getHorsePower() == last.getHorsePower() and mCars[c].getWeight() < last.getWeight()){
        mCars[x] = mCars[c];
        mCars[c] = last;
    }else{
        mCars[x] = last;
    }
}



//VALIDATION
bool isRegCorrect(string reg_num){
    if(reg_num.length()>4){
        return false;
    }
    for (int i = 0; i < reg_num.length(); i++) {
        char ch = reg_num[i];
        if ((not(ch >= 'A' && ch <= 'Z')) && (not(ch >= 'a' && ch <= 'z')) && (not(ch >= '0' && ch <= '9'))) {
            return false;
        }
    }

    //string is correct
    return true;
}

bool isHorsePowCorrect(string horse_power){
    //isINT
    
    for(int i=0; i<horse_power.length(); i++){
        char value = horse_power[i];
        if(!(value >= 48 && value <= 57)){
            return false;
        }
    }

    return true;
}

bool isWeightCorrect(string weight){
    //isDouble

    for(int i=0; i<weight.length(); i++){
        char value = weight[i];
        if(!((value >= 48 && value <= 57) || value == '.')){
            return false;
        }
    }

    return true;
}


int main(){

    CarCatalogue myCatalog;

    //DEBUG CODE

    // Car auto1("Aa00", 100, 2, 'B');
    // Car auto2("Bb01", 40, 0.7, 'B');
    // Car auto3("Cc02", 90, 1.5, 'D');
    // Car auto4("Dd03", 150, 1.8, 'D');
    // Car auto5("Ee04", 70, 1.1, 'E');
    // Car auto6("Ff05", 140, 2.1, 'H');
    // myCatalog.addCars(auto1);
    // myCatalog.addCars(auto2);
    // myCatalog.addCars(auto3);
    // myCatalog.addCars(auto4);
    // myCatalog.addCars(auto5);
    // myCatalog.addCars(auto6);

    // myCatalog.dispCars();
    // cout<<endl<<"po usunieciu"<<endl;
    // myCatalog.removeCars(auto3);
    // myCatalog.dispCars();


    //ACTUAL VALIDATION

    string reg_num, s_horse_power, s_weight, s_engine_type;
    int horse_power;
    double weight;
    char engine_type;

    for(int i=0; i<6; i++){
        int counter = 0;
        while(counter<4){
            if(counter==0){
                cin>>reg_num;
                if(isRegCorrect(reg_num)){
                    counter++;
                }else{
                    continue;
                }
            }

            if(counter==1){
                cin>>s_horse_power;
                if(isHorsePowCorrect(s_horse_power)){
                    horse_power = stoi(s_horse_power);
                    counter++;
                }else{
                    continue;
                }
            }

            if(counter==2){
                cin>>s_weight;
                if(isWeightCorrect(s_weight)){
                    weight = stod(s_weight);
                    counter++;
                }else{
                    continue;
                }
            }

            if(counter==3){
                cin>>s_engine_type;
                if(s_engine_type[0]=='B' || s_engine_type[0]=='D' || s_engine_type[0]=='H' || s_engine_type[0]=='E'){
                    engine_type = s_engine_type[0]; //make a function for this
                    counter++;
                }else{
                    continue;
                }
            }
            Car carToAdd(reg_num, horse_power, weight, engine_type);
            myCatalog.addCars(carToAdd);

        }
    }
    myCatalog.dispCars();

    return 0;
}
