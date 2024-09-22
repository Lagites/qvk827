#include "player.hh"

Player::Player()
{

}

Player::Player(std::string name)
{

}

std::string Player::get_name(){
    return name_;
}
int Player::get_points(){
    return points_;
}

void Player::add_points(int points){

}

bool Player::has_won(){
    return true;
}
