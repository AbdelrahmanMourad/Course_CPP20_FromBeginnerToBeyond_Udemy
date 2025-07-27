/*  =============================================================================================================
                                                Header Gaurd File - Start
    =============================================================================================================   */
#ifndef _MODULE_UNIQUE_POINTER_DR_MUSTAFA_SAAD_
#define _MODULE_UNIQUE_POINTER_DR_MUSTAFA_SAAD_

/*  =============================================================================================================
                                                Included libraries
    =============================================================================================================   */
#include "class_smart_pointers_my_implementation.h"
#include "class_Account.h"
#include "class_Player.h"
#include <iostream>   // IO Stream.
#include <memory>     // Smart pointers.
#include <vector>     // Vectors.
#include <functional> // Lambdas.
#include <cstring>    // for memset.

/*  =============================================================================================================
                                                Declarations
    =============================================================================================================   */
namespace Examples_UniquePointer_DrMustafaSaad
{
    /*
    =============
    Key Takeaways
    =============
        unique_ptr cannot be copied, only moved.
        Use std::move to transfer ownership.
        Pass by reference if you want to keep using the pointer.
        Pass by const reference if you only need to read, not modify or move.
    */
    void unique_ptr_main00_Creation(void);
    void unique_ptr_main01_CopyConstructor_vs_Moving(void);
    void unique_ptr_main02_Addresses(void);
    void unique_ptr_main03_PassToFunction(void);
    void unique_ptr_main04_ReturnFromFunction(void);
    void unique_ptr_main05_HelperFunction(void);
    void unique_ptr_main06_PointerToArrayAndLeaks(void);
    void unique_ptr_main07_PointerWithVectors(void);
    void unique_ptr_main08_Release_Reset_MemoryLeaks(void);
    void unique_ptr_main09_warning_MemoryLeaks(void);
    void unique_ptr_main10_BehindTheSeen(void);
};

/*  =============================================================================================================
                                            unique_ptr
    =============================================================================================================   */

void Examples_UniquePointer_DrMustafaSaad::unique_ptr_main00_Creation(void)
{
    /*  ----------------------------------------
        Creation.
        ----------------------------------------
    */
    std::unique_ptr<int> p1{new int{20}}; // Direct Initialization.

    // CE: conversion from int* to unique_ptr
    // Internally explicit constructor
    // std::unique_ptr<int p1 = new int {20};

    std::cout << "*p1= " << *p1 << "\n\n";

    // Once we go out of scope:
    // p1 internals are destroyed.
}

void Examples_UniquePointer_DrMustafaSaad::unique_ptr_main01_CopyConstructor_vs_Moving(void)
{
    /*  ----------------------------------------
       Copy Constructor vs Moving.
       ----------------------------------------
   */
    std::unique_ptr<int> p2{new int{20}};

    // CE: use of """deleted copy constructor""".
    // But we can """move p2 internals""" to p3.
    // Useful for function calls in some scenarios.
    std::unique_ptr<int> p3{std::move(p2)};
    // Now: DON'T use p2 any more. Another pointer p3 has the ownership.

    if (p2 == nullptr)
        std::cout << "Yah, p2 nulled and moved to p3.\n\n";

    // Force delete.
    p3 = nullptr; // Exception in assignment.
    p3.reset();   // Also set to nullptr.
}

void Examples_UniquePointer_DrMustafaSaad::unique_ptr_main02_Addresses(void)
{
    /*  ----------------------------------------
        Addresses
        ----------------------------------------
    */
    std::unique_ptr<int> p4{new int{40}};

    // p4 is an object: so it has its own address
    /* Inside it is a raw pointer:
         -   The raw pointer itself: has an address.
         -   The raw pointer points to an address.   */
    // Now we have 3 addresses!

    int *raw_p4 = p4.get(); // "."  NOT "->"
    std::cout << "std::addressof(p4) == &p4" << " == " << std::addressof(p4) << " == " << &p4
              << "\n*p4= " << std::dec << *p4
              << "\n&raw_p4= " << std::hex << &raw_p4
              << "\n raw_p4= " << std::hex << raw_p4
              << "\n*raw_p4= " << std::dec << *raw_p4
              << "\n\n";
    /*  NOTE:
            """std::addressof(p4) == &p4"""
    */
}

void Examples_UniquePointer_DrMustafaSaad::unique_ptr_main03_PassToFunction(void)
{

    /*  ----------------------------------------
        Pass to function
        ----------------------------------------
    */
    std::function<void /*output*/ (std::unique_ptr<int> /*inputs*/)> print_0_Template_Lambda = [](std::unique_ptr<int> p1 /*inputs*/) -> void /*output*/ { /* Logic: Pass by value. */ };
    std::function<void(std::unique_ptr<int> p)> print_1_ByVal = [](std::unique_ptr<int> p) -> void { /*Logic: Pass by value. */ };
    std::function<void(std::unique_ptr<int> & p)> print_2_Ref = [](std::unique_ptr<int> &p) -> void { /*Logic: Pass by reference. */ };
    std::function<void(const std::unique_ptr<int> &p)> print_3_ConstRef = [](const std::unique_ptr<int> &p) -> void { /*Logic: Pass by reference.. const. */ };

    std::function<void(void)> TEST_pass2func = [&]() -> void
    {
        /*
        Why "CE" (Compilation Error) Happens
            1. unique_ptr Cannot Be Copied
                std::unique_ptr only allows move semantics (ownership transfer), not copy.
                Its copy constructor is deleted to prevent accidental double ownership and double deletion.
        */
        std::unique_ptr<int> p1{new int{20}}; // Direct Initialization.
        std::unique_ptr<int> &p2 = p1;        // Alias OK: still one owner.

        /*
            2. Passing by Value
                When you pass a unique_ptr by value (e.g., print_1_ByVal(p2)), the compiler tries to copy it.
                This is not allowed and causes a compilation error (CE).
        */
        // print_1_ByVal(p2); // ❌ Compilation Error: tries to copy unique_ptr // CE: use of deleted copy constructor.

        /*
            3. Passing by Move
                print_1_ByVal(std::move(p2)) is OK because std::move converts p2 into an rvalue, so the lambda receives ownership.
                After this call, p2 becomes nullptr (ownership transferred).
        */
        print_1_ByVal(std::move(p2)); // ✅ Ownership transferred, p2 is now nullptr // OK: pass it, but DON'T use it after return. /*Ownership Moved Already*/

        /*
            4. Passing by Reference
                print_2_Ref(p2) is OK because you’re passing a reference, not copying or moving.
                You can still use p2 after the call.
        */
        p2.reset(new int{30});
        print_2_Ref(p2); // ✅ Pass by reference, p2 still valid after call // // Perfect: Pass it, then you CAN use it after return.

        /*
            5. Passing by Move to Non-const Reference
                print_2_Ref(std::move(p2)) is NOT allowed because you cannot bind a temporary (rvalue) to a non-const lvalue reference.
        */
        // print_2_Ref(std::move(p2)); // ❌ Compilation Error: cannot bind rvalue to non-const ref // CE: temporary object to non const reference.

        /*
            6. Passing by Const Reference
                print_3_ConstRef(std::move(p2)) is OK because you can bind a temporary to a const reference.
                But you cannot modify or move from p2 inside the lambda.
        */
        print_3_ConstRef(std::move(p2)); // ✅ Pass by const reference, p2 is nullptr after move // Ok now: const reference.

        // void print_1_ByVal(std::unique_ptr<int> p) { /*Logic: Pass by value. */ }
        // void print_2_Ref(std::unique_ptr<int> &p) { /*Logic: Pass by reference. */ }
        // void print_3_ConstRef(const std::unique_ptr<int> &p) { /*Logic: Pass by reference.. const. */ }
    };

    TEST_pass2func();
}

void Examples_UniquePointer_DrMustafaSaad::unique_ptr_main04_ReturnFromFunction(void)
{

    /*  ----------------------------------------
        Return from function
        ----------------------------------------
    */
    std::function<std::unique_ptr<int>(void)> get_instance = [](void) -> std::unique_ptr<int>
    {
        std::unique_ptr<int> p{new int{20}};
        return p;
    };

    std::function<void(void)> TEST_returnFromFunc = [&]() -> void
    {
        std::unique_ptr<int> x = get_instance(); // Moving Object.
    };

    TEST_returnFromFunc();
}

void Examples_UniquePointer_DrMustafaSaad::unique_ptr_main05_HelperFunction(void)
{
    /*  ----------------------------------------
           Make Unique helper function
           ----------------------------------------
       */
    struct Employee
    {
        std::unique_ptr<int> &id;
        std::string name;
        Employee(std::unique_ptr<int> &i, std::string n) : id{i}, name{n} { std::cout << "Constructor Called: Employee.\n"; }
        void print(void) { std::cout << "Name: " << name << "\tid= " << *id << std::endl; }
    };

    std::function<void(void)> TEST_UniqueHelperFunc = [&](void) -> void
    {
        std::unique_ptr<int> p1{new int{20}};
        std::unique_ptr<int> p2 = std::make_unique<int>(30);
        auto p3 = std::make_unique<int>(40);

        std::unique_ptr<Employee> most{new Employee{p1, "Mostafa"}};
        auto emp = std::make_unique<Employee>(p1, "Belal");

        emp->print(); // Employee id 20
        emp.get();    // Notice ""."" not ""->""
    };
    TEST_UniqueHelperFunc();
}

void unique_ptr_main06_PointerToArrayAndLeaks(void)
{
    int n = 5;
    std::unique_ptr<int[]> p1{new int[n]};                  // Pointer to array of n integers.
    std::unique_ptr<int[]> p2{new int[n]()};                // Pointer to array of n integers.
    std::unique_ptr<int[]> p3 = std::make_unique<int[]>(n); // Pointer to array of n integers.

    /**** ALWAYS USE ""std::make_unique()"" ****/
    /*  -------------
        Are they same?  NO :)
        -------------
            -   p1 created memory and did not initialize (faster).
            -   p2 and p3 initialized to 0 [safe / slower].
    */
    /*   In Practice:    STL => vector/array are enough typically.   */

    for (int i = 0; i <= 5; ++i)
    {
        p1[i] = 7; // initialize the p1 array.
    }

    /* Function Definition. */
    std::function<void(void)> Ptr2Array_Leaks_FreeMemory = [](void) -> void
    {
        // BE CAREFUL: undefined behavior for freeing memory.
        std::unique_ptr<int> p_NotSafe{new int[5]}; // WRONG: Undefined Behavior!
        std::unique_ptr<int[]> p_Safe{new int[5]};  // CORRECT.
        *p_NotSafe = 10;

        /*  ---------------------------------------------------
        The problem is here:
            "std::unique_ptr<int> p_NotSafe{new int[5]};"
        This is undefined behavior because:
            "std::unique_ptr<int>" expects a pointer to a single int and will call "delete" on destruction.
            But you allocated an array with "new int[5]", which must be deleted with "delete[]".
            When "p_NotSafe" goes out of scope, it will call "delete p_NotSafe", not "delete[] p_NotSafe",
                which is undefined behavior and can cause memory leaks or crashes.

        How to Fix
            Use the array specialization:
                ""std::unique_ptr<int[]> p_Safe {new int[5]};"" // Correct: will call delete[] automatically
            Or, even better, use "std::make_unique":
                ""auto p = std::make_unique<int[]>(5);""
        --------------------------------------------------- */
    };
    std::function<void(void)> fast_initialize = [](void) -> void
    {
        int n = 100000;
        std::unique_ptr<int[]> p_2_arr{new int[n]};

        // You can get pointer array to do fast initialization.
        int *p2int = p_2_arr.get();

        /********* In integers: use memset ONLY with 0 and 1  *********/
        memset(p2int, -1, n * sizeof(int)); // Now arr "p_2_arr": -1 -1 -1 -1 -1 ...etc

        char str[] = "hello";
        memset(str, 't', sizeof(str)); //  tttttt
    };
    /* Function Call. */
    Ptr2Array_Leaks_FreeMemory();
    fast_initialize();
}

void unique_ptr_main07_PointerWithVectors(void)
{
    std::vector<std::unique_ptr<int>> vec;    // Create vector of Unique_ptrs 2 int
    vec.push_back(std::make_unique<int>(20)); // push_back()

    auto p1 = std::make_unique<int>(20); // Create unique_ptr 2 int.
    // vec.push_back(p1);                // CE: Using deleted Copy Construcotor.
    vec.push_back(std::move(p1)); // OK: p1 is now empty.

    auto p2 = std::make_unique<int>(20);

    /********** ""emplace_back()"" constructs in-place even withoud ""std::move()"" **********/
    vec.emplace_back(std::move(p2));
    vec.emplace_back(std::make_unique<int>(7));

    /*  ---------------------------------------------------------
        Since C++17: You can use emplace_back with & return
            "" auto &b = vec.emplace_back(std::make_unique<int>(7)); ""
        ---------------------------------------------------------   */
    for (auto &p : vec)
    {
        // you must use "&"
    }
}

void unique_ptr_main08_Release_Reset_MemoryLeaks(void)
{
    std::unique_ptr<int> p1_unique = std::make_unique<int>(20);

    // Return the pointer and set nullptr.
    int *p2_int = p1_unique.release();

    if (p1_unique == nullptr) // validate.
        std::cout << "p1 is gone.\n";

    // The ONLY case when you have to remove p2_int.
    std::cout << *p2_int << std::endl;
    delete p2_int;    // delete/ free the allocated memory.
    p2_int = nullptr; // null the pointer itself.

    /************* DON'T use ""relase()"" unless you have good reason. *************/

    // - Use release() to release ownership and return the raw pointer (manual deletion required).
    // - Use reset()   to delete the managed object and optionally take ownership of a new one.
}

void unique_ptr_main09_warning_DanglingPointer(void)
{
    int *p = new int{30};

    // You can assign same pointer to more that unique_ptr :(
    // Dangling pointer --> Double "delete"
    std::unique_ptr<int> p1{p};
    std::unique_ptr<int> p2{p};

    // RTE: once we go out of the scope. => double delete
    // Tip: Don't assign raw pointers this way.
}

void unique_ptr_main10_BehindTheSeen(void)
{
    /*  ------------------------------------------------------------------
        ●   Smart Pointers are just classes:
            ○   They wrap raw pointers. (raw pointer is private member)
            ○   operator overloading:   {*} , {"->"}
            ○   deleted copy constructor.
            ○   deleted copy assignment=.
            ○   Object goes out of scope: Destructor Called.
                ■   Properly clean the raw data
                ■   This technique is called Resource Acquisition Is Initialization (RAII).
            ○   Feel free to try to implement this class with some basic functionality. --> See "class my_unique_ptr"
        ------------------------------------------------------------------
    */
}

/*  =============================================================================================================
                                                Header Gaurd File - Start
    =============================================================================================================   */
#endif /*_MODULE_UNIQUE_POINTER_DR_MUSTAFA_SAAD_*/

/*
========================================================================================================
C++ Smart Pointer (unique_ptr) - Key Concepts & Best Practices Summary
========================================================================================================
| - unique_ptr is a smart pointer for exclusive ownership of dynamically allocated memory.
| - It cannot be copied, only moved (copy constructor is deleted).
| - Use std::move to transfer ownership between unique_ptrs.
| - Pass by reference (unique_ptr<T>&) to allow access without transferring ownership.
| - Pass by value (unique_ptr<T>) to transfer ownership (requires std::move).
| - Pass by const reference (const unique_ptr<T>&) to allow read-only access without transfer.
| - Returning unique_ptr from functions is safe (move semantics).
| - For arrays, use unique_ptr<T[]> to ensure correct deletion (delete[]).
| - Always use std::make_unique<T>() for exception safety and clarity.
| - Never use unique_ptr<T> for arrays allocated with new T[] (use unique_ptr<T[]> instead).
| - Avoid using unique_ptr<T>& as a member variable; prefer unique_ptr<T> for ownership.
| - After moving from a unique_ptr, the source becomes nullptr and should not be used.
| - Use get() to access the raw pointer, but avoid manual deletion.
| - Use reset() to delete the managed object and optionally take ownership of a new one.
| - Use release() to release ownership and return the raw pointer (manual deletion required).
| - For containers, prefer std::vector or std::array over raw arrays with unique_ptr.
| - Always match the unique_ptr type to the allocation type (T for single object, T[] for arrays).
| - Use unique_ptr for strict resource management and to prevent memory leaks.
========================================================================================================
*/