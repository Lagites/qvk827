#include <iostream>
#include "cards.hh"
#include <memory>

using namespace std;

Cards::Cards(): top_(nullptr)
{
    std::cout << "constructor" << std::endl;
}

Cards::~Cards()
{
    std::cout << "destructor" << std::endl;
}

void Cards::add(int id)
{
    shared_ptr<Card_data> new_ptr
            = make_shared<Card_data>(Card_data{id, nullptr});

    if ( top_ == nullptr ) {
        top_ = new_ptr;
    } else {
        new_ptr->next = top_;
        top_ = new_ptr;
    }
}

bool Cards::remove(int &id)
{
    if( top_ == nullptr)
            return false;
    id = top_->data;
    top_ = top_->next;
    return true;
}

void Cards::print_from_top_to_bottom(std::ostream &s)
{
    shared_ptr<Card_data> printable_ptr = top_;
    int running_number = 1;

    while ( printable_ptr != nullptr ) {
        s << running_number << ": "
             << printable_ptr->data << endl;
        ++running_number;
        printable_ptr = printable_ptr->next;
    }
}

void Cards::print_from_bottom_to_top(std::ostream &s)
{
    s << endl;
}

bool Cards::top_to_bottom()
{
    if(top_ == nullptr || top_->next == nullptr)
        return false;
    shared_ptr<Card_data> next_top = top_->next;
    shared_ptr<Card_data> running_ptr = top_;
    while ( running_ptr->next != nullptr ) {
        running_ptr = running_ptr->next;
    }
    running_ptr->next = top_;
    top_->next = nullptr;
    top_ = next_top;
    return true;
}

void Cards::reverse()
{
    shared_ptr<Card_data> running_ptr = top_->next;
    top_->next = nullptr;
    while ( running_ptr != nullptr ) {
        shared_ptr<Card_data> old_top_ptr = top_;
        top_ = running_ptr;
        running_ptr = running_ptr->next;
        top_->next = old_top_ptr;
    }

}

int Cards::recursive_print(std::shared_ptr<Card_data> top, std::ostream &s)
{
    s << top->data << endl;
    return 1;
}
