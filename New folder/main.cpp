#include <iostream>
#include <stdlib.h> 
#include<iomanip>
#include "sqlite3.h"

using namespace std;

// Pointer to SQLite connection 
sqlite3* db; 

//prototype
void allmenu();     void showmenu();    void addmenu();     void deletemenu();      void edit_menu();
int callback(void *NotUsed, int argc, char **argv, char **azColName);

void start();   void select_table();
void checkbill();

int main() 
{ 
    sqlite3_stmt * stmt;    // Save the connection result
    int exit = 0;
    exit = sqlite3_open("database.db", &db); 
  
    // Test if there was an error
    if (exit) { 
        cout << "DB Open Error: " << sqlite3_errmsg(db) << endl; 
    } else {
        cout << "Opened Database Successfully!" << endl; 
    }

    //void start();
    void allmenu();
    
    sqlite3_close(db);// Close the connection
    return (0); 
} 

void allmenu(){

    sqlite3_stmt * stmt;
  
    sqlite3_prepare( db, "SELECT * FROM menu;", -1, &stmt, NULL );//preparing the statement

    const unsigned char* text;
    bool done = false;

    cout<<"---------------------------------------------------------\n\n";
    cout <<setw(10)<<right<<"Food ID"<<"\t"<<setw(15)<<left <<"Food Name"<<setw(10)<<right<<"Price"<<endl;
    while (!done) {
        switch (sqlite3_step(stmt)) {
            case SQLITE_ROW:
            for(int i=0; i<3;i++){
                text = sqlite3_column_text(stmt, i);
                if(i==1)
                {
                    cout <<"\t"<<setw(15)<<left; 
                } 
                else cout <<setw(10)<<right;
                cout <<text ;
            }
                break;
            
            case SQLITE_DONE:
                done = true;
                break;

            default:
                fprintf(stderr, "Failed.\n");
                return;
        }
        cout << endl;
    }
    cout<<"---------------------------------------------------------\n";

    sqlite3_finalize(stmt);

}

void showmenu(){
    sqlite3_stmt * stmt;
  
    int id;
    cin >> id;
    id -= 1;

    sqlite3_prepare( db, "SELECT * FROM menu;", -1, &stmt, NULL );//preparing the statement
    const unsigned char* text;
    
    for(int j=0;j<=id;j++){
        sqlite3_step(stmt);
        if(j==id){
            for(int i=0;i<3;i++){
                text = sqlite3_column_text(stmt,i);
                cout << text << " ";
            }
            break;
        }
    }
    sqlite3_finalize(stmt);
}

void addmenu(){
    sqlite3_stmt * stmt;
    
    string name,price;
    cout << "Input food name : ";
    cin >> name ;
    cout << "Input food price : ";
    cin >> price ;

    string sqlstatement = "INSERT INTO menu (food_name, price) VALUES ('" + name + "','" + price + "');";
    sqlite3_prepare( db, sqlstatement.c_str(), -1, &stmt, NULL );//preparing the statement
    sqlite3_exec(db, sqlstatement.c_str(), callback, 0, NULL);
    
}

void deletemenu(){
    string id;
    cout << "Input food ID : ";
    cin >> id;
    sqlite3_stmt * stmt;
    string sqlstatement = "DELETE FROM menu WHERE food_id = ('" + id + "');";
    sqlite3_prepare( db, sqlstatement.c_str(), -1, &stmt, NULL );//preparing the statement
    sqlite3_exec(db, sqlstatement.c_str(), callback, 0, NULL);
}

void edit_menu(){
    int select;
    cout << "what you want to edit\n"<<"1.Add menu ( press 1 )\n"<<"2.Delete menu ( press 2 )\n"<<"3.Go back ( press 3 )\n"<<"Input your choice : ";
    cin >> select;

    if(select == 1) addmenu();
    if(select == 2) deletemenu();
    if(select == 3) ;

}

int callback(void *NotUsed, int argc, char **argv, char **azColName){

    // int argc: holds the number of results
    // (array) azColName: holds each column returned
    // (array) argv: holds each value

    for(int i = 0; i < argc; i++) {
        
        // Show column name, value, and newline
        cout << azColName[i] << ": " << argv[i] << endl;
    
    }

    // Insert a newline
    cout << endl;

    // Return successful
    return 0;
}

void checkbill(){
    sqlite3_stmt * stmt;
  
    sqlite3_prepare( db, "SELECT * FROM menu;", -1, &stmt, NULL );//preparing the statement
}

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
                edit_menu();
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
//gcc sqlite3.c -c   ทำแบบนี้มันจะไม่ได้ exe แต่จะได้เป็น object file ที่ลิงค์เข้ากับโค้ดให้โปรแกรมเราไปเรียกใช้ตอน compile ครับ
//how to run (safe file first) ; g++ main.cpp sqlite3.o ; ./a.exe