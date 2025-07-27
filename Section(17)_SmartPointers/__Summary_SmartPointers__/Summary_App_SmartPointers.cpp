/*  =============================================================================================================
                                                Included libraries
    =============================================================================================================   */
/*Classes*/
#include "class_smart_pointers_my_implementation.h
#include "class_Account.h"
#include "class_Player.h"
/*Modules*/
#include "module_unique_ptr_DrMustafaSaad.h"
#include "module_unique_ptr_RoboticsCorner.h"
#include "module_shared_ptr_RoboticsCorner.h"
/*Libraries*/
#include <iostream>   // IO Stream.
#include <memory>     // Smart pointers.
#include <vector>     // Vectors.
#include <functional> // Lambdas.

/*  =============================================================================================================
                                                Declarations
    =============================================================================================================   */

/*  =============================================================================================================
                                            unique_ptr
    =============================================================================================================   */

/*  =============================================================================================================
                                                shared_ptr
    =============================================================================================================   */

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
    Examples_UniquePointer_DrMustafaSaad::unique_ptr_main00_Creation();
    Examples_UniquePointer_DrMustafaSaad::unique_ptr_main01_CopyConstructor_vs_Moving();
    Examples_UniquePointer_DrMustafaSaad::unique_ptr_main02_Addresses();
    Examples_UniquePointer_DrMustafaSaad::unique_ptr_main03_PassToFunction();
    Examples_UniquePointer_DrMustafaSaad::unique_ptr_main04_ReturnFromFunction();
    Examples_UniquePointer_DrMustafaSaad::unique_ptr_main05_HelperFunction();
    Examples_UniquePointer_DrMustafaSaad::unique_ptr_main06_PointerToArrayAndLeaks();
    Examples_UniquePointer_DrMustafaSaad::unique_ptr_main07_PointerWithVectors();
    Examples_UniquePointer_DrMustafaSaad::unique_ptr_main08_Release_Reset_MemoryLeaks();
    Examples_UniquePointer_DrMustafaSaad::unique_ptr_main09_warning_MemoryLeaks();
    Examples_UniquePointer_DrMustafaSaad::unique_ptr_main10_BehindTheSeen();

    Examples_UniquePointer_RoboticsCorner::unique_ptr_main1_Creation_using_new();               //// init by new, reset(), use_count()
    Examples_UniquePointer_RoboticsCorner::unique_ptr_main2_Creation_using_make_unique();       //// init by std::make_shared<>(), init by copy constructor, init by assignment operator=
    Examples_UniquePointer_RoboticsCorner::unique_ptr_main3_ptr2class();                        //// Ptr 2 user defined type/class.
    Examples_UniquePointer_RoboticsCorner::unique_ptr_main4_ptr_vector_move_not_copy();         //// vector if shared pointers.
    Examples_UniquePointer_RoboticsCorner::unique_ptr_main5_Creation_class_using_make_unique(); //// user defined classes.

    /*___________shared_ptr___________*/
    Examples_SharedPointer_RoboticsCorner::shared_ptr_main1(); // init by new, reset(), use_count()
    Examples_SharedPointer_RoboticsCorner::shared_ptr_main2(); // init by std::make_shared<>(), init by copy constructor, init by assignment operator=
    Examples_SharedPointer_RoboticsCorner::shared_ptr_main3(); // vector if shared pointers.
    Examples_SharedPointer_RoboticsCorner::shared_ptr_main4(); // user defined classes.

    /*___________weak_ptr___________*/

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