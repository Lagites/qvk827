#include "queue.hh"
#include "iostream"

using namespace std;

Queue::Queue(unsigned int cycle)
{
    cycle_ = cycle;
}

void Queue::enqueue(const string &reg)
{
    if(is_green_){
        cout << "GREEN: The vehicle " << reg <<" need not stop to wait";
        return;
    }

    shared_ptr<Vehicle> new_ptr
            = make_shared<Vehicle>(Vehicle{reg, nullptr});    

    if ( first_ == nullptr ) {
        first_ = new_ptr;
        last_ = new_ptr;
    } else {
        last_->next = new_ptr;
        last_ = new_ptr;
    }
}

void Queue::switch_light()
{
    if(is_green_){
        is_green_ = false;
        cout << "RED: ";
    }

    else{
        is_green_ = true;
        cout << "GREEN: ";
    }

    if(first_ == nullptr)
        cout << "No vehicles waiting in traffic lights" << endl;
    else{
        shared_ptr<Vehicle> car_ptr = first_;
        int running_number = cycle_;
        cout << "Vehicle(s) ";
        while(running_number > 0 && car_ptr != nullptr){
            car_ptr = first_->next;
            cout << first_->reg_num << " ";
            first_->next = nullptr;
            first_ = car_ptr;
            running_number--;
        }
        cout << "can go on";
        is_green_ = false;
    }
}

void Queue::reset_cycle(unsigned int cycle)
{
    cycle_ = cycle;
}

void Queue::print() const
{
    if(is_green_)
        cout << "GREEN: ";
    else
        cout << "RED: ";

    if(first_ == nullptr)
        cout << "No vehicles waiting in traffic lights" << endl;
    else{
        cout << "Vehicle(s) ";
        shared_ptr<Vehicle> printable_ptr = first_;

        while ( printable_ptr != nullptr ) {
            cout << printable_ptr->reg_num << " ";
            printable_ptr = printable_ptr->next;
        }
        cout << "waiting in traffic lights" << endl;
    }
}
