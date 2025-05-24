#include <iostream>

class Player
{
private:
    std::string name;
    int health;
    int xp;

public:
    // Copy Constructor
    Player(const Player &source) : name(source.name), health(source.health), xp(source.xp)
    {
        std::cout << "Copy constructor made a copy of " << source.name << std::endl;
    }
    Player(const Player &source);
};

//  Type::Type (const Type &source)
// {
//     //Code or initialization list to copy the object
// }

Player::Player(const Player &source): name{source.name},health{source.health},xp{source.xp}{}
