/*  =============================================================================================================
                                                Header Gaurd File - Start
    =============================================================================================================   */
#ifndef _MODULE_SHARED_POINTER_DR_MUSTAFA_SAAD_
#define _MODULE_SHARED_POINTER_DR_MUSTAFA_SAAD_

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
                                                Summary - Shared Pointers
    =============================================================================================================

    ● It owns the object it points to but it allows for multiple references.

    ● As a result: Both copy constructor and assignment operator are enabled

    ● Memory cleaning
        ○ When every reference goes out of the scope, the pointer is deleted

    ● Reference Counting:
        ○ There is an internal counter with number of references for the shared data
        ○ With every new pointer: counter++
        ○ With every shared pointer out of scope/deleted: counter-
        ○ Once counter = 0 ⇒ No one points to it ⇒ safe automatic removal

    ● Functionalities
        ○ Overall, very close to unique pointer, but less restrictive in references

    =============================================================================================================
*/

/*  =============================================================================================================
                                                Declarations
    =============================================================================================================   */
namespace Examples_SharedPointer_DrMustafaSaad
{
    void shared_ptr_main00_Creation(void);
    void shared_ptr_main01_Shared_Count(void);
    void shared_ptr_main02_Shared_with_Vectors(void);
    void shared_ptr_main03_DownCasting_Shared_vs_Unique(void);
    void shared_ptr_main04_Concurrency_ADVANCED(void);
    void shared_ptr_main05_Misc(void);
    void shared_ptr_main06_GuessTheOutput(void);
};

namespace PrivateHelpingfunctions
{
    void go1(std::shared_ptr<int> p1 /*Copy*/) { std::cout << p1.use_count() << "\n"; }
    void go2(std::shared_ptr<int> &p1 /*Move*/) { std::cout << p1.use_count() << "\n"; }
};

/*  =============================================================================================================
                                                Implementations
    =============================================================================================================   */
void Examples_SharedPointer_DrMustafaSaad::shared_ptr_main00_Creation(void)
{
    std::shared_ptr<int> p1{new int{20}}; // Declare and init shared_ptr.

    // std::shared_ptr<int> p1 = new int{20}; // CE
    // p1 = new int{30};                      // CE

    std::shared_ptr<int> p2{p1}; // OK: Copy Constructor not deleted and allowed.

    std::shared_ptr<int> p3; // OK: delcare without initialize.
    p3 = p2;                 // OK: Assignment allowed.
    *p1 = 5;                 // OK: dereference operator operloaded.

    // *p1= 5    *p2= 5   *p3=5 :   SAME VALUE
    std::cout << "*p1= " << *p1 << "\t*p2= " << *p2 << "\t*p3= " << *p3 << std::endl;

    auto p4 = std::make_shared<int>(20); /************* PREFERRED *************/
}

void Examples_SharedPointer_DrMustafaSaad::shared_ptr_main01_Shared_Count(void)
{
    std::shared_ptr<int> p1{new int{20}};
    std::cout << p1.use_count() << "\n"; // 1

    std::shared_ptr<int> p2{p1};
    std::cout << p1.use_count() << " " << p2.use_count() << "\n"; //  2   2

    { // _____________Inner scope: start_____________
        std::shared_ptr<int> p3;
        p3 = p2; // Create 3rd instace inside the scope

        std::cout << p1.use_count() << " " << p3.use_count() << "\n"; //  3   3

        PrivateHelpingfunctions::go1(p2);    // copy: 4 inside go1, after scope drop again to 3
        std::cout << p2.use_count() << "\n"; // 3

        PrivateHelpingfunctions::go2(p2);    // move: 3 inside go2, after scope remains to 3
        std::cout << p2.use_count() << "\n"; // 3

        /******* Go Out of scope: ""count--"" *******/
    } // _____________Inner scope: end_____________

    std::cout << p1.use_count() << " " << p2.use_count() << "\n"; //  2   2
    p1 = nullptr;
    std::cout << p2.use_count() << "\n"; // 1
    // p2 goes out of scope: original memory is deallocated.
}

void Examples_SharedPointer_DrMustafaSaad::shared_ptr_main02_Shared_with_Vectors(void)
{
    typedef std::shared_ptr<int> IntPtr;

    IntPtr p1{new int{20}};
    std::cout << p1.use_count() << "\n"; //  1

    std::vector<IntPtr> vec;
    vec.push_back(p1);                   //  2
    vec.push_back(p1);                   //  3
    vec.push_back(p1);                   //  4
    std::cout << p1.use_count() << "\n"; //  4

    vec.clear();
    std::cout << p1.use_count() << "\n"; //  1
}

void Examples_SharedPointer_DrMustafaSaad::shared_ptr_main03_DownCasting_Shared_vs_Unique(void)
{
    // NOTE: ""Employee"" is child class of parent class ""Person"".

    std::shared_ptr<Person> base_shared = std::make_shared<Employee>();

    std::shared_ptr<Employee> child_1 = std::dynamic_pointer_cast<Employee>(base_shared);

    if (child_1)
    {
        std::cout << base_shared.use_count() << " " << child_1.use_count() << "\n"; //  2   2
    }

    // Also see: """static_pointer_cast()"""

    // No casting for unique, You have to do it with normal way.
    std::unique_ptr<Person> base_unique = std::make_unique<Employee>();
    Employee *child_2 = dynamic_cast<Employee *>(base_unique.get());
    // DON'T do this with shared_ptr. as reference counter don't increase.
}

void Examples_SharedPointer_DrMustafaSaad::shared_ptr_main04_Concurrency_ADVANCED(void)
{
    /*  ----------------------------------------------------------------------
        ●   You did not study concurrency now.
            ○   Come back to these links later relevant
                ■   link:   "https://www.modernescpp.com/index.php/c-core-guidelines-passing-smart-pointer"
                ■   link:   "https://stackoverflow.com/questions/9127816/stdshared-ptr-thread-safety-explained"
                ■   link:   "https://news.ycombinator.com/item?id=11698784"

        ● "shared_ptr" instance is guaranteed "thread-safe" when always used by "value"
            (copied/moved) across thread boundaries.

        ● All other uses, "shared_ptr&"" are unsafe across thread boundaries
            ○   E.g. with &, the reference count is not increased
            ○  Void do(shared pointer & p)
                ■  Do_something with p
                ■   Another thread does freed original shared pointer
                    -   But we still are doing something! But reference count became 0

        ----------------------------------------------------------------------
    */
}

void Examples_SharedPointer_DrMustafaSaad::shared_ptr_main05_Misc(void)
{
    /*  ----------------------------------------------------------------------
        Misc:
        -----
        ●   Use Make Shared / Make Unique
            ○   ONE dynamic memory allocations insteads of 2
                    "https://www.bfilipek.com/2013/02/smart-pointers-gotchas.html#makeshared"
            ○   Better handling for scenarios with memory leaks due to exceptions
                    "https://www.internalpointers.com/post/beginner-s-look-smart-pointers-modern-c"

        ●   Shared vs Unique
            ○   It depends on the context. Favors unique as much as possible
                ■   Shared is slower, others may corrupt your data, issues with threading
                ■   You might use unique + pass raw pointer for some objects who need a reference

        ●   Smart pointers vs Raw pointers
            ○   Raw pointers: hell to build exception-safe and free from memory leaks code
            ○   Smart pointers are a bit verbose but less error-prone code: over time you will get use to it
            ○   Performance wise:
                very_close: "http://blog.davidecoppola.com/2016/10/performance-of-raw-pointers-vs-smart-pointers-in-cpp/"

        ●   You must be smart in using smart pointers.

        ----------------------------------------------------------------------
    */
}

void Examples_SharedPointer_DrMustafaSaad::shared_ptr_main06_GuessTheOutput(void)
{
    /*
        ●   1) Guess the output
        ●   Let’s uncomment 24 => last line.
        ●   2) Guess the output
        ●   Run. Compare. Think
    */

    Emp_Ptr_t e = std::make_shared<Department>();

    std::shared_ptr<Department> d = std::make_shared<Department>();

    e->Department = d;

    // d->Employees.push_back(e);
}

/*  =============================================================================================================
                                                Header Gaurd File - Start
    =============================================================================================================   */
#endif /*_MODULE_SHARED_POINTER_DR_MUSTAFA_SAAD_*/
