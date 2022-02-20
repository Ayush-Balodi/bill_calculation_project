#include<iostream>
#include<fstream>
#include<vector>
#include<sstream>
#include<conio.h>
#include<cstdlib>
#include<windows.h>
#include<string>

using namespace std;

HANDLE h = GetStdHandle( STD_OUTPUT_HANDLE);

#define BLUE SetConsoleTextAttribute( h , 1 );//Blue
#define PUR SetConsoleTextAttribute( h , 5 );//Purple
#define GRN SetConsoleTextAttribute( h , 10 );//Bright green
#define CYN SetConsoleTextAttribute( h , 3 );//Cyan
#define RED SetConsoleTextAttribute( h , 4 );//Red

class Bill{

    string name;
	int item_number , quantity;
	float tax , discount , price;
    
    public:
        void report();
		void add();
		void show( int );
		void edit ();
		void del ();
		int check( int );
		float calculate( float , int , float , float );
};

/*Generates the report of all the products in the inventory*/
void Bill::report(){
	
	system("cls");

	fstream fin("report.csv",ios::in);
	if( fin.fail() ){
		RED
		cout << "*  Error occured while opening the file." << endl;
		return;
	}
	
	string line , word;
	vector<string> row;
	float net_amount = 0;
	int count=0;

	CYN
	cout << "////////////////////////////////////BILL DETAILS///////////////////////////////////\n" << endl << endl;

	GRN
	cout << "Item no Name            Price   Quantity        Tax     Discount        Net Amount" << endl;
	while( getline( fin , line ) ){
		
		row.clear();
		stringstream ss(line);
		
		while( getline ( ss , word , ',' ) ){
			row.push_back(word);
		}

		/*Display the content of the report.csv file*/
		for( int i=0 ; i<7 ; i++ ){
			if( i == 3 || i == 5 ){
				cout << row[i] << "\t\t";
			}
			else{
				cout << row[i] << "\t";
			}
			if( i==6 ){
				net_amount = net_amount + (float)stof(row[i]);
			}
		}
		cout << endl;
		count ++;
	}
	
	cout << "\n\n\t\t\tTotal inventory : " << net_amount << endl;
	
	fin.close();
	return;
}

void Bill::add (){
	
	fstream fin("report.csv",ios::app);
	if( fin.fail() ){
		RED
		cout << "*  Error occured while opening the file." << endl;
		return;
	}

	GRN
	cout << "*  Item number => ";
	cin >> item_number;
	
	cout << "*upto 11 characters only*" << endl;
	fflush( stdin );
	cout << "*  Name        => ";
	getline(cin , name);

	cout << "*  Quantity    => ";
	cin >> quantity;

	cout << "*  Tax         => ";
	cin >> tax;

	cout << "*  Discount    => ";
	cin >> discount;

	cout << "*  Mrp         => ";
	cin >> price;
    
	float net_amount = calculate(price , quantity , tax , discount);
    
	fin << item_number << "," << name << "," << price << "," << quantity << "," << tax << "," << discount << "," ;
	fin << net_amount << "\n";
	
	fin.close();
    return;
}

void Bill::show ( int num ){
	
	fstream fin("report.csv",ios::in);
	if( fin.fail() ){
		RED
		cout << "*  Error occured while opening the file." << endl;
		fin.close();
		return;
	}
	
	string line , word;
	vector<string> row;
	int itemno;

	while( getline( fin , line ) ){

		row.clear();
		stringstream ss(line);
		
		while( getline ( ss , word , ',' ) ){
			
			row.push_back(word);
		}
		itemno = stoi(row[0]);

		BLUE	
		if( num == itemno ){

			cout << endl;
			cout << "*  Item Number      => " << row[0] << endl << endl;
			cout << "*  Name of item     => " << row[1] << endl << endl;
			cout << "*  Inventory Cost   => " << row[6] << endl << endl << endl;
			cout << "\t*********************************************" << endl;
			cout << "\t\t\tDETAILS" << endl;
			cout << "\t*********************************************" << endl << endl;
			cout << "\tPRICE                       => " << row[2] << endl;
			cout << "\tQUANTITY                    => " << row[3] << endl;
			cout << "\tTAX PERCENTAGE              => " << row[4] << endl;
			cout << "\tDISCOUNT PERCENTAGE         => " << row[5] << endl;
			cout << "\tINVENTORY COST              => " << row[6] << endl << endl;
			cout << "\t*********************************************" << endl;
			fin.close();
			return;
		}
	}
	cout << "*  No such item is present in inventory." << endl;
	
	fin.close();
	return;
}
 
void Bill::edit(){

    int itemno , num , index;
    char choice;
ss:
	system("cls");
	CYN
	cout << "///////////////////////////////EDIT DETAILS/////////////////////////////////" << endl << endl;
    
	GRN
    cout << "*  Enter the item number => ";
    cin >> itemno;

    if( check( itemno ) == 0 ){
		RED
        cout << "*  Item number not existed.Redirecting........." << endl;
		cout << "*  Press any key to continue => ";
		getch();
        goto ss;
    }

	RED
	cout << "*  I=>Item number ; N=>Name ; P=>Price ; Q=>Quantity ; T=>Tax ; D=>Discount" << endl;
    GRN
	cout << "*  Enter particular what you want to update(I/N/P/Q/T/D) => ";
    cin >> choice;

    if (choice == 'I' || choice == 'i')
        index = 0;
    else if (choice == 'N' || choice == 'n')
        index = 1;
    else if (choice == 'P' || choice == 'p')
        index = 2;
    else if (choice == 'Q' || choice == 'q')
        index = 3;
    else if (choice == 'T' || choice == 't')
        index = 4;
    else if( choice == 'D' || choice == 'd')
        index = 5;
    else {
		RED
        cout << "*  Wrong choice.Enter again\n";
		cout << "*  Redirecting ........" <<endl;
		cout << "*  Press any key to continue => ";
		getch();
        goto ss;
    }

	cout << "********************CURRENT DETAILS*********************************" << endl << endl;
	show( itemno );
    string str;
	cout << endl;
	GRN
	cout << "**********************NEW DETAILS***********************************" << endl;
    cout << "*  Enter new details => ";

    fflush(stdin);
    
    getline( cin , str );

    if( choice == 'I' || choice == 'i' ){

        if( check( stoi(str) ) == 1 ){
			RED
            cout << "*  Item number already existed.Redirecting........." << endl;
			cout << "*  Press any key to continue => ";
            goto ss;
        }
    }

    fstream fin("report.csv",ios::in);
    fstream fout("reportcard.csv",ios::out);

    if( fin.fail() || fout.fail() ){
		RED
        cout << "*  Error occured while opening the file." << endl;
        return;
    }
	
    string line , word;
    vector<string> row;
    int c2=0;

    while( getline ( fin , line ) ){
        
        row.clear();
        stringstream ss( line );

        while( getline( ss , word , ',' ) ){
            row.push_back( word );
        }

        num = stoi( row[0] );
        int row_size = row.size();

        if( num == itemno ){
            c2 = 1;
            row[index] = str;

            if (!fin.eof()) {
                
                for ( int i = 0; i < row_size-1 ; i++) {
  
                    fout << row[i] << ',';
                }
                fout << row[row_size - 1] << "\n";
            }
        }
        else{
            if (!fin.eof() ){
                for ( int i = 0; i < row_size-1 ; i++) {
                    fout << row[i] << ',';
                }
                fout << row[row_size - 1] << "\n";
            }
        }
    }
    if( c2 == 0 ){
		RED
        cout << "*  Record not found." << endl;
    }
    fin.close();
    fout.close();

    remove("report.csv");
    rename("reportcard.csv","report.csv");

    return;
}

int main () {

	int choice;					//choice -> for maintaining user choice
	Bill obj;					//object of class Bill

menu:
	system("cls");
	CYN
	cout << "////////////////////SUPERMARKET BILLING CALCULATION SYSTEM//////////////////////" << endl << endl << endl;
	GRN
	cout << "******************MAIN MENU***********************" << endl;
	cout << "*  1.>Bill Report                                *" << endl;
	cout << "*  2.>Add/Edit/Delete item                       *" << endl;
	cout << "*  3.>Show item list                             *" << endl;
	cout << "*  4.>Exit                                       *" << endl;
	cout << "**************************************************\n" << endl << endl;

	BLUE
	cout << "*  Enter your choice => " ; 
	cin >> choice ;
		
	switch ( choice ){
		
		case 1 :{
		one:
			int choice;
			system("cls");
			CYN
			cout << "//////////////////////ADD DETAILS///////////////////////////" << endl << endl;

			GRN
			cout << "*************************" << endl;
			cout << "*  1.>All items         *" << endl;
			cout << "*  2.>Back to main menu *" << endl;
			cout << "*************************" << endl << endl;

			cout << "*  Enter your choice => ";
			cin >> choice;

			switch ( choice ){
				case 1:{
					obj.report ();
					cout << endl;
					PUR
					cout << "*  Redirecting........." << endl;
					cout << "*  Press any key to continue => ";
					getch();
					goto one;
				}
				case 2:{
					cout << endl;
					PUR
					cout << "*  Redirecting........." << endl;
					cout << "*  Press any key to continue => ";
					getch();
					goto menu;
				}
				default:{
					RED
					cout << "*  Invalid choice" << endl;
					PUR
					cout << endl;
					cout << "*  Redirecting........." << endl;
					cout << "*  Press any key to continue => ";
					getch();
					goto one;
				}
			}
		}
		case 2 :{
		two:
			int choice;
			system("cls");
			CYN
			cout << "//////////////////////ADD/REMOVE/DELETE///////////////////////////" << endl << endl;

			GRN
			cout << "*********************EDITING AREA**************************" << endl;
			cout << "*  1.>ADD Item Details                                    *" << endl;
			cout << "*  2.>EDIT Item Details                                   *" << endl;
			cout << "*  3.>DELETE Item Details                                 *" << endl;
			cout << "*  4.>Back to main menu                                   *" << endl;
			cout << "***********************************************************" << endl << endl;

			BLUE
			cout << "*  Enter your choice => ";
			cin >> choice;

			switch( choice ){
				case 1:{
					system("cls");
					CYN
					cout << "////////////////////////////ADD DETAILS//////////////////////////////////\n" << endl << endl;
					obj.add();
					cout << endl << endl;
					
					PUR
					cout << "*  Redirecting........." << endl;
					cout << "*  Press any key to continue => ";
					
					getch();
					goto two;
				}
				case 2 :{
					system("cls");
					CYN
					cout << "////////////////////////////EDIT DETAILS/////////////////////////////////\n" << endl << endl;
					obj.edit();
					cout << endl << endl;
					
					PUR	
					cout << "*  Redirecting........." << endl;
					cout << "*  Press any key to continue => ";
					
					getch();
					goto two;
				}
				case 3:{
					system("cls");
					CYN
					cout << "//////////////////////////////DELETE DETAILS/////////////////////////////////\n" <<endl << endl;
					obj.del();
					cout << endl << endl;

					PUR
					cout << "*  Redirecting........." << endl;
					cout << "*  Press any key to continue => ";
					
					getch();
					goto two;
				}
				case 4:{
					PUR
					cout << endl << endl;
					cout << "*  Redirecting........." << endl;
					cout << "*  Press any key to continue => ";
					
					getch();
					goto menu;
				}
				default:{
					RED
					cout << "*  Invalid choice" << endl;
					
					PUR
					cout << endl << endl;
					cout << "*  Redirecting .............";
					cout << "*  Enter any key to continue => ";
					
					getch();
					goto two;
				}
			}
		}
		case 3:{
		
		three:
			int ch;
			system("cls");

			CYN
			cout << "///////////////////////////////SHOW DETAILS//////////////////////////////////" << endl << endl;
			
			GRN
			cout << "*************************" << endl;
			cout << "*  1.>Show the detail   *" << endl;
			cout << "*  2.>Back to main menu *" << endl;
			cout << "*************************" << endl << endl;

			BLUE
			cout << "*  Enter your choice => ";
			cin >> ch;

			if( ch == 1 ){
				int itemno;
				cout << "*  Enter the item number => ";
				cin >> itemno;
				obj.show( itemno );

				PUR
				cout << endl << endl;
				cout << "*  Redirecting........." << endl;
				cout << "*  Press any key to continue => ";
				getch();
				goto three;
			}
			else if( ch == 2 ){
				PUR
				cout << endl << endl;
				cout << "*  Redirecting........." << endl;
				cout << "*  Press any key to continue => ";
				
				getch();
				goto menu;
			}else{
				RED
				cout << "*  Invalid Choice." << endl;

				PUR
				cout << endl << endl;
				cout << "*  Redirecting........." << endl;
				cout << "*  Press any key to continue => ";
				
				getch();
				goto three;
			}
		}
		case 4:{
			char ch;
			system("cls");
			RED
			cout << "*  Are you sure you want to exit ? (Y/N) => ";
			cin >> ch;
			if( ch == 'y' || ch == 'Y' ){
				system("cls");
				cout << "*  Thanks for using our services.\n\n";
				cout << endl << endl << "=================================Thanks=====================================" << endl;
				getch();
				break;
			}
			else if( ch == 'N' || ch == 'n' ){
				goto menu;
			}
			else{
				goto menu;
			}
		}
		default:{
			RED
			cout << "*  Invalid choice" << endl;
			cout << "*  Redirecting .............";
			cout << "*  Enter any key to continue => ";
			getch();
			goto menu;
		}
	}
	system("cls");
	return 0;
}