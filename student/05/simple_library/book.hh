#ifndef BOOK_HH
#define BOOK_HH
#include <iostream>
#include "date.hh"

class Book
{
public:
    Book();
    Book(std::string author, std::string name);

    void print() const;
    void loan(Date loanDate);
    void renew();
    void give_back();

private:

    std::string author_;
    std::string name_;
    bool loaned_;
    Date loanDate_;
    Date returnDate_;
};

#endif // BOOK_HH
