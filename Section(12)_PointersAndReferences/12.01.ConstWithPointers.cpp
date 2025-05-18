#include <iostream>

using namespace std;

int main()
{
    int high_score{100};
    int low_score{65};

    // Pointer to const-int.
    const int *ptr1{&high_score}; // Initialize pointer.
    // *ptr1 = 77;                   // ERROR .. Change variable value by dereference "*".
    // ptr1 = &low_score;            // OK    .. Point to another Variable

    // Const-Pointer to int.
    int *const ptr2{&high_score}; // Initialize pointer.
    // *ptr2 = 77;                   // OK       .. Change variable value by dereference "*".
    // ptr2 = &low_score;            // ERROR    .. Point to another Variable.

    // Const-pointer to const-int.
    const int *const ptr3{&high_score}; // Initialize pointer.
    // *ptr3 = 77;                         // ERROR .. Change variable value by dereference "*".
    // ptr3 = &low_score;                  // ERROR .. Point to another Variable
}
