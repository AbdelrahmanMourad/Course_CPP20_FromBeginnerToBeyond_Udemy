/*  =============================================================================================================
                                                Header Gaurd File - Start
    =============================================================================================================   */
#ifndef _MODULE_SHARED_POINTER_ROBOTICS_CORNER_
#define _MODULE_SHARED_POINTER_ROBOTICS_CORNER_

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
namespace Examples_SharedPointer_RoboticsCorner
{
    void shared_ptr_main1();
    void shared_ptr_main2();
    void shared_ptr_main3();
    void shared_ptr_main4();
};

/*  =============================================================================================================
                                                Implementations
    =============================================================================================================   */

void Examples_SharedPointer_RoboticsCorner::shared_ptr_main1()
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

void Examples_SharedPointer_RoboticsCorner::shared_ptr_main2()
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

void Examples_SharedPointer_RoboticsCorner::shared_ptr_main3()
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

void Examples_SharedPointer_RoboticsCorner::shared_ptr_main4()
{
    std::shared_ptr<Account> ptr1{new Account{"Mohamed"}};
    ptr1->Display();

    ptr1->deposit(1000);
    ptr1->withdraw(500);

    ptr1->Display();
} // Automatically delete.

/*  =============================================================================================================
                                                Header Gaurd File - Start
    =============================================================================================================   */
#endif /*_MODULE_SHARED_POINTER_ROBOTICS_CORNER_*/