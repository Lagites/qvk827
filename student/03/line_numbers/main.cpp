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
    ofstream writer(outputFile);
    if(!reader){
        cout << "Error! The file " << inputFile << " cannot be opened." << endl;
        return EXIT_FAILURE;
    }

    else{
        if(!writer){
            cout << "Error! The file " << outputFile << " cannot be opened." << endl;
            return EXIT_FAILURE;
        }
        else{
            string line;
            while(getline(reader,line)){
                writer << line << endl;
            }
        }

    }
    reader.close();
    writer.close();

    return 0;
}
