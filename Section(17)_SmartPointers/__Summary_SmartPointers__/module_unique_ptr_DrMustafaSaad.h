/*  =============================================================================================================
                                                Included libraries
    =============================================================================================================   */
#include "class_Account.h"
#include "class_Player.h"
#include <iostream>
#include <memory>
#include <vector>
#include <functional>

/*  =============================================================================================================
                                                Declarations
    =============================================================================================================   */
namespace DrMustafaSaadExamples
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
    void unique_ptr_main0_Creation(void);
    void unique_ptr_main1_CopyConstructor_vs_Moving(void);
    void unique_ptr_main2_Addresses(void);
    void unique_ptr_main3_PassToFunction(void);
    void unique_ptr_main4_ReturnFromFunction(void);
    void unique_ptr_main5_HelperFunction(void);
};

/*  =============================================================================================================
                                            unique_ptr
    =============================================================================================================   */

void DrMustafaSaadExamples::unique_ptr_main0_Creation(void)
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

void DrMustafaSaadExamples::unique_ptr_main1_CopyConstructor_vs_Moving(void)
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

void DrMustafaSaadExamples::unique_ptr_main2_Addresses(void)
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

void DrMustafaSaadExamples::unique_ptr_main3_PassToFunction(void)
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

void DrMustafaSaadExamples::unique_ptr_main4_ReturnFromFunction(void)
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

void DrMustafaSaadExamples::unique_ptr_main5_HelperFunction(void)
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
