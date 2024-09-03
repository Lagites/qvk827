#include <iostream>

using namespace std;

unsigned long int calculateProbability(int allBalls, int drawnBalls);

unsigned long int getFactorial(unsigned long int value);

int main()
{    
    int allBalls;
    int drawnBalls;

    cout << "Enter the total number of lottery balls: ";
    cin >> allBalls;

    cout << "Enter the number of drawn balls: ";
    cin >> drawnBalls;

    if(allBalls < 1 || drawnBalls < 1){
        cout << "The number of balls must be a positive number." << endl ;
        return EXIT_FAILURE;
    }

    if(drawnBalls > allBalls){
        cout << "The maximum number of drawn balls is the total amount of balls." << endl ;
        return EXIT_FAILURE;
    }

    cout << "The probability of guessing all " << drawnBalls << " balls correctly is 1/" << calculateProbability(allBalls,drawnBalls) << endl ;

    return EXIT_SUCCESS;
}

unsigned long int calculateProbability(int allBalls, int drawnBalls) {
    //Oletetaan, että n on lottopelin kaikkien pallojen lukumäärä ja p arvottujen pallojen lukumäärä. Tällöin erilaisia lottorivejä on olemassa
    // n! / (n−p)!∗p!
    return getFactorial(allBalls) / (getFactorial(allBalls - drawnBalls) * getFactorial(drawnBalls));
}

//Kertoman kaava esim. 5!=1∗2∗3∗4∗5=120
unsigned long int getFactorial(unsigned long int value) {
    if(value == 0)
        return 1;
    unsigned long result = 1;
    for(unsigned long i = 1; i <= value; i++){
        result = result * i;
    }
    return result;
}
