#include <iostream>

using namespace std;

int main()
{
    string text;
    string search;
    string results = "";
    string::size_type index = 0;

    cout << "Enter a (longer) string: ";
    cin >> text;
    cout << "Enter a (shorter) string to be found: ";
    cin >> search;

    while (true){
        index = text.find(search, index);
        if(index != string::npos)
            results = results + to_string(index)+ ", ";
        else
            break;
        index++;
    };
    if(results.length() == 0)
        cout << "Not found" << endl;
    else
        cout << "Found at " << results.erase(results.length() - 2) << endl;

    return 0;
}
