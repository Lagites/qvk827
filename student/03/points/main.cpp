#include <iostream>
#include <fstream>
#include <map>
#include <string>

using namespace std;

int main()
{
    string inputFile;
    cout << "Input file: ";
    cin >> inputFile;

    ifstream reader(inputFile);
    if(!reader){
        cout << "Error! The file " << inputFile << " cannot be opened." << endl;
        return EXIT_FAILURE;
    }
    string line;
    string::size_type index = 0;
    map<string,int> points = {};
    map<string,int>::iterator iter;

    while(getline(reader,line)){
        index  = line.find(":");
        if(index != std::string::npos){
            string name = line.substr(0,index);
            iter = points.find(name);
            if(iter == points.end()){
                points.insert({name, stoi(line.substr(index + 1,line.length() - index))});
            }
            else{
                points.at(name) = points.at(name) + stoi(line.substr(index + 1,line.length() - index));
            }
        }
    }

    cout << "Final scores:" << endl;
    iter = points.begin();
    while(iter != points.end()){
        cout << iter->first << ": " << iter->second << endl;
        iter++;
    }

    reader.close();
    return EXIT_SUCCESS;
}
