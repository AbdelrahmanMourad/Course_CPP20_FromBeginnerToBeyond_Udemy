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
    // Player() = default;
    // Player() = delete;
    Player();
    Player(std::string name_val);
    Player(std::string name_val, int health_val, int xp_val);
};

Player::Player() : /*Delegate Constructor*/ Player{"None", 0, 0} { cout << "No-args constructor" << endl; }

Player::Player(std::string name_val) : /*Delegate Constructor*/ Player{name_val, 0, 0} { cout << "One-arg constructor" << endl; }

Player::Player(std::string name_val, int health_val, int xp_val) : name{name_val}, health{health_val}, xp{xp_val} { cout << "Three-args constructor" << endl; }

int main()
{

    Player empty;
    Player frank{"Frank"};
    Player villain{"Villain", 100, 55};

    return 0;
}
