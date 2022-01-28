#include <iostream>
#include "sqlite3.h"

using namespace std;

// Pointer to SQLite connection 
sqlite3* db; 

//prototype
void allmenu();
void showmenu();
void addmenu();

int main() 
{ 
    sqlite3_stmt * stmt;
    
    // Save the connection result
    int exit = 0;
    exit = sqlite3_open("database.db", &db); 
  
    // Test if there was an error
    if (exit) { 
        
        cout << "DB Open Error: " << sqlite3_errmsg(db) << endl; 
        
    } else {

        cout << "Opened Database Successfully!" << endl; 
        sqlite3_prepare( db, "SELECT * FROM menu;", -1, &stmt, NULL );//preparing the statement
        sqlite3_step( stmt );//executing the statement
        char * str = (char *) sqlite3_column_text( stmt, 1 );///reading the 1st column of the result
        cout << str << endl;
    }
    //showmenu();
    //allmenu();
    addmenu();

    // push close button
    // Close the connection
    sqlite3_close(db);
    return (0); 
} 

void allmenu(){

    sqlite3_stmt * stmt;
  
    sqlite3_prepare( db, "SELECT * FROM menu;", -1, &stmt, NULL );//preparing the statement

    const unsigned char* text;
    bool done = false;
    while (!done) {
        switch (sqlite3_step(stmt)) {
            case SQLITE_ROW:
            for(int i=0; i<3;i++){
                text = sqlite3_column_text(stmt, i);
                cout << text ;
            }
                break;
            

            case SQLITE_DONE:
                done = true;
                break;

            default:
                fprintf(stderr, "Failed.\n");
                return;
        }
    }

    sqlite3_finalize(stmt);

}

void showmenu(){
    sqlite3_stmt * stmt;
  
    int id=0;

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
  
    sqlite3_prepare( db, "SELECT * FROM menu;", -1, &stmt, NULL );//preparing the statement
    string name,price;

    cin >> name >> price;

    //string sqlstatement = "INSERT INTO menu (food_name, price) VALUES (name, price)";
    string sqlstatement = "INSERT INTO menu (food_name, price) VALUES ('" + name + "','" + price + "');";
    
}
//gcc sqlite3.c -c   ทำแบบนี้มันจะไม่ได้ exe แต่จะได้เป็น object file ที่ลิงค์เข้ากับโค้ดให้โปรแกรมเราไปเรียกใช้ตอน compile ครับ
//how to run (safe file first) ; g++ main.cpp sqlite3.o  && ./a.exe