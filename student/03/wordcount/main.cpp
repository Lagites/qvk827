#include <iostream>
#include <fstream>
#include <map>
#include <string>

using namespace std;

void insertWord(map<string,int>& words, string word){
    map<string,int>::iterator iter;
    iter = words.find(word);
    if(iter == words.end()){
        words.insert({word, 1});
    }
    else{
        ++words.at(word);
    }
}

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
    map<string,int> words = {};

    while(getline(reader,line)){
        string::size_type index = 0;
        string::size_type prevPos = 0;
        while(true){

            index  = line.find(" ",index);
            if(index != std::string::npos){
                string subStr = line.substr(prevPos,index - prevPos);
                insertWord(words,subStr);
                index++;
                prevPos = index;
            }
            else{
                std::string subStr = line.substr(prevPos,line.size() - prevPos);
                if(subStr.length() > 0)
                    insertWord(words,subStr);
                break;
            }
        }
    }

    map<string,int>::iterator iter;
    iter = words.begin();
    while(iter != words.end()){
        cout << iter->first << ": " << iter->second << endl;
        iter++;
    }

    return EXIT_SUCCESS;
}
