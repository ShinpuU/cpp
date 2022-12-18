#include <iostream>
#include <list>

using namespace std;
class Point{
    private:
        string mName;
        double mX;
        double mY;
    public:
        Point() = default;
        Point(string name, double x, double y) : mName(name), mX(x), mY(y){};
        
        //methods
        double getSum(){ return mX+mY; }
        double getX(){ return mX; }
        double getY(){ return mY; }
        string getName(){ return mName; }
};

//GLOBAL OVERLOADED OPERATORS

ostream& operator<<(ostream &s, Point point){
    return s << point.getName() << " " <<point.getX() << " " << point.getY()<<" ";
}

bool operator<(Point firstPoint, Point secondPoint){
    if(firstPoint.getSum() < secondPoint.getSum()){
        return true;
    }
    
    if(firstPoint.getSum() == secondPoint.getSum()){
        if(firstPoint.getX() < secondPoint.getX())
            return true;
            
        if(firstPoint.getX() == secondPoint.getX()){
            if(firstPoint.getName() < secondPoint.getName()){
                return true;
            }
            
            return false;
        }
        return false;
    }
    return false;
}

int main() {
    //1. stworzenie listy 
    std::list<Point> points;
    
    //2. domyslny iterator w std::list
    std::list<Point>::iterator it;
    
    //3. dlugosc tablicy
    int n;
    cin >> n;
    
    //4. Dodawanie do listy i sortowanie wedlug ustalonych kryteriow 
    string name;
    double x,y;
    for(int i=0 ; i<n; i++){
        cin>>name>>x>>y;
        Point newPoint(name,x,y);
        points.push_front(newPoint);
    }
    
    //sorting
    points.sort();
    
    //5. usun podany element
    double inputSum;
    bool isDeleted = false;
    cin >> inputSum;
    
    for(std::list<Point>::iterator it=points.begin(); it != points.end();){
        
        //cout<<endl<<"SUM: "<<sum<<endl;
        //cout<<endl<<"INPUT SUM: "<<inputSum<<endl;
        
        if(it->getSum() == inputSum && isDeleted == false){
            //cout<<endl<<it->getSum() <<endl;
            it = points.erase(it);
            //isDeleted = true;
        }
        else{
            ++it;
        }
    }
    
    //6. Wyswietlenie wszystkich elementow
    for(const auto& item : points){
        cout<<item;
    }
    
    return 0;
}
