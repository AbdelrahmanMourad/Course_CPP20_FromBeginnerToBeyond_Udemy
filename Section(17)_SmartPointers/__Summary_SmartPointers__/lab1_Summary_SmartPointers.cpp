/*  =============================================================================================================
                                                Included libraries
    =============================================================================================================   */
/*Classes*/
#include "class_Account.h"
#include "class_Player.h"
/*Modules*/
#include "module_unique_ptr_DrMustafaSaad.h"
/*Libraries*/
#include <iostream>
#include <memory>
#include <vector>
#include <functional>

/*  =============================================================================================================
                                                Declarations
    =============================================================================================================   */

    /*  =============================================================================================================
                                                unique_ptr
    =============================================================================================================   */

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