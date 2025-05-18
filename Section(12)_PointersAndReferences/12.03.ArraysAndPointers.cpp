#include <iostream>

using namespace std;

int main()
{
    // Initialize Array.
    int scores[]{100, 95, 89};

    // Message
    cout << endl;
    cout << "Value of scores:\t" << scores <<"\tArray name value is:\t address of array 1st Element"<< endl;

    // Initialize Pointer{score_ptr} to Array{scores}.
    int *score_ptr{scores};

    cout << "Value of score_ptr: \t" << score_ptr <<"\tPointer Value is:\t address of array 1st element"<< endl;

    cout << "\nArray subscript notation:\n-------------------------" << endl;
    cout << scores[0] << endl;
    cout << scores[1] << endl;
    cout << scores[2] << endl;

    cout << "\nPointer subscript notation:\n-------------------------" << endl;
    cout << score_ptr[0] << endl;
    cout << score_ptr[1] << endl;
    cout << score_ptr[2] << endl;

    cout << "\nPointer offset notation:\n-------------------------" << endl;
    cout << *score_ptr << endl;
    cout << *(score_ptr + 1) << endl;
    cout << *(score_ptr + 2) << endl;

    cout << "\nArray offset notation:\n-------------------------" << endl;
    cout << *scores << endl;
    cout << *(scores + 1) << endl;
    cout << *(scores + 2) << endl;

    cout << endl;
    return 0;
}
