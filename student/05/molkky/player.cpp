#include "player.hh"

Player::Player()
{

}

Player::Player(std::string name)
{
    name_ = name;
}

std::string Player::get_name(){
    return name_;
}
int Player::get_points(){
    return points_;
}

void Player::add_points(int points){
    points_ = points_ + points;
    if(points_ > 50)
        points_ = 25;
}

bool Player::has_won(){
    return points_ == 50;
}
