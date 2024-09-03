#include <iostream>

using namespace std;

int main()
{
    cout << "Enter a temperature: ";
    double temp = 0;
    cin >> temp;
    cout << temp << " degrees Celsius is " <<  temp * 1.8 + 32 << " degrees Fahrenheit" << endl;

    return 0;
}
