#include <iostream>

using namespace std;

int main()
{
    cout << "Enter a positive number: ";
    int number;
    cin >> number;
    if(number < 1){
        cout << "Only positive numbers accepted" <<  endl;
        return 0;
    }
    int firstResult = number;
    int secondResult = 1;
    int i = 1;
    int j = number;
    while(i <= j){
        if(j * i > number){
            j--;
            i = 1;
            continue;
        }
        if(j * i == number){
            firstResult = i;
            secondResult = j;
        }
        i++;
    }
    cout << number << " = " << firstResult << " * " << secondResult <<  endl;

    return 0;
}
