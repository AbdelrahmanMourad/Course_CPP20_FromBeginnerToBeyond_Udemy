/*
___________________________________________________________________

Reverse a std::string using Pointers (Challenging!)
Exercise: Reverse a std::string using Pointers

Specification:

Write a C++ function reverse_string that takes a std::string as input and returns a new std::string with the characters in reverse order. The function should use pointers to perform the reversal.

Function Signature:

std::string reverse_string(const std::string& str);
Input:

str: The input string.

Output:

The function should return a new string with the characters of str reversed.

Example:

std::string input = "Hello, World!";
std::string reversed = reverse_string(input);

// reversed should be "!dlroW ,olleH"




Hint: The c_str() function in C++ is used to obtain a pointer to a null-terminated character array (C-style string) that represents the contents of a std::string. It allows you to work with the underlying character array of the string.

Think about how you can leverage c_str() to obtain pointers to the first and last characters of the string. By manipulating these pointers, you can access and manipulate the characters in reverse order.




___________________________________________________________________
*/

// You do NOT have to write a main() function. The main() function is written by me
// behind the scenes to call your function and test your code.
#include <string>

std::string reverse_string(const std::string &str)
{
    std::string reversed;
    // Write your code below this line

    // Write your code abocve this line
    return reversed;
}

#include <iostream>
#include <string>

// This function takes a const std::string reference as input and returns a new string with its characters reversed.
// Pointers are used to traverse the input string from the end to the beginning.
std::string reverse_string(const std::string &str)
{
    // Determine the length of the input string.
    size_t length = str.size();

    // Create a new string (rev) with the same length as the input.
    // We resize rev first so that we can safely write reversed characters directly.
    std::string rev;
    rev.resize(length);

    // pStart is a pointer that points to the first character of the input string.
    // We use c_str() to get a constant C-style string (array of characters).
    const char *pStart = str.c_str();

    // pEnd is a pointer that points to the last character in the input string.
    // We add (length - 1) to the starting address to reach the end.
    const char *pEnd = pStart + length - 1;

    // pRev is a pointer that points to the beginning (first character) of the 'rev' string.
    // We get a modifiable pointer by taking the address of the first character of the string.
    char *pRev = &rev[0];

    // Loop until pEnd has traversed all characters back to pStart.
    while (pEnd >= pStart)
    {
        // Dereference pEnd to get the character it points to and store it in the location pointed to by pRev.
        *pRev = *pEnd;
        // Move pRev to the next position in the reverse string.
        pRev++;
        // Move pEnd backward to the previous character in the input string.
        pEnd--;
    }

    // Return the newly constructed reversed string.
    return rev;
}

int main()
{
    // Example usage of the reverse_string function.
    std::string input = "Hello, World!";
    std::string reversed = reverse_string(input);

    // Print the original and reversed strings.
    std::cout << "Original: " << input << std::endl;
    std::cout << "Reversed: " << reversed << std::endl;

    return 0;
}