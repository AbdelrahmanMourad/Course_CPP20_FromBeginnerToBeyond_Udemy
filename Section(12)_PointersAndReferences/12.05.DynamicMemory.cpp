// Section 12
// Dynamic Memory
#include <iostream>

using namespace std;

int main()
{

    int *int_ptr{nullptr};   // initialize ptr2int to location 0 in memory.
    int_ptr = new int;       // allocate the int on the heap
    cout << int_ptr << endl; // use it
    delete int_ptr;          // release it

    // Declare a variable 'size' of type size_t and initialize it to 0.
    size_t size{0};            // size_t: typedef long long variable used for storing sizes returning from sizeof()
    double *temp_ptr{nullptr}; // initialize ptr2double.

    /*
    The program asks the user for the number of “temps” (temperatures), storing that value in size.
    Since size_t is non-negative, it prevents any accidental use of negative numbers in this context.
    */
    cout << "How many temps? "; // display msg to user.
    cin >> size;                // get size from user.

    temp_ptr = new double[size]; // allocate the storage on the heap [array of double]
    cout << temp_ptr << endl;    // use it
    delete[] temp_ptr;           // release it

    cout << endl;

    // cout << sizeof(unsigned long long) << "\n";  // 8-Bytes
    return 0;
}
