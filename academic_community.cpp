#include <iostream>
#include <cmath>
using namespace std;

enum sexVar{
    K,
    M
};

class Student;

void bubbleSort(Student *tab);

//===========================
//CLASS PERSON 
//=========================

class Person{
private:
    string mName;
    string mLastname;
    float mWeight; //in kg
    float mHeight; //in cm
    int mAge; //in years
protected:
    sexVar mSex;

public:
    Person() = default;
    Person(string name, string lastname, float weight, float height, int age, sexVar sex)
            : mName(name), mLastname(lastname), mWeight(weight), mHeight(height), mAge(age), mSex(sex) {

    }
    void dispPerson() const;
    float calcBMI();
    
    int getAge(){
        return mAge;
    }
    
    string getNameAndLastname(){ return mName+" "+mLastname; }

};

void Person::dispPerson() const {
    cout<<mName<<" "<<mLastname<<" "<<mWeight<<" "<<mHeight<<" "<<mAge;
    
}

float Person::calcBMI() {
    return mWeight / (pow(mHeight, 2.0));
}

//===========================
//CLASS STUDENT
//=========================
class Student : public Person{
private:
    string mIndexNum;
    int mYear;
    double *mGrades;
public:
    Student(string indexNum, int year, double *grades, string name, string lastname, float weight, float height, int age, sexVar sex)
            :  mIndexNum(indexNum), mYear(year), Person(name, lastname, weight, height, age, sex){
        mGrades = grades;
    }
    Student(){ mIndexNum = ""; mGrades = new double[10]; }
    double calculateMean();
    
    int getYear(){ return mYear; }
    string getIndex(){ return mIndexNum; }
     
};

double Student::calculateMean(){
    int i=0;
    double sum=0;
    while(i<10){
        if(mGrades[i]==0){
            break;
        }
        sum+=mGrades[i];
        i++;
    }
    
    if(i>0){
        return sum/i;
    }
    return 0;
    

}

//===========================
//CLASS WORKER 
//=========================
class Worker : public Person{
private:
    string mCompanyName;
    string mJob;
    float mSalary;
    float mSeniority; //staż pracy

public:
    Worker(string companyName, string job, float salary, float seniority, string name, string lastname, float weight, float height, int age, sexVar sex)
            : mCompanyName(companyName), mJob(job), mSalary(salary), mSeniority(seniority), Person(name, lastname, weight, height, age, sex){
        
    }

    void calculateRemaining();

};

void Worker::calculateRemaining() {
    int womanYears = 60;
    int menYears = 65;
    int remaining = 0;
    if(mSex == K){
        if(womanYears >= Worker::getAge()){
            remaining = womanYears - Worker::getAge();
            cout<<" "<<remaining;
        }else
            cout<<"0"; //print 0 when remaining time exceeds years
    }else{
        if(menYears >= Worker::getAge()){
            remaining = menYears - Worker::getAge();
            cout<<" "<<remaining;
        }
        else
            cout<<"0";
    }
}


//===========================
//CLASS COURSE 
//=========================
class Course{
private:
    string mCourseName;
    Student** mStudentTab; //mStudentTab[5][10];
    int mStudentTotal;


public:
    Course(string name, int studentTotal=0)
            : mCourseName(name), mStudentTotal(studentTotal) {
        mStudentTab = new Student*[5];
        for(int i=0; i<10; i++){
            mStudentTab[i] = new Student[10];
        }
    }
    
    bool addStudent(Student *student);
    void updateStudentTotal();
    bool removeStudent(Student *student);
    void studentSort();
    void getTopStudents(int y);
    
    //refactor later, maybe use heap, heapsort or use vectors instead of arrays
};

bool Course::addStudent(Student *student){
    for(int i=0; i<10; i++){
        if(mStudentTab[student->getYear()][i].getIndex() == ""){
            mStudentTab[student->getYear()][i] = *student;
            return true; //loop escape
        }
        
    }
    return false;
}

void Course::updateStudentTotal(){
    mStudentTotal = 0;
    for(int y=0; y<5; y++){
        for(int i=0; i<10; i++){
            if(mStudentTab[y][i].getIndex() == ""){
                break;
            }
            mStudentTotal++;
        }
    }
}

bool Course::removeStudent(Student *student){
    int y = student->getYear(); //get current year
    for(int i=0; i<10; i++){
        if(mStudentTab[y][i].getIndex() == student->getIndex()){
            mStudentTab[y][i] = Student();
            int j = i;
            while(j<9){
                swap(mStudentTab[y][j],mStudentTab[y][j+1]);
                j++;
            }
            return true;
        }
    }
    
    return false;
}

void Course::studentSort(){
    for(int y=0; y<5; y++){
        bubbleSort(mStudentTab[y]); //sort students on every year
    }
}

void Course::getTopStudents(int y){
    studentSort();
    for(int i=0; i<3; i++){
        cout<<mStudentTab[y][i].getIndex()<<" "<<mStudentTab[y][i].getNameAndLastname();
        if(i<2){
            cout<<" ";
        }
    }
}

bool operator<=(Student studentOne,Student studentTwo){
    if(studentOne.calculateMean() <= studentTwo.calculateMean()) {
        return true;
    }
    return false;
}

// bool operator>(Student studentOne,Student studentTwo){
//     if(studentOne.calculateMean() > studentTwo.calculateMean()) {
//         return true;
//     }
//     return false;
// }


void bubbleSort(Student *tab){
    // int i, j;
    // bool swapped;
    // for (i = 0; i < 10; i++){
    // swapped = false;
    // for(j=0; j<9-i; j++){
    //     if(tab[j].getIndex()=="") return;
    //     if (tab[j].getIndex() > tab[j+1].getIndex()){
    //         swap(tab[j], tab[j+1]);
    //         swapped = true;
    //     }
    // }
    // if (swapped == false)
    //     break;
    // }
    
    for(int i = 0; i <9; i++){
        for(int j=i+1;j<10;j++){
            if(tab[j].getIndex()=="")
                return;
            if(tab[i]<=tab[j]){
                swap(tab[j],tab[i]);
            }
        }
    }
}

int main() {
    // double *grades = new double[10];
    
    // for(int i = 0; i < 5; i++)
    // {
    //     grades[i] = i+1;
    // }
    // cout<<endl;
    // for(int i=0; i<5; i++){
        
    //     cout<<grades[i]<<" ";
    // }
    
    
    // Student maniek("151686", 2, grades, "Maniek", "Mankowski", 80, 180, 21, M);
    // cout<<"BMI MANIEK: " << maniek.calcBMI() << endl;
    // maniek.dispPerson();
    
    // cout<<endl;
    // cout<<maniek.calculateMean();
    
    
    //creating a course
    string course;
    cin>>course;
    Course createdCourse(course);
    
    
    Student** studentsTab = new Student*[10];
    double **grades = new double*[10];
    
    //person
    string name, lastname;
    int age;
    char sex_char;
    sexVar sex;
    float weight, height;
    
    //student
    int year;
    string indexNum;
    
    //worker
    string companyName, job;
    float salary,seniority;
    
    //=====================================
    
    for(int i=0; i<10; i++){
        cin>>name>>lastname>>weight>>height>>age>>sex_char;
        if(sex_char == 'K'){
            sex = K;
        }
        else{
            sex = M;
        }
        
        cin>>indexNum>>year;
        grades[i] = new double[10];
        for(int j=0; j<5 ; j++){
            cin>>grades[i][j];
        }
        
        studentsTab[i] = new Student(indexNum, year, grades[i],name,lastname,weight, height, age, sex);
        createdCourse.addStudent(studentsTab[i]);
    }
    
    
    //==============================================
    //top3
    cin>>year;
    createdCourse.getTopStudents(year);
    
    //=================================================
    
    Worker** Workers = new Worker*[2];
    for(int i=0; i<2; i++){
        cin>>name>>lastname>>weight>>height>>age>>sex_char;
        if(sex_char == 'K'){
            sex = K;
        }
        else{
            sex = M;
        }
        cin>>companyName>>job>>salary>>seniority;
        Workers[i] = new Worker(companyName, job, salary, seniority, name, lastname, weight, height, age, sex);
    }
    
    Workers[0]->calculateRemaining();
    Workers[1]->calculateRemaining();
        


    return 0;
}


