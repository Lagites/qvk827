#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main()
{
    string inputFile;
    string outputFile;
    cout << "Input file: ";
    cin >> inputFile;
    cout << "Output file: ";
    cin >> outputFile;

    ifstream reader(inputFile);
    if(!reader){
        cout << "Error! The file " << inputFile << " cannot be opened." << endl;
        return EXIT_FAILURE;
    }
    else{
        ofstream writer(outputFile);
        string line;
        int i = 1;
        while(getline(reader,line)){
            writer << i << " " << line << endl;
            i++;
        }
        reader.close();
        writer.close();
    }

    return EXIT_SUCCESS;
}
