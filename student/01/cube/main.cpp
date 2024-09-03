#include <iostream>

using namespace std;

int main()
{
    int number;
    cout << "Enter a number: ";
    cin >> number;
    int cubed = number * number * number;
    if(cubed / number / number != number )
        cout << "Error! The cube of " << number << " is not " << cubed << "." << endl;
    else
        cout << "The cube of " << number << " is " << cubed << "." << endl;
    return 0;
}
