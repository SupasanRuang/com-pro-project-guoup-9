#include<iostream>
using namespace std;

void start(){
    int select;
    bool done = true;
    
    while(done){
        cout << "--START--";
        cout << "1.Select table ( press 1 )\n" << "2.Check bill ( press 2 )\n" << "3.Edit menu ( press 3 )\n" << "4.Check daily balance ( press 4 )\n";
        cout << "5.Exit ( press 5 )\n";
        cin >> select;

        switch (select)
        {
            case 1:

                break;
            case 2:

                break;
            case 3:
                //edit_menu();
                break;
            case 4:
            
                break;
            case 5:
                done = false;
                break;    
            default:

                break;
        }
        
    }
    
}
int main(){
    start();
}