/*  =============================================================================================================
                                                Header Gaurd File - Start
    =============================================================================================================   */
#ifndef _MODULE_UNIQUE_POINTER_ROBOTICS_CORNER_
#define _MODULE_UNIQUE_POINTER_ROBOTICS_CORNER_

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

/*  =============================================================================================================
                                                Declarations
    =============================================================================================================   */
namespace Examples_UniquePointer_RoboticsCorner
{

    void unique_ptr_main1_Creation_using_new();
    void unique_ptr_main2_Creation_using_make_unique();
    void unique_ptr_main3_ptr2class();
    void unique_ptr_main4_ptr_vector_move_not_copy();
    void unique_ptr_main5_Creation_class_using_make_unique();
};

/*  =============================================================================================================
                                                Implementations
    =============================================================================================================   */

void Examples_UniquePointer_RoboticsCorner::unique_ptr_main1_Creation_using_new() // create, init by new, using.
{
    std::unique_ptr<int> p1{new int{100}}; // init by new.
    std::cout << "*p1= " << *p1 << "\n";   // 100

    *p1 = 200;                           // change value.
    std::cout << "*p1= " << *p1 << "\n"; // 200
} // Automatically deleted.

void Examples_UniquePointer_RoboticsCorner::unique_ptr_main2_Creation_using_make_unique() // init by """std::make_unique()""" ... """unique_ptr.reset()""" to delete and nullptr.
{
    std::unique_ptr<int> p1 = std::make_unique<int>(100); // init by """std::make_unique()""".
    std::cout << "*p1= " << p1.get() << "\n";             // get the value stored.
    std::cout << "p1.get()= " << p1.get() << "\n";        // get the value stored.

    p1.reset(); // location is deleted, p1 is nullptr.

    if (p1)
        std::cout << "*p1= " << *p1 << std::endl; // Won't execute (p1==nullptr).

} // Automatically delete.

void Examples_UniquePointer_RoboticsCorner::unique_ptr_main3_ptr2class() // Using unique_ptr with user defined classes.
{
    std::unique_ptr<Account> p1{new Account{"Larry"}};
    p1->Display();

    p1->deposit(2000);
    p1->withdraw(500);
    p1->Display();

} // Automatically delete.

void Examples_UniquePointer_RoboticsCorner::unique_ptr_main4_ptr_vector_move_not_copy() // Vectors and move (Copy Not Allowed).
{
    std::vector<std::unique_ptr<int>> vec1_VectorOfUniquePtrsToInt; // Create vector of unique_ptr

    std::unique_ptr<int> ptr{new int{100}}; // Create unique_ptr

    // Error - Copy NOT Allowed!
    // vec1_VectorOfUniquePtrsToInt.push_back(ptr);

    // OK - Move is Allowed.
    vec1_VectorOfUniquePtrsToInt.push_back(std::move(ptr));

} // Automatically delete.

void Examples_UniquePointer_RoboticsCorner::unique_ptr_main5_Creation_class_using_make_unique() // using unique_ptr with """std::make_unique<class>()""" - (C++14)
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
                                                Header Gaurd File - Start
    =============================================================================================================   */
#endif /*_MODULE_UNIQUE_POINTER_ROBOTICS_CORNER_*/