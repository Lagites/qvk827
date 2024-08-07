#include "cards.hh"
#include <iostream>

using namespace std;

int main()
{
    Cards deck; // constructor is called

    int n = 0;
    cout << "Enter amount of test cards: ";
    cin >> n;

    cout << endl << "print_from_top_to_bottom (deck is empty)" << endl;
    deck.print_from_top_to_bottom(cout);

    cout << endl << "add * n" << endl;
    for(int i = 0; i < n; i++)
    {
        deck.add(i);
    }

    cout << endl << "print_from_top_to_bottom" << endl;
    deck.print_from_top_to_bottom(cout);

    cout << endl << "top_to_bottom * 2" << endl;
    deck.top_to_bottom();
    deck.top_to_bottom();

    cout << endl << "print_from_top_to_bottom" << endl;
    deck.print_from_top_to_bottom(cout);

    cout << endl << "top_to_bottom * 1" << endl;
    deck.top_to_bottom();

    cout << endl << "print_from_top_to_bottom" << endl;
    deck.print_from_top_to_bottom(cout);

    cout << endl << "print_from_bottom_to_top" << endl;
    deck.print_from_bottom_to_top(cout);

    cout << endl << "reverse" << endl;
    deck.reverse();

    cout << endl << "print_from_bottom_to_top" << endl;
    deck.print_from_bottom_to_top(cout);

    cout << endl;
    int value = 0;
    while(deck.remove(value))
    {
        cout << "remove " << value << endl;
    }

    // Destructor is called automatically
    return EXIT_SUCCESS;
}
