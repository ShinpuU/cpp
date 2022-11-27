#include<iostream>
using namespace std;


template<class T>class Container{
        
    
    public:
        unsigned int mCounter = 0;
        static const unsigned int mSize = 6;    
        T mObjectTab[mSize];
        
        Container(){
            mCounter = 0;   
        }
        
        //methods
        void addObj(T &toAdd);
        void removeObj(unsigned int index);
        void dispArr();
        void dispSortedArr();
        
};

template<class T> void Container<T>::addObj(T &toAdd){
    
    if(mCounter==6) //prevent from adding if full
        return;
    
    mObjectTab[mCounter] = toAdd;
    mCounter++;
}

template<class T> void Container<T>::removeObj(unsigned int index){
    if(!(mObjectTab[index].isObjEmpty) and index < mCounter){
        mObjectTab[index] = mObjectTab[mCounter-1];
        mObjectTab[mCounter-1] = T();
        mCounter--;
    }
}

template<class T> void Container<T>::dispArr(){
    for(int i=0; i<mCounter; i++){
        cout<<i<<". ";
        mObjectTab[i].dispData();
        cout<<endl;
    }
}

template<class T> void Container<T>::dispSortedArr(){
    //copy table
    T tmpTab[mSize];
    for(int i=0; i<mCounter; i++){
        tmpTab[i] = mObjectTab[i];
    }
    
    //sort
    for(int i=0; i<mCounter-1; i++){
        for(int j=i+1; j<mCounter; j++){
            if(tmpTab[j] <= tmpTab[i]){
                swap(tmpTab[j], tmpTab[i]);
            }
        }
    }
    
    for(int i=0; i<mCounter; i++){
        tmpTab[i].dispData();
        cout<<" ";
    }
}




class Animal{
    private:
        string mName;
        float mWeight;
        int mBirthYear;
        string mId;
    public:
        bool isObjEmpty; //true if obj is empty, false if not
        Animal(string name, float weight, int birthYear, string id)
            : mName(name), mWeight(weight), mBirthYear(birthYear), mId(id){
            isObjEmpty = false;
        }
        
        Animal(){
            //setting tmp values for class to work 
            isObjEmpty = true;
            string mName = "tmp";
            float mWeight = 0;
            int mBirthYear = 0;
            string mId = "tmp";
        }
        
        //methods
        void dispData();
        int getYear(){ return mBirthYear; }
        float getWeight(){ return mWeight; }
};

void Animal::dispData(){
    cout<<mName<<" "<<mWeight<<" "<<mBirthYear<<" "<<mId;
}

bool operator<=(Animal firstAnimal, Animal secondAnimal){
    if(firstAnimal.getYear() > secondAnimal.getYear()){
        return true;
    } else if(firstAnimal.getYear() == secondAnimal.getYear()){
        if(firstAnimal.getWeight() <= secondAnimal.getWeight()){
            return true;
        }
        return false;
    }
    return false;
}

class Building{
    private:
        string mName = "";
        float mGPSx=0, mGPSy=0, mHeight=0;
    public:
        bool isObjEmpty;
        Building(string name, float GPSx, float GPSy, float height)
            : mName(name), mGPSx(GPSx), mGPSy(GPSy), mHeight(height){
            isObjEmpty = false;
        }
        Building(){
            isObjEmpty = true;
            mName="tmp";
        }
        //methods
        void dispData();
        float getXY(){ return (mGPSx + mGPSy); }
};

void Building::dispData(){
    cout<<mName<<" "<<mGPSx<<" "<<mGPSy<<" "<<mHeight;
}

bool operator<=(Building firstBuild, Building secondBuild){
    if(firstBuild.getXY() <= secondBuild.getXY()){
        return true;
    }
    return false;
}


//VALIDATION BELOW
bool isSpaceInString(const string &inputStr){
    for(char const &character : inputStr){
        if(isspace(character)){
            return false;
        }
    }
    
    return true;
}

bool isInputFloat(const string &inputStr){
    int dots = 0;
    for(char const &character : inputStr) {
        if((character != '.' and isdigit(character) == 0) or dots>1){
            return false;
        }
        if(character == '.'){
            dots++;
        }
    }
    return true;
}

bool isInputInt(const string &inputStr){
    for(char const &character : inputStr){
        if(isdigit(character)==0){
            return false;
        }
    }
    return true;
}

string validateString(string &inputStr){
    do{
        cin>>inputStr;
    }while(!isSpaceInString(inputStr));
    string outstr = inputStr;
    inputStr="";
    
    return outstr;
}

float validateFloat(string &inputStr){
    do{
        cin>>inputStr;
    }while(!isInputFloat(inputStr));
    
    float outfloat = stof(inputStr);
    inputStr="";
    return outfloat;
}

int validateInt(string &inputStr){
    do{
        cin>>inputStr;
    }while(!isInputInt(inputStr));
    int outint = stoi(inputStr);
    inputStr="";
    return outint;
}



int main() {
   
    Container<Animal> animal_container;
    Container<Building> building_container;
    
    string inputS, name, id;
    float weight;
    int birthYear;
    
    for(int i=0; i<4; i++){
        name = validateString(inputS);
        weight = validateFloat(inputS);
        birthYear = validateInt(inputS);
        id = validateString(inputS);
        
        Animal animalObj(name, weight, birthYear, id);
        animal_container.addObj(animalObj);
    }
    
    float x, y, height;
    
    for(int i=0; i<4; i++){
        name = validateString(inputS);
        x = validateFloat(inputS);
        y = validateFloat(inputS);
        height = validateFloat(inputS);
        
        
        Building buildingObj(name, x, y, height);
        building_container.addObj(buildingObj);
    }
    
    
    
    //animal_container.addObj(cat);
    //animal_container.addObj(krowa);
    
    
    // pkt5
    int index=0;
    cin>>index;
    animal_container.removeObj(index);
    
    //pkt 6
    animal_container.dispSortedArr();
    building_container.dispSortedArr();
    
    
    
    
    return 0;
}




