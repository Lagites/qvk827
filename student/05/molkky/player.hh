#ifndef PLAYER_HH
#define PLAYER_HH
#include <iostream>

class Player
{
public:
    Player();
    Player(std::string name);
    std::string get_name();
    int get_points();
    void add_points(int points);
    bool has_won();
private:
    std::string name_;
    int points_;

};

#endif // PLAYER_HH
