/*  =============================================================================================================
                                                Header Gaurd File - Start
    =============================================================================================================   */
#ifndef _CLASS_ACCOUNT_
#define _CLASS_ACCOUNT_

/*  =============================================================================================================
                                                Included libraries
    =============================================================================================================   */
#include <iostream>

/*  =============================================================================================================
                                                Declarations / Implementations
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


/*  =============================================================================================================
                                                Header Gaurd File - End
    =============================================================================================================   */
#endif /*_CLASS_ACCOUNT_*/