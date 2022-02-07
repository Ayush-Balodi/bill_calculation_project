#include<iostream>
#include<fstream>
#include<vector>
#include<sstream>

using namespace std;

class Bill{
    private:
        string name;
        int item_number , quantity;
        float price , tax , discount , mrp;
    
    public:
        void report ();
        void entry ();
};

/*Generates the bill report all the products in the inventory*/
void Bill::report (){
    system("cls");
    fstream fin("report.csv",ios::in);

    if( fin.eof() ){
        cout << "Unable to access tyhe file." << endl;
        return;
    }
    string line , word;
    vector<string> row;

    int count=0;
    while( getline( fin , line ) ){
        row.clear();

        /*stringstream changes the input stream to string stream and
          now getline can be overloaded to apply delimiters*/

        stringstream ss( line );
        while( getline ( ss , word , ',' ) ){
            row.push_back( word );
        }

        if( count == 0 ){
            /*isplay the heading of the report.csv file*/
            for(int i=0 ; i<7 ; i++){
                cout << row[i] << "\t";
            }
            cout << endl;
        }
        else{
            /*isplay the content of the report.csv file*/
            for(int i=0 ; i<7 ; i++){
                if( i==3 || i==5 ){
                    cout << row[i] << "\t\t";
                }
                else{
                    cout << row[i] << "\t";
                }
            }
            cout << endl;
        }
        count ++;
    }
    fin.close();
    return;
}

int main (){
    Bill obj;
    obj.report();
    return 0;
}