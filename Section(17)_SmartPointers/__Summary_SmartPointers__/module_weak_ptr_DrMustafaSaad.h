/*  =============================================================================================================
                                                Header Gaurd File - Start
    =============================================================================================================   */
#ifndef _MODULE_WEAK_POINTER_DR_MUSTAFA_SAAD_
#define _MODULE_WEAK_POINTER_DR_MUSTAFA_SAAD_

/*  =============================================================================================================
                                                Included libraries
    =============================================================================================================   */
#include "class_smart_pointers_my_implementation.h"
#include "class_Person.h"
#include <iostream>   // IO Stream.
#include <memory>     // Smart pointers.
#include <vector>     // Vectors.
#include <functional> // Lambdas.

/*  =============================================================================================================
                                                Summary - Weak Pointers
    =============================================================================================================




    =============================================================================================================
*/

/*  =============================================================================================================
                                                Declarations
    =============================================================================================================   */
namespace Examples_SharedPointer_DrMustafaSaad
{
    void weak_ptr_main00_GuessTheOutput(void);
    void weak_ptr_main01_UsingWeakPtrs(void);
    void weak_ptr_main02_Lock_And_Expired(void);
    void weak_ptr_main03_Concurrency_ADVANCED(void);
    void weak_ptr_main04_Proper_Usage_Weak_Pointers(void);
};

namespace PrivateHelpingfunctions
{

};

/*  =============================================================================================================
                                                Implementations
    =============================================================================================================   */
void Examples_SharedPointer_DrMustafaSaad::weak_ptr_main00_GuessTheOutput(void)
{

    Emp_Ptr_t e = std::make_shared<Employee>();
    std::shared_ptr<Department> d = std::make_shared<Department>();
    e->Department = d;
    d->Employees.push_back(e);

    // We are about to go out of scope.
    // e waiting for d destruction to be released.
    // d waiting for d destruction to be released.
    std::cout << e.use_count() << " " << d.use_count(); //  2   2

    /*  -------------------------------------------------
        ●   The core problem here is the "circular reference"
            ○   Employee has a department which has the employee
        ●   Sadly the reference count of both of them will remain > 0
            ○   Never released
            ○   Memory leak!
        ●   So?! Weak pointers
        -------------------------------------------------
    */

    /*  -------------------------------------------------
        ●   C++ tries to handle this severe issue with a weak pointer
        ●   It is pointer to a shared pointer
            ○   Counter of the shared pointer is NOT affected.
                ■   Then the cycle has no effect
                ■   img src: "https://media.geeksforgeeks.org/wp-content/uploads/Image_3.jpg"
            ○   Note cycle can be bigger: E.g. A ⇒ B ⇒ C ⇒ D ⇒ A

        -------------------------------------------------
    */
}
void Examples_SharedPointer_DrMustafaSaad::weak_ptr_main01_UsingWeakPtrs(void)
{
    // Step(1): Create a shared pointer.
    // Step(2): Create weak pointer from the shared pointer (Pointer to pointer).


    // 1) Create shared, 2) then assign/construct to weak ptr.
    std::shared_ptr<Employee> e = std::make_shared<Employee>();

    std::shared_ptr<Department> d = std::make_shared<Department>();

    e->Department = d; // Assign shared to weak.
    // e->Department = std::weak_ptr<Department>(d);   // OR

    d->Employees.push_back(e);

    // weak from weak
    std::weak_ptr<Department> d2 = std::weak_ptr<Department>(e->Department);
}
void Examples_SharedPointer_DrMustafaSaad::weak_ptr_main02_Lock_And_Expired(void)
{
}
void Examples_SharedPointer_DrMustafaSaad::weak_ptr_main03_Concurrency_ADVANCED(void)
{
}
void Examples_SharedPointer_DrMustafaSaad::weak_ptr_main04_Proper_Usage_Weak_Pointers(void)
{
}

/*  =============================================================================================================
                                                Header Gaurd File - Start
    =============================================================================================================   */
#endif /*_MODULE_WEAK_POINTER_DR_MUSTAFA_SAAD_*/
