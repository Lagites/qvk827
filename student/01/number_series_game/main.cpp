#include <iostream>


int main()
{
    std::cout << "How many numbers would you like to have? ";
    int numbers;
    std::cin >> numbers;
    for(int i = 0; i < numbers; i++){
        std::cout << i + 1 << std::endl;
    }

    return 0;
}
