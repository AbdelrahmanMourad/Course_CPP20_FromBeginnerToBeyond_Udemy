// Section 13
// Delegating Constructors
#include <iostream>
#include <string>

using namespace std;

class Player
{
private:
    std::string name;
    int health;
    int xp;

public:
    // Overloaded Constructors
    Player();
    Player(std::string name_val);
    Player(std::string name_val, int health_val, int xp_val);
    void PrintPlayer(void);
};

Player::Player() : Player{"None", 0, 0}
{
    cout << "No-args constructor" << endl;
}

Player::Player(std::string name_val) : Player{name_val, 0, 0}
{
    cout << "One-arg constructor" << endl;
}

Player::Player(std::string name_val, int health_val, int xp_val) /*Delegeation*/ : name{name_val}, health{health_val}, xp{xp_val}
{
    cout << "Three-args constructor" << endl;
}
void Player::PrintPlayer(void)
{
    std::cout << "Name= " << name << " \t,Health= " << health << "\t,xp= " << xp << std::endl;
}

int main()
{
    // Try all the constructors.
    Player empty;                       // Default Constructor.
    Player frank{"Frank"};              // Parameterized contstructor-1
    Player villain{"Villain", 100, 55}; // Paramterized constructor-2

    // Print each.
    empty.PrintPlayer();
    frank.PrintPlayer();
    villain.PrintPlayer();

    return 0;
}
