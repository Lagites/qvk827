#include <iostream>
#ifndef RECURSIVE_FUNC
#define RECURSIVE_FUNC
#endif

using namespace std;

void print_vertical(unsigned int num)
{
    RECURSIVE_FUNC
    // Do not remove RECURSIVE_FUNC declaration, it's necessary for automatic testing to work
    // ------------

    /*
    string str = to_string(num);
    cout << str.substr(0,1) << endl;
    if(str.size() > 1)
        print_vertical(stoi(str.substr(1,str.length() - 1)));
    */
    if(num > 9)
        print_vertical(num / 10);
    cout << num % 10 << endl;
}

// Do not modify rest of the code, or the automated testing won't work.
#ifndef UNIT_TESTING
int main()
{
    unsigned int number = 0;
    cout << "Enter a number: ";
    cin >> number;
    cout << "The given number (" << number << ") written vertically:" << endl;
    print_vertical(number);
    return 0;
}
#endif
