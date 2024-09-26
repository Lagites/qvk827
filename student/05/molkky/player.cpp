#include "player.hh"

Player::Player()
{

}

Player::Player(std::string name)
{
    name_ = name;
}

std::string Player::get_name() const {
    return name_;
}
int Player::get_points() const {
    return points_;
}

void Player::add_points(int points){
    points_ = points_ + points;
    if(points_ > 50){
        points_ = 25;
        std::cout << name_ << " gets penalty points!" << std::endl;
    }

}

bool Player::has_won() const {
    return points_ == 50;
}
