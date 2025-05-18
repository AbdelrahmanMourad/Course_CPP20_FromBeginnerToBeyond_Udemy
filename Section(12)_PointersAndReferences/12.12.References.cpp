// Section 12
// References
// Please see the section 11 examples for references as function paramters
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
    
    int num {100};
    int &ref {num};
    
    cout << num << endl;    // 100
    cout << ref << endl;    // 100
    
    num  = 200;
    cout << "\n---------------------------------" << endl;
    cout << num << endl;    // 200
    cout << ref << endl;    // 200
    
    ref = 300;
    cout << "\n---------------------------------" << endl;
    cout << num << endl;    // 300
    cout << ref << endl;    // 300
    
    cout << "\n---------------------------------" << endl;
    vector<string> stooges {"Larry", "Moe", "Curly"};

    for (auto str: stooges)     
        str = "Funny";        // str is a COPY of the each vector element
      
    for (auto str:stooges)    // No change
        cout << str << endl;
 
    cout << "\n---------------------------------" << endl;
    for (auto &str: stooges)  // str is a reference to each vector element
        str = "Money";
     
    for (auto const &str:stooges)   // notice we are using const
        cout << str << endl;        // now the vector elements have changed
    
    cout << endl;
    return 0;
}

