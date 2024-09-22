#include "book.hh"

Book::Book()
{

}

Book::Book(std::string author, std::string name){
    author_ = author;
    name_ = name;
}

void Book::print() const
{
    std::cout << author_ << " " << name_ << std::endl;
}

void Book::loan(Date loanDate){

}

void Book::renew(){

}

void Book::give_back(){

}
