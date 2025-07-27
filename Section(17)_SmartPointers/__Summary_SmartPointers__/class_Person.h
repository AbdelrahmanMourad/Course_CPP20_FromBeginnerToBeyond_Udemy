/*  =============================================================================================================
                                                Header Gaurd File - Start
    =============================================================================================================   */
#ifndef _CLASS_PERSON_
#define _CLASS_PERSON_

/*  =============================================================================================================
                                                Included libraries
    =============================================================================================================   */
#include <iostream>
#include <memory> // Smart Pointers.
#include <vector> // vectors.

/*  =============================================================================================================
                                                Declarations / Implementations
    =============================================================================================================   */
//________typedef________
typedef std::shared_ptr<Employee> Emp_Ptr_t;
typedef std::vector<Emp_Ptr_t> Emp_Vec_t;

//________class_forward_declarations________
class Person;
class Employee;
class Department;

//________class_definition________
class Person
{
public:
    virtual ~Person() {}
};

class Employee : public Person
{
public:
    std::shared_ptr<Department> Department;
    ~Employee() { std::cout << "Destructor Called: Employee.\n"; }
};

class Department
{
    // Logic: Department is the actual OWNER
public:
    Emp_Vec_t Employees;
    ~Department() { std::cout << "Destructor Called: Department.\n"; }
};

/*  =============================================================================================================
                                                Header Gaurd File - End
    =============================================================================================================   */
#endif /*_CLASS_PERSON_*/