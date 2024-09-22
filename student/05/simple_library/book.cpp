#include "book.hh"

Book::Book()
{
    author_ = "";
    name_ = "";
    loanDate_ = Date();
    returnDate_ = Date();
    loaned_ = false;
}

Book::Book(std::string author, std::string name){
    author_ = author;
    name_ = name;
    loanDate_ = Date();
    returnDate_ = Date();
    loaned_ = false;
}

void Book::print() const
{
    std::cout << author_ << " : " << name_ << std::endl;
    if(loaned_){
        std::cout << "- loaned: ";
        loanDate_.print();
        std::cout << "- to be returned: ";
        returnDate_.print();
    }
    else
        std::cout << "- available" << std::endl;
}

void Book::loan(Date loanDate){
    if(loaned_){
        std::cout << "Already loaned: cannot be loaned" << std::endl;
        return;
    }

    loanDate_ = loanDate;
    returnDate_ = loanDate;
    returnDate_.advance(28);
    loaned_ = true;

}

void Book::renew(){
    if(!loaned_){
        std::cout << "Not loaned: cannot be renewed" << std::endl;
        return;
    }
    returnDate_.advance(28);
}

void Book::give_back(){
    if(!loaned_){
        std::cout << "Not loaned: cannot be returned" << std::endl;
        return;
    }
    loaned_ = false;
}
