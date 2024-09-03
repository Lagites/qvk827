#include <iostream>

using namespace std;

int main()
{
    string keytest = "abcdefghijklmnopqrstuvwzyx";
    string key;
    string text;
    string results = "";
    string::size_type asciiValuesAdded = 0;

    cout << "Enter the encryption key: ";
    //cin >> key;
    key = keytest;

    if(key.length() != 26){
        cout << "Error! The encryption key must contain 26 characters." << endl;
        return EXIT_FAILURE;
    }

    for(string::size_type i = 0 ; i < key.length() ; i++){
        char keychar = key.at(i);
        int asciiValue = static_cast< int >( keychar);
        if(asciiValue < 97 || asciiValue > 122){
            cout << "Error! The encryption key must contain only lower case characters." << endl;
            return EXIT_FAILURE;
        }
        asciiValuesAdded += asciiValue;
    }

    cout << "Asciisize: " << asciiValuesAdded << endl;

    //Tarkistetaan onko kaikki ascii-merkit mukana vertailemalla saatua summaa ascii-kirjainten yhteenlaskettuun summaan.
    if(asciiValuesAdded != 2847){
        cout << "Error! The encryption key must contain all alphabets a-z." << endl;
        return EXIT_FAILURE;
    }

    cout << "Enter the text to be encrypted: ";
    cin >> text;
    return 0;
}
