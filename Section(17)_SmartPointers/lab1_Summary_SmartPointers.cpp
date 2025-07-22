/*  =============================================================================================================
                                                Included libraries
    =============================================================================================================   */
#include <iostream>
#include <memory>
#include <vector>
#include <functional>

/*  =============================================================================================================
                                                Declarations
    =============================================================================================================   */
class Account
{
private:
    std::string name_;
    double balance_ = 0;

public:
    // Account(std::string n) : name_{n} { std::cout << "Contructor Called: Account.\n" };
    Account(std::string n, double b = 0) : name_{n}, balance_{b} { std::cout << "Contructor Called: Account.\n"; }
    void deposit(double amount) { this->balance_ += amount; }
    void withdraw(double amount) { this->balance_ -= amount; }
    void Display() const { std::cout << "Acc Name= " << this->name_ << "\t,Balance= " << this->balance_ << "\n"; }
    void operator*(Account &rhs) { rhs.Display(); }
};

class Player
{
private:
    std::string name_;
    int id_;
    int balance_;

public:
    Player(std::string n, int i, int b) : name_{n}, id_{i}, balance_{b} {}
};
/*  =============================================================================================================
                                                unique_ptr
    =============================================================================================================   */
namespace DrMostafaSaadExamples
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
    void unique_ptr_main0_DrMostafaSaad(void);
};
void DrMostafaSaadExamples::unique_ptr_main0_DrMostafaSaad(void)
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
    };
    TEST_pass2func();

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

// void print_1_ByVal(std::unique_ptr<int> p) { /*Logic: Pass by value. */ }
// void print_2_Ref(std::unique_ptr<int> &p) { /*Logic: Pass by reference. */ }
// void print_3_ConstRef(const std::unique_ptr<int> &p) { /*Logic: Pass by reference.. const. */ }

void unique_ptr_main1() // create, init by new, using.
{
    std::unique_ptr<int> p1{new int{100}}; // init by new.
    std::cout << "*p1= " << *p1 << "\n";   // 100

    *p1 = 200;                           // change value.
    std::cout << "*p1= " << *p1 << "\n"; // 200
} // Automatically deleted.

void unique_ptr_main2() // init by """std::make_unique()""" ... """unique_ptr.reset()""" to delete and nullptr.
{
    std::unique_ptr<int> p1 = std::make_unique<int>(100); // init by """std::make_unique()""".
    std::cout << "*p1= " << p1.get() << "\n";             // get the value stored.
    std::cout << "p1.get()= " << p1.get() << "\n";        // get the value stored.

    p1.reset(); // location is deleted, p1 is nullptr.

    if (p1)
        std::cout << "*p1= " << *p1 << std::endl; // Won't execute (p1==nullptr).

} // Automatically delete.

void unique_ptr_main3() // Using unique_ptr with user defined classes.
{
    std::unique_ptr<Account> p1{new Account{"Larry"}};
    p1->Display();

    p1->deposit(2000);
    p1->withdraw(500);
    p1->Display();

} // Automatically delete.

void unique_ptr_main4() // Vectors and move (Copy Not Allowed).
{
    std::vector<std::unique_ptr<int>> vec1_VectorOfUniquePtrsToInt; // Create vector of unique_ptr

    std::unique_ptr<int> ptr{new int{100}}; // Create unique_ptr

    // Error - Copy NOT Allowed!
    // vec1_VectorOfUniquePtrsToInt.push_back(ptr);

    // OK - Move is Allowed.
    vec1_VectorOfUniquePtrsToInt.push_back(std::move(ptr));

} // Automatically delete.

void unique_ptr_main5() // using unique_ptr with """std::make_unique<class>()""" - (C++14)
{
    /*
    ===============================================
    -   More effecient - no calls to new or delete.
    ===============================================
    */
    std::unique_ptr<int> p1 = std::make_unique<int>(100);

    std::unique_ptr<Account> p2 = std::make_unique<Account>("Curly", 5000);

    auto p3 = std::make_unique<Player>("Hero", 100, 100); // auto == std::unique_ptr<Player>

} // Automatically delete.

/*  =============================================================================================================
                                                shared_ptr
    =============================================================================================================   */

void shared_ptr_main1()
{

    std::shared_ptr<int> p1{new int{100}};                                            // Init p1 by new value 100
    std::cout << "*p1= " << *p1 << "\t,\tp1.use_count()= " << p1.use_count() << "\n"; //  100 1

    //  Shared Ownership
    std::shared_ptr<int> p2{p1};                                                      // Init p2 by copy of p1
    std::cout << "*p2= " << *p2 << "\t,\tp2.use_count()= " << p2.use_count() << "\n"; //  100 2

    p1.reset();                                                                             // p1 is nulled ,   decrement the use_count() by 1
    std::cout << "*p1= " << "nullptr" << "\t,\tp1.use_count()= " << p1.use_count() << "\n"; //  nullptr 0
    std::cout << "*p2= " << *p2 << "\t,\tp2.use_count()= " << p2.use_count() << "\n";       //  100     1
} // Automatically deleted.

void shared_ptr_main2()
{
    std::shared_ptr<int> p1 = std::make_shared<int>(100); // use_count: 1
    std::shared_ptr<int> p2{p1};                          // use_count: 2
    std::shared_ptr<int> p3;
    p3 = p1; // use_count: 3
    /*
    ==================================================================
    NOTES:
        -   Use """std::make_shared()""" - it's more efficient!
        -   All 3 pointers point to the same object on the heap!
        -   When the ""use_count()"" becomes 0 the heap object is deallocated.
    ==================================================================
    */
} // Automatically deleted.

void shared_ptr_main3()
{
    std::vector<std::shared_ptr<int>> vec1_VectorOfSharedPtrsToIntegers; // vector of shared_ptrs to int.

    std::shared_ptr<int> ptr1{new int{100}};                       // init shared_ptr to int DMA, init with 100
    std::cout << "ptr1.use_count()= " << ptr1.use_count() << "\n"; // Print after share with copy.

    vec1_VectorOfSharedPtrsToIntegers.push_back(ptr1); // OK - copy IS allowed in shared_ptr.
    std::cout << "v.push_back();\n";
    std::cout << "ptr1.use_count()= " << ptr1.use_count() << "\n"; // Print after share with copy.

    vec1_VectorOfSharedPtrsToIntegers.push_back(ptr1);
    std::cout << "v.push_back();\n";
    std::cout << "ptr1.use_count()= " << ptr1.use_count() << "\n"; // Print after share with copy.

    vec1_VectorOfSharedPtrsToIntegers.push_back(vec1_VectorOfSharedPtrsToIntegers[0]);
    std::cout << "v.push_back();\n";
    std::cout << "ptr1.use_count()= " << ptr1.use_count() << "\n"; // Print after share with copy.
    std::cout << "vector1[0].use_count()= "
              << vec1_VectorOfSharedPtrsToIntegers[0].use_count() << "\n"; // Print after share with copy.

    vec1_VectorOfSharedPtrsToIntegers.pop_back();
    std::cout << "v.pop_back();\n";
    std::cout << "ptr1.use_count()= " << ptr1.use_count() << "\n"; // Print after release once.

    vec1_VectorOfSharedPtrsToIntegers[1].reset();
    std::cout << "v[1].reset();\n";
    std::cout << "ptr1.use_count()= " << ptr1.use_count() << "\n"; // Print after release once.
} // Automatically delete.

void shared_ptr_main4()
{
    std::shared_ptr<Account> ptr1{new Account{"Mohamed"}};
    ptr1->Display();

    ptr1->deposit(1000);
    ptr1->withdraw(500);

    ptr1->Display();
} // Automatically delete.

/*  =============================================================================================================
                                                weak_ptr
    =============================================================================================================   */

void weak_ptr_main1()
{
    //
} // Automatically delete.
void weak_ptr_main2()
{
    //
} // Automatically delete.
void weak_ptr_main3()
{
    //
} // Automatically delete.
void weak_ptr_main4()
{
    //
} // Automatically delete.

/*  =============================================================================================================
                                                main - Entry Point
    =============================================================================================================   */
int main()
{
    /*___________unique_ptr___________*/
    DrMostafaSaadExamples::unique_ptr_main0_DrMostafaSaad();
    // unique_ptr_main1(); //// init by new, reset(), use_count()
    // unique_ptr_main2(); //// init by std::make_shared<>(), init by copy constructor, init by assignment operator=
    // unique_ptr_main3(); //// vector if shared pointers.
    // unique_ptr_main4(); //// user defined classes.
    // unique_ptr_main5();

    /*___________shared_ptr___________*/
    // shared_ptr_main1(); // init by new, reset(), use_count()
    // shared_ptr_main2(); // init by std::make_shared<>(), init by copy constructor, init by assignment operator=
    // shared_ptr_main3(); // vector if shared pointers.
    // shared_ptr_main4(); // user defined classes.

    /*___________weak_ptr___________*/
    // weak_ptr_main1(); //// init by new, reset(), use_count()
    // weak_ptr_main2(); //// init by std::make_shared<>(), init by copy constructor, init by assignment operator=
    // weak_ptr_main3(); //// vector if shared pointers.
    // weak_ptr_main4(); //// user defined classes.

    return 0;
}

/*
========================================================================================================
C++ Smart Pointers: unique_ptr, shared_ptr, weak_ptr - Methods, Usage, and Differences
========================================================================================================
| unique_ptr
| - Exclusive ownership of a dynamically allocated object.
| - Cannot be copied, only moved.
| - Useful methods:
|     * get()        : Returns the raw pointer.
|     * release()    : Releases ownership, returns raw pointer, does NOT delete object.
|     * reset(p)     : Deletes current object, takes ownership of p (or nullptr).
|     * swap(other)  : Swaps pointers with another unique_ptr.
|     * operator*    : Dereference.
|     * operator->   : Member access.
| - Use when only one owner is needed (fastest, safest).

--------------------------------------------------------------------------------
| shared_ptr
| - Shared ownership via reference counting.
| - Multiple shared_ptrs can own the same object.
| - Useful methods:
|     * get()        : Returns the raw pointer.
|     * use_count()  : Returns number of shared_ptrs owning the object.
|     * reset(p)     : Releases ownership, optionally takes new pointer.
|     * swap(other)  : Swaps pointers with another shared_ptr.
|     * operator*    : Dereference.
|     * operator->   : Member access.
| - Use when multiple owners are needed (e.g., containers, callbacks).

--------------------------------------------------------------------------------
| weak_ptr
| - Non-owning reference to an object managed by shared_ptr.
| - Does NOT affect reference count.
| - Useful methods:
|     * lock()       : Returns a shared_ptr if object is still alive, else nullptr.
|     * expired()    : Returns true if managed object was deleted.
|     * reset()      : Releases reference.
|     * swap(other)  : Swaps pointers with another weak_ptr.
| - Use to break circular references or observe shared_ptr-managed objects.

--------------------------------------------------------------------------------
| Differences & Use Cases
| - unique_ptr: Exclusive ownership, cannot be copied, best for strict resource management.
| - shared_ptr: Shared ownership, reference counting, best for shared resources.
| - weak_ptr  : Non-owning, best for observing shared_ptr objects or breaking cycles.

--------------------------------------------------------------------------------
| Tips & Best Practices
| - Prefer unique_ptr by default; use shared_ptr only when sharing is required.
| - Use make_unique/make_shared for exception safety and efficiency.
| - Never manually delete memory managed by smart pointers.
| - Use weak_ptr to avoid memory leaks from circular references.
| - Use get() only when you need to interface with legacy APIs.

--------------------------------------------------------------------------------
| Interview Q&A
| Q1: What is the difference between unique_ptr and shared_ptr?
| Q2: How does shared_ptr manage memory?
| Q3: What is the purpose of weak_ptr?
| Q4: What happens if you copy a unique_ptr?
| Q5: When is use_count() useful?
| Q6: How do you break a circular reference with smart pointers?
| Q7: What does release() do in unique_ptr?
| Q8: How do you check if a weak_ptr is
========================================================================================================
*/