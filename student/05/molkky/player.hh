#ifndef PLAYER_HH
#define PLAYER_HH
#include <iostream>

class Player
{
public:
    Player();
    Player(std::string name);
    std::string get_name() const;
    int get_points() const;
    void add_points(int points);
    bool has_won() const;
private:
    std::string name_;
    int points_;

};

#endif // PLAYER_HH
