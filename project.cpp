#include<iostream>
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

int main (){
    return 0;
}