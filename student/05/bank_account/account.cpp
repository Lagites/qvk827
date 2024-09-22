#include "account.hh"
#include <iostream>

Account::Account(const std::string& owner, bool has_credit)
{
    owner_ = owner;
    has_credit_ = has_credit;
    credit_limit_ = 0;
    money_ = 0;
    generate_iban();
}

// Setting initial value for the static attribute running_number_
int Account::running_number_ = 0;

void Account::generate_iban()
{
    ++running_number_;
    std::string suffix = "";
    if(running_number_ < 10)
    {
        suffix.append("0");
    }
    else if(running_number_ > 99)
    {
        std::cout << "Too many accounts" << std::endl;
    }
    suffix.append(std::to_string(running_number_));

    iban_ = "FI00 1234 ";
    iban_.append(suffix);
}

void Account::print() const{
    std::cout << owner_ << " : " << getIban() << " : " <<  money_ << " euros" << std::endl;
}

std::string Account::getIban() const{
    return iban_;
}

bool Account::set_credit_limit(int money){
    if(!has_credit_){
        std::cout << "Cannot set credit limit: the account has no credit card" << std::endl;
        return false;
    }
    credit_limit_ = 0 - money;
    return true;
}

bool Account::save_money(int money){
    money_ = money_ + money;
    return true;
}

bool Account::take_money(int money){
    if(money_ - money < credit_limit_){
        std::cout << "Cannot take money: balance underflow" << std::endl;
        return false;
    }
    money_ = money_ - money;
    std::cout << money << " euros taken: new balance of " << getIban() << " is " << money_ << " euros" << std::endl;
    return true;
}

bool Account::transfer_to(Account& account, int money){
    if(!take_money(money)){
        std::cout << "Transfer from " << getIban() << " failed" << std::endl;
        return false;
    }
    if(!account.save_money(money)){
        std::cout << "Transfer to " << account.getIban() << " failed" << std::endl;
        return false;
    }
    return true;
}
