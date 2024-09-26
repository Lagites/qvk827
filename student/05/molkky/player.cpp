#include "player.hh"

Player::Player()
{

}

Player::Player(std::string name)
{
    name_ = name;
    points_ = 0;
}

std::string Player::get_name() const {
    return name_;
}
int Player::get_points() const {
    std::cout << "Unit test debug: "<< name_ << " has points: " << points_ << std::endl;
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
    std::cout << "Unit test debug: "<< name_ << " has won: " << points_ << " " << (points_ == 50) << std::endl;
    return points_ == 50;
}
