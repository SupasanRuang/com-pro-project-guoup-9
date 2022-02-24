#include <iostream>
#include <stdlib.h> 
#include<iomanip>
#include<string>
#include<vector>
#include <ctime>
#include "sqlite3.h"

using namespace std;

// Pointer to SQLite connection 
sqlite3* db; 

struct menubook
{
    int id ;
    string name;
    int price;

};

struct  table_order
{
    int food_id;
    int order;
    
};

struct daily_income
{
    string date;
    int income;
};

char table[9] = {'1','2','3','4','5','6','7','8','9'};
vector<table_order> table1,table2,table3,table4,table5,table6,table7,table8,table9;
vector<daily_income> daily;
vector<menubook> book;

//prototype
void allmenu();     void showmenu(int);    void addmenu();     void deletemenu();      
void edit_menu();
int callback(void *NotUsed, int argc, char **argv, char **azColName);

void number_table_order(int); void loop_order(vector<table_order> &table);

void start();   void select_table();
void select_checkbill(); void delete_old_daily();

void push_menubook(vector<menubook> &book);                     
void printmenubook(vector<menubook> &book);
void vec_addorder(vector<table_order> &note , int id, int num);
void add_table_order(vector<table_order> &thetable);
bool vec_cancelorder(vector<table_order> &note ,int id,int num);
void cancel_table_order(vector<table_order> &thetable);
int find_id(vector<menubook> book ,int id);  
int find_id_in_order (vector<table_order> thetable ,int id);                   
int find_name(vector<menubook> book ,string name);
void add_daily_income(vector<daily_income> &daily,int income);
void show_bill(vector<table_order> &note ,vector<menubook> book);
int check_bill(vector<table_order> &note ,vector<menubook> book);
void show_table_order(vector<table_order> thetable,vector<menubook> book);
vector<table_order>* which_table(int number);
void update_menubook(vector<menubook> &book);
void table_bill(vector<daily_income> &daily);
void print_daily_income(vector<daily_income> daily);
void push_daily_income(vector<daily_income> &daily);
void pull_daily_income(vector<daily_income> &daily);
string datenow();

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
    
    pull_daily_income(daily);
    push_menubook(book); 
    printmenubook(book);
    start();


    push_daily_income(daily);
    daily.clear();
    sqlite3_close(db);// Close the connection
    return (0); 
} 

void start(){
    int select;
    bool done = true;
    
    while(done){
        cout <<setw(56) << "_______________________________________________" <<endl;
        cout <<setw(10)<<"|"<<setw(26) <<"--START--"<<setw(20) << "|" <<endl;
        cout <<setw(10)<<"|"<<"  1.Select table ( press 1 )" <<setw(18)  <<"|" <<endl;
        cout <<setw(10)<<"|"<<"  2.Add menu for selected table ( press 2 )"<< setw(3) <<"|"<<setw(40)<<" ____________________________"<<endl;
        cout <<setw(10)<<"|"<<"  3.Check bill ( press 3 )"<<setw(20) <<"|"<<setw(40)<<" | what would you choose ?  |"<<endl ;
        cout <<setw(10)<<"|"<<"  4.Edit menu ( press 4 )" <<setw(21) <<"|"<<setw(40)<<" |__________________________|"<<endl;
        cout <<setw(10)<<"|"<<"  5.Check daily balance ( press 5 )"<<setw(11) <<"|"<<setw(10)<<" ("<<"\\"<<"______/)  "<<"|"<<"|"<<endl;
        cout <<setw(10)<<"|"<<"  6.Exit ( press 6 )"<<setw(26)  << "|"<<setw(23)<<"(  O w O  ) ||" << endl;
        cout <<setw(56)<< "|_____________________________________________|"<<setw(37)<<"/         >   SELECT HERE : ";
        //cout <<setw(60)<<"\t" <<"  What would you choose ? : ";
        cin >> select;
        cout<<endl;


        switch (select)
        {
            case 1:
                select_table();
                break;
            case 2:
                number_table_order(0);
                break;
            case 3:
                table_bill(daily);
                break;
            case 4:
                edit_menu();
                break;
            case 5:
                print_daily_income(daily);
                break; 
            case 6:
                done = false;
                cout<<setw(108)<<"-------------------------------------------------------------------------------------------------------------\n\n";
                cout<<setw(63)<<"                ()_()    "<<endl;
                cout<<setw(59)<<"                /   \\"<<endl;
                cout<<setw(62)<<"               ( 'v' )  "<<endl;
                cout<<setw(60)<<"               <(___)>"<<endl;       
                cout<<setw(61)<<"               _''_''_ "<<endl;
                cout << "\t\t\t\t\t        mmmm         mmmm            \n";
	            cout << "\t\t\t\t\t       E    3mmmmmmmE    3           \n";
	            cout << "\t\t\t\t\t        E               3            \n";
	            cout << "\t\t\t\t\t        E   X       X   3            \n";
	            cout << "\t\t\t\t\t        E       W       3            \n";
	            cout << "\t\t\t\t\t  mmm   E               3   mmm      \n";
	            cout << "\t\t\t\t\t m   m  E               3  m   m     \n";
	            cout << "                  TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT\n";
	            cout << "                  [[   ITT]  I\\  T  [TTTD   TTTP  IRRR   [TTT]  ITTTT]  IRRR     III   [\\  /]   ]]\n";
	            cout << "                  [[   I--   I \\ |  [    D  I__P  I___R  [   ]  I --    I___R   I---I  I \\/ I   ]]\n";
	            cout << "                  [[   I__]  I  \\|  I___D   I     I    R [___]  I___]   I    R  I   I  I    I   ]]\n";
	            cout << "                  LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL\n";
                cout<<setw(108)<<"-------------------------------------------------------------------------------------------------------------\n\n";
                break;
            default:
                cout<<setw(108)<<"--------------------------------------------------------------------------------------------------------\n";
                cout<<setw(59)<< "Error!!!\n";
                cout<<setw(60)<<"Select again"<<endl;
                cout<<setw(108)<<"--------------------------------------------------------------------------------------------------------\n";
                break;
        }
        
    }
    
}

void select_table(){
    
    int sl_table,count=0;
    cout<<setw(109)<<"--------------------------------------------------------------------------------------------------------\n\n";
    for(int j=0 ; j<9;j++){
        if(j%3 == 0){
            cout << setw(73) << table[j];
        }else{
            cout<<setw(8) << table[j];
        }
        if((j+1)%3 == 0 && j != 0){
            if((j+1) == 9){
                cout << "\n";
            }else{
                cout << "\n\n\n";
            }
        }
        if(table[j]=='-')
        {
            count++;
        }
    }
    cout << endl;
    if(count==9)
    {
        cout<<setw(108)<<"---------------------------------------------------\n";
        cout<<setw(93)<<"Sorry all table are used." <<"\n";
        cout<<setw(91)<<"Please wait it empty." << endl;
        cout<<setw(108)<<"--------------------------------------------------------------------------------------------------------\n";
        return;
    }
    while(true)
    {
        cout << "                      ______"<<endl;
        cout << "                     /  .  ."<<"\\"<<"___"<<endl;
        cout << "                    /        '  "<<"\\"<<endl;
        cout << "                    "<<"\\"<<"   ______V_/"<<endl;
        cout << "       _______/--"<<"\\"<<"___|___|____/--"<<"\\"<<"_______"<<endl;
        cout << "              "<<"\\"<<",,/            "<<"\\"<<",,/";
        cout<<setw(70)<< "INPUT THE TABLE YOU WANT TO SELECT ( exit input [0] ): ";
        cin >> sl_table;
        cout << "\n";
        if(sl_table == 0){
            cout<<endl;
            cout<<setw(108)<<"--------------------------------------------------------------------------------------------------------\n";
            return; // out of select table
        }
        if (sl_table<1||sl_table>9)
        {
            cout<<setw(108)<<"---------------------------------------------------\n";
            cout<<setw(93)<<"Don't have this table\n";
            cout<<setw(108)<<"---------------------------------------------------\n";
            continue;
        }
        
        if(table[sl_table-1]!='-')
        {
           break; 
        }
        else 
        {
            cout<<setw(108)<<"---------------------------------------------------\n";
            cout<<setw(93)<<"Sorry this table is used."<<endl;
            cout<<setw(95)<< "Please select table again. ^^" << endl;
            cout<<setw(108)<<"---------------------------------------------------\n";
            continue;
        }
    }
    
    table[sl_table-1] = '-';
    cout <<endl;
    for(int j=0 ; j<9;j++){
        if(j%3 == 0){
            cout << setw(73) << table[j];
        }else{
            cout<<setw(8) << table[j];
        }
        if((j+1)%3 == 0 && j != 0){
            if((j+1) == 9){
                cout << "\n\n";
            }else{
                cout << "\n\n\n";
            }
        }
    }
    cout<<setw(108)<<"--------------------------------------------------------------------------------------------------------\n";
    number_table_order(sl_table);
}

void select_checkbill(){
    int sl_table;
    cout << "input num : ";
    cin >> sl_table;

    table[sl_table-1] = '-';
    for(int j=0 ; j<9;j++){
        cout << table[j] << " ";
    }
    cout <<endl;
}

void loop_order(vector<table_order> &thetable){
    int num;
    while (true)
    {
        //cout<<setw(109)<<"--------------------------------------------------------------------------------------------------------\n\n";
        cout<<setw(48)<<"______________________________"<<endl;
        cout<<setw(19)<<"|"<<setw(29)<<"|"<<endl;
        cout<<setw(19)<<"|"<<setw(23)<< "SELECT THESE CHOICE"<<setw(6)<<"|"<<"\n";
        cout<<setw(19)<<"|"<<setw(29)<<"|"<<setw(4)<<" "<<"   __,,,__"<<endl;
        cout<<setw(19)<<"|"<<setw(18)<< "[1] Add Order"<<setw(11)<<"|"<<setw(4)<<" "<<"(d  .   . b)    ====================="<<endl;
        cout<<setw(19)<<"|"<<setw(21)<<"[2] Cancel Order"<<setw(8)<<"|"<<setw(4)<<" "<<"  (  (Y)  )   << INPUT YOUR CHOICE ||"<<endl;
        cout<<setw(19)<<"|"<<setw(14)<<"[3] Exit "<<setw(15)<<"|"<<setw(4)<<" "<<"  |>     |>     ====================="<<endl;
        cout<<setw(48)<<"|____________________________|"<<setw(4)<<" "<<"\\"<<"_(''')_(''')";
        cout<<"    HERE : ";
        cin >> num;
        cout <<endl;
        //cout<<setw(108)<<"--------------------------------------------------------------------------------------------------------\n";
        switch (num)
        {
            case 1 :
               // cout<<"[1] Add Order Process"<<endl; //เอาอยู่บ่?
                add_table_order(thetable);
                break;

            case 2 :
                //cout<<"[2] Cancel Order Process"<<endl;
                cout<<endl;
                cout<<setw(108)<<"--------------------------------------------------------------------------------------------------------\n";
                cancel_table_order(thetable);
                break;

            case 3 :
                //cout<<"[3] Exit Order Food Process"<<endl;
                cout<<endl;
                cout<<setw(108)<<"--------------------------------------------------------------------------------------------------------\n";
                return ;
                break;
    
            default:
                cout<<"\n";
                cout<<setw(108)<<"---------------------------------------------------\n";
                cout<<setw(91)<< "Error Select again!!"<<endl;
                cout<<setw(108)<<"---------------------------------------------------\n";
                //cout<<setw(63)<<"---------------------------------------------------------\n";

                break;
        }
    }
    return ;
}

void show_table_order(vector<table_order> thetable,vector<menubook> book)
{
    cout<<"\n";
    cout<<setw(100)<<"_________________________________________\n";
    cout<<setw(59)<<"|"<<setw(41)<<"|\n";
    cout<<setw(59)<<"|"<<setw(24)<<"YOUR ORDER"<<setw(17)<<"|\n";
    cout<<setw(100)<<"|_______________________________________|\n";
    cout<<setw(59)<<"|"<<setw(41)<<"|\n";
    cout<<setw(59)<<"|" <<setw(8)<<right<<"Food ID"<<"\t"<<setw(15)<<left <<"Food Name"<<setw(10)<<right<<"Quantity"<<setw(2)<<"|"<<endl;
    for (unsigned int i = 0; i < thetable.size(); i++)
    {
        cout <<setw(59)<<"|"<<" "<<thetable[i].food_id;
        int k= find_id(book,thetable[i].food_id);
        cout <<"\t\t"<<setw(15)<<left<<book[k].name; 
        cout <<setw(10)<<right<<thetable[i].order<<" |"<<endl;
    }
    cout<<setw(100)<<"|_______________________________________|\n";
    //cout << endl;
    //cout<<setw(63)<<"---------------------------------------------------------\n";
}

void number_table_order(int tb_num=0){ //รับค่า selecttable;
    int sl_table,count=0;
    if(tb_num==0) //ADD ORDER BEFORE SELECT
    {
        cout<<setw(109)<<"--------------------------------------------------------------------------------------------------------\n\n";
        for(int j=0 ; j<9;j++){
            if(j%3 == 0){
                cout << setw(73) << table[j];
            }else{
                cout<<setw(8) << table[j];
            }
            if((j+1)%3 == 0 && j != 0){
                if((j+1) == 9){
                cout << "\n";
                }else{
                cout << "\n\n\n";
                }
            }
            if(table[j]!='-')
            {
            count++;
            }

        }
        cout << endl;
        if(count==9)
        {
            cout<<setw(108)<<"---------------------------------------------------\n";
            cout<<setw(93)<<"Sorry all table are used." <<"\n"; // maybe [please select table first] //กด add ก่อน select
            cout<<setw(91)<<"Please wait it empty." << endl;
            cout<<setw(108)<<"--------------------------------------------------------------------------------------------------------\n";
            return;
        }
        while(true) //มาทำหลังแก้ loop
        {
            //cout<<setw(63)<<"---------------------------------------------------------\n";
            cout<<setw(5)<<" "<<" _______"<<endl;
            cout<<setw(5)<<" "<<" [ @ @ ]"<<endl;
            cout<<setw(5)<<" "<<"/"<<"|_____|"<<"\\"<<endl;
            cout<<setw(5)<<" "<<"  d   b";
            cout <<"    input table want to Order Menu : "; 
            cin >> sl_table;
            if (sl_table<1||sl_table>9)
            {
                cout<<setw(108)<<"---------------------------------------------------\n";
                cout<<setw(93)<<"Don't have this table\n";
                cout<<setw(108)<<"---------------------------------------------------\n";
                continue;
            }
        
            if(table[sl_table-1]=='-')
            {
                cout<<endl;
                cout<<setw(108)<<"--------------------------------------------------------------------------------------------------------\n";
                break; 
            }
            else 
            {
                cout<<setw(108)<<"---------------------------------------------------\n";
                cout<<setw(95)<<"Sorry this table is empty."<<endl;
                cout<<setw(95)<<"Please select table again." << endl;
                cout<<setw(108)<<"---------------------------------------------------\n";
                //cout<<setw(63)<<"---------------------------------------------------------\n";
                continue;
            }
        }
    }
    else
    {
        sl_table=tb_num;
    }
    vector<table_order>* vec_point;
    vec_point=which_table(sl_table);
    if(vec_point==NULL)
    {
        cout<<setw(63)<<"---------------------------------------------------------\n";
        cout<<"Error table" << endl;//how to access
        cout<<setw(63)<<"---------------------------------------------------------\n";

        return;
    }
    loop_order(*vec_point);
    return;
}

vector<table_order>* which_table(int number)
{
    switch (number)
    {
    case 1:
        return &table1;
        break;
    case 2:
        return &table2;
        break;
    case 3:
        return &table3;
        break;
    case 4:
        return &table4;
        break;
    case 5:
        return &table5;
        break;
    case 6:
        return &table6;
        break;
    case 7:
        return &table7;
        break;
    case 8:
        return &table8;
        break;
    case 9:
        return &table9;
        break;
    default:
        return NULL;
        break;
    }     
}

void allmenu(){ //have question;

    sqlite3_stmt * stmt;
  
    sqlite3_prepare( db, "SELECT * FROM menu;", -1, &stmt, NULL );//preparing the statement

    const unsigned char* text;
    bool done = false;

    cout<<"\n";
    cout<<setw(108)<<"--------------------------------------------------------------------------------------------------------\n";
    cout<<setw(44)<<"_____________________________________\n";
    cout<<setw(7)<<"|"<<setw(37)<<"|\n";
    cout<<setw(7)<<"|"<<setw(22)<<"-ALLMENU-"<<setw(15)<<"|\n";
    cout<<setw(44)<<"|___________________________________|\n";
    cout<<setw(7)<<"|"<<setw(37)<<"|\n";
    //cout<<"---------------------------------------------------------" << "\n\n";
    cout<<setw(7)<<"|" <<setw(8)<<right<<"Food ID"<<"\t"<<setw(15)<<left <<"Food Name"<<setw(10)<<right<<"Price"<<setw(2)<<"|"<<endl;
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
                cout<<text ;
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
    cout<<setw(56)<<"---------------------------------------------------\n";

    sqlite3_finalize(stmt);

}

void showmenu(int id){
    sqlite3_stmt * stmt;

    string str_id = to_string(id);
    string text2 = "SELECT * FROM menu WHERE food_id = " + str_id + " ;" ;

    sqlite3_prepare( db, text2.c_str(), -1, &stmt, NULL );//preparing the statement
    const unsigned char* text;
    sqlite3_step(stmt);
            for(int i=0;i<3;i++){
                text = sqlite3_column_text(stmt,i);
                cout << text << " ";
            }
    sqlite3_finalize(stmt);
}

void addmenu(){
    sqlite3_stmt * stmt;
    
    string name,price;
    cout<<setw(56)<<"             ___  "<<endl;
    cout<<setw(57)<<"            /. .\\__"<<endl;
    cout<<setw(58)<<"           /      _\\"<<endl;
    cout<<setw(63)<<"      __   \\  _____/   __"<<endl;
    cout<<setw(70)<<"  ___/__\\__|___|______/__\\______"<<setw(30) << "Input food name : ";
    cin.ignore();
    getline(cin,name);
    cout<<setw(56)<<"             ___  "<<endl;
    cout<<setw(57)<<"            /. .\\__"<<endl;
    cout<<setw(58)<<"           /      o\\"<<endl;
    cout<<setw(63)<<"      __   \\  _____/   __"<<endl;
    cout<<setw(70)<<"  ___/__\\__|___|______/__\\______"<<setw(30)<< "Input food price : ";
    cin >> price ;

    string sqlstatement = "INSERT INTO menu (food_name, price) VALUES ('" + name + "','" + price + "');";
    sqlite3_prepare( db, sqlstatement.c_str(), -1, &stmt, NULL );//preparing the statement
    sqlite3_exec(db, sqlstatement.c_str(), callback, 0, NULL);
    update_menubook(book);
    
}

void deletemenu(){
     cout<<setw(100)<<"_________________________________________\n";
    cout<<setw(59)<<"|"<<setw(41)<<"|\n";
    cout<<setw(59)<<"|"<<setw(24)<<"MENU BOOK"<<setw(17)<<"|\n";
    cout<<setw(100)<<"|_______________________________________|\n";
    cout<<setw(59)<<"|"<<setw(41)<<"|\n";
    cout<<setw(59)<<"|" <<setw(8)<<right<<"Food ID"<<"\t"<<setw(15)<<left <<"Food Name"<<setw(10)<<right<<"Price"<<setw(2)<<"|"<<endl;
    for (unsigned int i = 0; i < book.size(); i++)
    {
        cout<<setw(59)<<"|"<<" "<<book[i].id;
        cout <<"\t\t"<<setw(15)<<left<<book[i].name; 
        cout <<setw(10)<<right<<book[i].price<<setw(2)<<"|"<<endl;

    }
    cout<<setw(100)<<"|_______________________________________|\n";
    bool no_empty= false;
    for (int i = 0; i < 9; i++)
    {
        if(table[i]=='-')
        {
            no_empty=true;
            break ;
        }
    }
    if(no_empty)
    {
    cout <<endl;
    for(int j=0 ; j<9;j++){
        if(j%3 == 0){
            cout << setw(73) << table[j];
        }else{
            cout<<setw(8) << table[j];
        }
        if((j+1)%3 == 0 && j != 0){
            if((j+1) == 9){
                cout << "\n\n";
            }else{
                cout << "\n\n\n";
            }
        }
    }
    cout<<setw(10)<<"                                                            -------------------------------------------------"<<endl;
    cout<<setw(10)<<"                                                            | These are used table. Wait all table are empty | "<<endl; 
    cout<<setw(10)<<"                                                            -------------------------------------------------\n"<<endl;
        return ;
    }
    string id;
    cout<<"\n";
    cout<<setw(57)<<"      _____"<<endl;
    cout<<setw(60)<<"___   / . . \\__"<<endl;
    cout<<setw(60)<<"/   \\  \\/      V"<<endl;
    cout<<setw(70)<<"_/_____\\_|_______/__________"<<setw(25)<< "Input food ID : ";
    cin >> id;
    cout<<setw(120)<<"------------------------------------------------------------------------------------------------------------\n"<<endl;
    sqlite3_stmt * stmt;
    string sqlstatement = "DELETE FROM menu WHERE food_id = ('" + id + "');";
    sqlite3_prepare( db, sqlstatement.c_str(), -1, &stmt, NULL );//preparing the statement
    sqlite3_exec(db, sqlstatement.c_str(), callback, 0, NULL);
    update_menubook(book);
   
}

void edit_menu(){
    int select;
    bool done=true;
    while(done){
        cout<<setw(120)<<"-----------------------------------------------------------------------------------------------------------------------\n"<<endl;
        cout<<setw(44)<<"___________________________________"<<endl;
        cout<<setw(10)<<"|"<<  "     What you want to edit     "<<setw(3)<<"|"<<setw(43)<<"("<<"\\"<<"_____/)"<<endl;
        cout<<setw(10)<<"|"<<"     1.Add menu ( press 1 )"<<setw(7)<<"|"<<setw(51)<<"(> *v* <)"<<endl; //Add menu in database
        cout<<setw(10)<<"|"<<"     2.Delete menu ( press 2 )"<<setw(4)<<"|"<<setw(51)<<"    /   .   \\"<<endl; // Delete menu in database
        cout<<setw(10)<<"|"<<"     3.Show menu ( press 3 )"<<setw(6)<<"|"<<setw(52)<<"('')___('')"<<endl;  //Show menu in book
        cout<<setw(10)<<"|"<<"     4.Go back ( press 4 )"<<setw(8)<<"|"<<endl;
        cout<<setw(44)<<"|_________________________________|"<<setw(48)<<"<------------Input your choice :    ";
        cin >> select;
        cout<<"\n\n";
        cout<<setw(120)<<"-----------------------------------------------------------------------------------------------------------------------\n"<<endl;
         

        switch (select)
            {
                case 1:
                    addmenu();
                    break;
                case 2:
                    deletemenu();
                    break;
                case 3:
                    printmenubook(book);
                    break;
                case 4:
                    done = false;
                    break;
                default:
                    cout<<setw(108)<<"---------------------------------------------\n";
                    cout<<setw(93)<< "Error Select again"<<endl;
                    cout<<setw(108)<<"---------------------------------------------\n";
                    break;
            }
    }


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

void add_table_order(vector<table_order> &thetable)
{
    printmenubook(book);
    //allmenu(); //ใช้ปริ้นMenuแทนได้ไหม;
    int id,num,want;
    while(true){
        //cout<<setw(63)<<"---------------------------------------------------------\n";
        cout<<setw(7)<<" "<<"              ______"<<endl;
        cout<<setw(7)<<" "<<"             C  '  ' "<<"\\"<<endl;
        cout<<setw(7)<<" "<<"             |     00 "<<"\\"<<endl;
        cout<<setw(7)<<" "<<"_______/--"<<"\\"<<"__|________/____/--"<<"\\"<<"_______"<<endl;
        cout<<setw(7)<<" "<<"       "<<"\\"<<"__/                "<<"\\"<<"__"<<"/";
        cout<< "          INPUT ORDER MENU [ID] TO ADD (If want to exit input 0) : "; // can use 03,04,0..
        cin >> id;
        if(id == 0){
            cout<<"\n";
            cout<<setw(108)<<"--------------------------------------------------------------------------------------------------------\n";
            break;
        } 
        int x=find_id(book,id);
        //cout<<x<<endl;
        if(x==-1)
        {
            cout <<"\n";
            cout<<setw(108)<<"---------------------------------------------------\n";
            cout<<setw(98)<<"Don't have this ID in Menubook\n";
            cout<<setw(108)<<"---------------------------------------------------\n";
            //cout<<setw(63)<<"---------------------------------------------------------\n";
            continue;
        }
        cout <<setw(80)<< "INPUT [QUANTITY] ORDER TO ADD : ";
        cin >> num;
        if(num>0)
        {
            vec_addorder(thetable,id,num);
            show_table_order(thetable,book);
        }
        else 
        {
            cout<<"\n";
            cout<<setw(108)<<"---------------------------------------------------\n";
            cout<<setw(98) << "Input quantity order Error!! \n";
            cout<<setw(108)<<"---------------------------------------------------\n";
        }       
    }
    return ;

}

void cancel_table_order(vector<table_order> &thetable )
{
    int id,num,quantity;
    if(thetable.size()==0)
    {
        cout<<"\n";
        cout<<setw(108)<<"---------------------------------------------------\n";
        cout<<setw(91)<<"The Order is empty"<<endl;
        cout<<setw(108)<<"---------------------------------------------------\n";
       //cout<<setw(63)<<"---------------------------------------------------------\n";
        return;
    }
    show_table_order(thetable,book);
    while(true){
        bool done=true;
        cout<<setw(7)<<" "<<"                      _____"<<endl;
        cout<<setw(7)<<" "<<"          ___  ___  /  ' ' "<<"\\"<<"__"<<endl;
        cout<<setw(7)<<" "<<"        /    "<<"\\"<<"    "<<"\\"<<" "<<"\\"<<"/        V"<<endl;
        cout<<setw(7)<<" "<<"_______/______"<<"\\"<<"____"<<"\\"<<"|_______^/_______";
        //cout<<setw(63)<<"---------------------------------------------------------\n";
        cout<< "    INPUT ORDER MENU [ID] TO CANCEL(If want to exit input 0) : ";
        cin >> id;
        if(id == 0) 
        {
            cout<<"\n";
            cout<<setw(108)<<"--------------------------------------------------------------------------------------------------------\n";
            break;
        }
        int x = find_id_in_order (thetable,id);
        //cout<<x<<endl;
        if(x==-1)
        {
            cout<<"\n";
            cout<<setw(108)<<"---------------------------------------------------\n";
            cout<<setw(96)<<"Don't have this ID in Order\n";
            cout<<setw(108)<<"---------------------------------------------------\n";
            //cout<<setw(63)<<"---------------------------------------------------------\n";
            continue;
        }
        else if(thetable[x].order==0)
        {
            cout<<"\n";
            cout<<setw(108)<<"---------------------------------------------------\n";
            cout<<setw(96)<<"Don't have this ID in Order\n";
            cout<<setw(108)<<"---------------------------------------------------\n";
            //cout<<setw(63)<<"---------------------------------------------------------\n";
            continue;
        }

        quantity = thetable[x].order;
        cout<<"\n"<<endl;
        cout<<setw(7)<<" "<<"                      _____"<<endl;
        cout<<setw(7)<<" "<<"          ___  ___  /  o o "<<"\\"<<"__"<<endl;
        cout<<setw(7)<<" "<<"        /    "<<"\\"<<"    "<<"\\"<<" "<<"\\"<<"/        O"<<endl;
        cout<<setw(7)<<" "<<"_____\\/______"<<"\\"<<"____"<<"\\"<<"|_______V/_______";
        cout<<setw(25) <<"     INPUT QUANTITY ORDER TO CANCEL "<<"[ 1 ~ "<<quantity<<" ] : ";
        cin >> num;
        if(num<=quantity&&quantity!=0&&num>0)
        {
            done=vec_cancelorder(thetable,id,num);//>>how to access;
            show_table_order(thetable,book);
        }
        else 
        {
            cout<<endl;
            cout<<setw(108)<<"---------------------------------------------------\n";
            cout<<setw(96)<< "Input quantity order Error \n";
            cout<<setw(108)<<"---------------------------------------------------\n";
            
        }
        if(done==false)
        {
            cout<<setw(108)<<"---------------------------------------------------\n";
            cout<<setw(96)<< "Cancelorder order Error!! \n";//how to access
            cout<<setw(108)<<"---------------------------------------------------\n";
        } 

    }
    return ;
}

bool vec_cancelorder(vector<table_order> &note ,int id,int num)
{
    bool having=true;

    for(unsigned int i=0 ;i<note.size();i++)
    {
        if(note[i].food_id==id)
        {
            note[i].order-=num;
            if(note[i].order==0)
            {
               note.erase(note.begin()+i); 
            }
            return true;
        }
    }
    return false;

}

void vec_addorder(vector<table_order> &note , int id, int num)
{
    
    bool having=true;
    for(unsigned int i=0 ;i<note.size();i++)
    {
        if(note[i].food_id==id)
        {
            having=false;
            note[i].order+=num;
            return;
        }
    }
    if(having)
    {
        table_order temp={id,num};
        note.push_back(temp);
    }
}

int find_id_in_order (vector<table_order> thetable ,int id)
{
    for(unsigned int i=0 ;i<thetable.size();i++)
    {
        if(thetable[i].food_id==id)
        {
            return i;    
        }
    }
    return -1;

}

int find_id(vector<menubook> book ,int id)
{
    for(unsigned int i=0 ;i<book.size();i++)
    {
        if(book[i].id==id)
        {
            return i;    
        }
    }
    return -1;

}

int find_name(vector<menubook> book ,string name)
{
    for(unsigned int i=0 ;i<book.size();i++)
    {
        if(book[i].name==name)
        {
            return i;    
        }
    }
    return -1;
}

string datenow()
{
    time_t now = time(0);
    tm *ltm = localtime(&now);
    string year=to_string(1900 + ltm->tm_year);
    string month=to_string(1 + ltm->tm_mon);
    string day=to_string(ltm->tm_mday);
    string date=year+"-"+month+"-"+day;
    return date;

}

void add_daily_income(vector<daily_income> &daily,int income)
{   
     string date = datenow();
    for(unsigned int i=0 ;i<daily.size();i++)
    {
        if(daily[i].date==date)
        {
           daily[i].income+=income;
           return ;
        }
    }
        daily_income temp={date,income};
        daily.push_back(temp);
}

void show_bill(vector<table_order> &note ,vector<menubook> book)
{
    double sum=0;
    cout<<"\n";
    cout<<setw(88)<<"____________________________________________________________\n";
    cout<<setw(28)<<"|"<<setw(59)<<"|"<<endl;
    cout<<setw(28)<<"|"<<setw(36)<<"YOUR RECEIPT"<<setw(23)<<"|"<<endl; 
    cout<<setw(28)<<"|"<<setw(39)<<"------------------"<<setw(20)<<"|"<<endl;
    cout<<setw(28)<<"|"<<setw(59)<<"|"<<endl;
    cout<<setw(28)<<"|"<<setw(59)<<"|"<<endl;
    cout<<setw(28)<<"|"<<setw(59)<<"|"<<endl;
    cout <<setw(28)<<"|"<<setw(4)<<right<<" Food ID"<<"\t"<<setw(15)<<left <<"Food Name"<<setw(7)<<right<<"Price";
    cout <<setw(13)<<right<<"Quantity"<<setw(10)<<right<<"Total"<<setw(2)<<"|"<<endl;
    for(unsigned int i=0 ;i<note.size();i++)
    {
        int j=find_id(book,note[i].food_id);
        cout <<setw(28)<<"|"<<setw(4)<<right<<book[j].id<<"\t"<<setw(15)<<left <<book[j].name<<setw(7)<<right<<book[j].price;
        cout <<setw(13)<<right<<note[i].order<<setw(10)<<right<<note[i].order*book[j].price<<setw(2)<<"|"<<endl;
        sum+=note[i].order*book[j].price;
    }
    cout<<setw(28)<<"|"<<setw(59)<<"|"<<endl;
    cout<<setw(28)<<"|"<<setw(59)<<"|"<<endl;
    cout <<setw(28)<<"|"<<setw(4)<<right<<" "<<"\t"<<setw(15)<<left <<"SUM"<<setw(30)<<right<<sum <<setw(2)<<"|"<<endl;
    cout<<setw(28)<<"|"<<setw(59)<<"|"<<endl;
    cout<<setw(28)<<"|"<<setw(59)<<"|"<<endl;
    cout<<setw(28)<<"|"<<setw(35)<<"VAT INCLUDE"<<setw(24)<<"|"<<endl; // VAT INCLUDE
    cout<<setw(28)<<"|"<<setw(46)<<"THANK YOU FOR USING OUR SERVICE!"<<setw(13)<<"|"<<endl; // THANK YOU FOR USING OUR SERVICE
    cout<<setw(28)<<"|"<<setw(59)<<"|"<<endl;
    cout<<setw(28)<<"|"<<setw(59)<<"|"<<endl;
    cout<<setw(89)<<"|__________________________________________________________|\n\n";
    cout<<setw(108)<<"--------------------------------------------------------------------------------------------------------\n";
    return;
}

int check_bill (vector<table_order> &note ,vector<menubook> book)
{
    double sum=0;
    for(unsigned int i=0 ;i<note.size();i++)
    {
        int j=find_id(book,note[i].food_id);
        sum+=note[i].order*book[j].price;
    }
    return sum;
}

void table_bill(vector<daily_income> &daily)
{
    int number ,count=0 ;
    vector<table_order> *vec_point; 
    vec_point = which_table(number);
    cout<<setw(109)<<"--------------------------------------------------------------------------------------------------------\n\n";
    for(int j=0 ; j<9;j++){
        if(j%3 == 0){
            cout << setw(50) << table[j];
        }else{
            cout<<setw(8) << table[j];
        }
        if((j+1)%3 == 0 && j != 0){
            if((j+1) == 9){
                cout << "\n";
            }else{
                cout << "\n\n\n";
            }
        }
        if(table[j]!='-')
        {
            count++;
        }
    }
    cout << endl;
    if(count==9)
    {
        cout<<setw(108)<<"--------------------------------------------------------------------------------------------------------\n";
        cout<<setw(68)<<"All table are empty." << endl;
        cout<<setw(108)<<"--------------------------------------------------------------------------------------------------------\n";
        return;
    }
    while(true)
    {   
        
        cout<<setw(7)<<" "<<"               "<<"\\"<<"/____"<<endl;
        cout<<setw(7)<<" "<<"               /      "<<"\\"<<endl;
        cout<<setw(7)<<" "<<"              /     ^  "<<"\\"<<endl;
        cout<<setw(7)<<" "<<"          ___/   /"<<"\\"<<"__   "<<"\\"<<endl;
        cout<<setw(7)<<" "<<"         /      /    "<<"\\"<<"   |"<<endl;
        cout<<setw(7)<<" "<<"        / |_;;  |_;;   "<<"\\"<<"/"<<endl;
        cout<<setw(7)<<" "<<"_______|________"<<"\\"<<"_________________";
        cout<< "        INPUT TABLE WANT TO CHECK BILL (If want to exit input 0): ";
        cin >> number ;
        //cout<<setw(64)<<"---------------------------------------------------------\n\n";
        if(number==0)
        {  
            cout<<"\n";
            cout<<setw(108)<<"--------------------------------------------------------------------------------------------------------\n";
            return;
        }
        else if(table[number-1]!='-')
        {
            cout<<"\n";
            cout<<setw(108)<<"---------------------------------------------------\n";
            cout<<setw(95)<<"Sorry this table are empty."<<endl;
            cout<<setw(95)<<"Please select table again. ^^" << endl;
            cout<<setw(108)<<"---------------------------------------------------\n"; 
        }
        else 
        {
            break;
        }
    }
    vec_point = which_table(number);
    show_bill(*vec_point,book);
    int money=check_bill(*vec_point,book);
    add_daily_income(daily,money);
    table[number-1]=(number+48);
    (*vec_point).clear();


}

void print_daily_income(vector<daily_income> daily)
{
    cout<<"-------------------------------------------------------------------------------------------------------------------------------------\n";
    cout<<setw(50)<<right<<"(> '' '' <)"<<"\t"<<setw(30)<<right<<",_____,"<<endl;
    cout<<setw(50)<<right<<"(  ='o'=  )"<<"\t"<<setw(30)<<right<<"[ o.O ]"<<endl;
    cout<<setw(50)<<right<<"-(,,)-(,,)-"<<"\t"<<setw(30)<<right<<"\\(____("<<endl;
    cout<<setw(50)<<right<<"-_________-"<<"\t"<<setw(30)<<right<<"_''__''_"<<endl;
    cout <<setw(46)<<right<<"Date"<<"\t"<<setw(38)<<right<<"income"<<endl;
    for(unsigned int i=0;i<daily.size();i++)
    {
        cout<<setw(49)<<right<<daily[i].date<<"\t"<<setw(29)<<right<<daily[i].income<<endl;
    }
    cout<<"-------------------------------------------------------------------------------------------------------------------------------------\n";
    return ;

}

void push_daily_income(vector<daily_income> &daily)
{
    delete_old_daily();

    sqlite3_stmt * stmt;
    //menu --------> daily income
    sqlite3_prepare( db, "SELECT * FROM dailybill;", -1, &stmt, NULL );
    string date , income;
    int int_income;
    for(unsigned int i=0;i<daily.size();i++){
        date = daily[i].date;
        income = to_string(daily[i].income);
        string sqlstatement = "INSERT INTO dailybill (date,income) VALUES ('" + date + "','" + income + "');";
        sqlite3_prepare( db, sqlstatement.c_str(), -1, &stmt, NULL );//preparing the statement
        sqlite3_exec(db, sqlstatement.c_str(), callback, 0, NULL);
    }
    
}

void pull_daily_income(vector<daily_income> &daily)
{
    sqlite3_stmt * stmt;
    //menu --------> daily income
    sqlite3_prepare( db, "SELECT * FROM dailybill;", -1, &stmt, NULL );
    const unsigned char* text;
    daily_income tempdaily;
    int num;
    bool done = false;
    while (!done) {
        switch (sqlite3_step(stmt)) {
            case SQLITE_ROW:
                for(int i=0; i<2;i++){
                    if(i==0)
                    {
                        basic_string<unsigned char> temp = sqlite3_column_text(stmt, i);
                        string text( temp.begin(), temp.end() );
                        tempdaily.date=text;
                        daily.push_back(tempdaily);
                    }
                    else if(i==1)
                    {
                        num= sqlite3_column_int(stmt,i);
                        daily[daily.size()-1].income =num;
                    }
                }
                break;
            
            case SQLITE_DONE:
                done = true;
                cout<<"Push Daily Income Successfully!"<<endl;
                break;

            default:
                fprintf(stderr, "Failed.\n");
                return;
        }
        
    }

    sqlite3_finalize(stmt);

}

void all_daily_income(){

    sqlite3_stmt * stmt;
    //menu --------> daily income
    sqlite3_prepare( db, "SELECT * FROM dailybill;", -1, &stmt, NULL );//preparing the statement

    const unsigned char* text;
    bool done = false;
    cout<<"---------------------------------------------------------\n";
    cout <<setw(15)<<right<<"Date"<<"\t"<<setw(10)<<right<<"income"<<endl;
    while (!done) {
        switch (sqlite3_step(stmt)) {
            case SQLITE_ROW:
            for(int i=0; i<2;i++){
                text = sqlite3_column_text(stmt, i);
                if(i==1)
                {
                    cout <<"\t"<<setw(10)<<right; 
                } 
                else cout<<setw(15)<<right;
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

void update_menubook(vector<menubook> &book)
{
    
    book.clear();
    push_menubook(book);
    cout<<setw(97)<<"====================================="<<endl;
    cout<<setw(97)<<"|        Menubook is update         |"<<endl;
    cout<<setw(97)<<"====================================="<<endl;
    printmenubook(book);
    cout<<setw(108)<<"-----------------------------------------------------------------------------------------------------------------------\n";
    return;
}

void push_menubook(vector<menubook> &book){

    sqlite3_stmt * stmt;
  
    sqlite3_prepare( db, "SELECT * FROM menu;", -1, &stmt, NULL );
    const unsigned char* text;
    menubook tempbook;
    int num;
    bool done = false;
    while (!done) {
        switch (sqlite3_step(stmt)) {
            case SQLITE_ROW:
            for(int i=0; i<3;i++){
                if(i==0)
                {
                    tempbook.id = sqlite3_column_int(stmt,i);
                    book.push_back(tempbook);
                }
                else if(i==1)
                {
                    basic_string<unsigned char> temp = sqlite3_column_text(stmt, i);
                    string text( temp.begin(), temp.end() );
                    book[book.size()-1].name=text;
                }
                else if(i==2)
                {
                    num =sqlite3_column_int(stmt,i);
                    book[book.size()-1].price=num;

                }
            }
                break;
            
            case SQLITE_DONE:
                done = true;
                cout<<"\n";
                cout<<setw(96)<<"===================================="<<endl;
                cout<<setw(97)<<"|    Push Menubook Successfully!    |"<<endl;
                cout<<setw(96)<<"===================================="<<endl;
                break;

            default:
                fprintf(stderr, "Failed.\n");
                return;
        }
        
    }

    sqlite3_finalize(stmt);

}

void printmenubook(vector<menubook> &book)
{
    cout<<setw(100)<<"_________________________________________\n";
    cout<<setw(59)<<"|"<<setw(41)<<"|\n";
    cout<<setw(59)<<"|"<<setw(24)<<"MENU BOOK"<<setw(17)<<"|\n";
    cout<<setw(100)<<"|_______________________________________|\n";
    cout<<setw(59)<<"|"<<setw(41)<<"|\n";
    cout<<setw(59)<<"|" <<setw(8)<<right<<"Food ID"<<"\t"<<setw(15)<<left <<"Food Name"<<setw(10)<<right<<"Price"<<setw(2)<<"|"<<endl;
    for (unsigned int i = 0; i < book.size(); i++)
    {
        cout<<setw(59)<<"|"<<" "<<book[i].id;
        cout <<"\t\t"<<setw(15)<<left<<book[i].name; 
        cout <<setw(10)<<right<<book[i].price<<setw(2)<<"|"<<endl;

    }
    cout<<setw(100)<<"|_______________________________________|\n";
}

void delete_old_daily(){
    
    sqlite3_stmt * stmt;
    string sqlstatement = "DELETE FROM dailybill;";
    sqlite3_prepare( db, sqlstatement.c_str(), -1, &stmt, NULL );//preparing the statement
    sqlite3_exec(db, sqlstatement.c_str(), callback, 0, NULL);

}
//gcc sqlite3.c -c   ทำแบบนี้มันจะไม่ได้ exe แต่จะได้เป็น object file ที่ลิงค์เข้ากับโค้ดให้โปรแกรมเราไปเรียกใช้ตอน compile ครับ
//how to run (safe file first) ; g++ main.cpp sqlite3.o ; ./a.exe