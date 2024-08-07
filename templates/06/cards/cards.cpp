#include <iostream>
#include "cards.hh"

Cards::Cards(): top_(nullptr)
{
    std::cout << "constructor" << std::endl;
}

Cards::~Cards()
{
    std::cout << "destructor" << std::endl;
}
