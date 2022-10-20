#include<iostream>
using namespace std;

bool checkWinner(char board[][3], const int n=3){
    int counter = 0;
    
    for(int i = 0; i<n; i++){
        for(int j = 1; j<n; j++){
            if(board[i][j-1] == board[i][j]){
                counter++;
            }
        }
        if(counter == n-1){
            return true;
        }else{
            counter = 0;
        }
    }
    
    for(int i = 0; i<n; i++){
        for(int j = 1; j<n; j++){
            if(board[j-1][i] == board[j][i]){
                counter++;
            }
        }
        if(counter == n-1){
            return true;
        }else{
            counter = 0;
        }
    }
    
    for(int i = 1; i<n; i++){
        if(board[i-1][i-1]==board[i][i]){
            counter++;
        }
    }
    if(counter==n-1){
        return true;
    }else{
        counter = 0;
    }
    
    for(int i = n-1, j=0; i>0; i--){
        if(board[i][j]==board[i-1][j+1]){
            counter++;
        }
        j++;
    }
    if(counter==n-1){
        return true;
    }else{
        counter = 0;
    }
    
    return false;
    
}

bool inputCheck(char board[][3],int x, int y, int n=3){
    if((x<48||x>50) || (y<48||y>50)){
        return true;
    }
    if(board[x%48][y%48]=='o' || board[x%48][y%48]=='x'){
        return true;
    }

    return false;
}

bool checkDraw(char board[][3], int n=3){
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            if(board[i][j] != 'x' && board[i][j] != 'o'){
                return false;
            }
        }
    }
    return true;
}

 void printA(char array[][3]){
     for(int i=0; i<3; i++){
         for(int j=0; j<3; j++){
             cout<<array[i][j]<<" ";
         }
         cout<<endl;
     }
 }

int main() {
    char board[3][3] = {};
    
    char x,y;
    bool play = true;
    char player = 'o';
    printA(board);
    
    while(play){
        cin>>x>>y;
        int xi = static_cast<int>(x), yi = static_cast<int>(y);
        
        if(inputCheck(board,xi,yi)){
            continue;
        }
        
        board[xi%48][yi%48] = player;
        printA(board);
        
        if(checkWinner(board) && player=='o'){
            cout<<1;
            break;
        }else if(checkWinner(board) && player=='x'){
            cout<<-1;
            break;
        }
        
        if(checkDraw(board)){
            cout<<0;
            break;
        }
        
        if(player=='o'){
            player='x';
        }else{
            player='o';
        }
    }
    
    return 0;
}
