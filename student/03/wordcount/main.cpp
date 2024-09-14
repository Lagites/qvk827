#include <iostream>
#include <fstream>
#include <map>
#include <set>
#include <string>

using namespace std;

struct lineData{
    int qty;
    set<int> lines;
};

void insertWord(map<string,lineData>& words, string word, int row){
    map<string,lineData>::iterator iter;
    iter = words.find(word);
    if(iter == words.end()){
        words.insert({word, lineData{1,{row}}});
    }
    else{
        if(iter->second.lines.find(row) == iter->second.lines.end()){
            iter->second.qty++;
            iter->second.lines.insert(row);
        }

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
    map<string,lineData> words = {};
    int row = 1;

    while(getline(reader,line)){
        string::size_type index = 0;
        string::size_type prevPos = 0;
        while(true){

            index  = line.find(" ",index);
            if(index != std::string::npos){
                string subStr = line.substr(prevPos,index - prevPos);
                insertWord(words,subStr,row);
                index++;
                prevPos = index;
            }
            else{
                std::string subStr = line.substr(prevPos,line.size() - prevPos);
                if(subStr.length() > 0)
                    insertWord(words,subStr,row);
                break;
            }
        }
        row++;
    }

    map<string,lineData>::iterator iter;
    iter = words.begin();
    while(iter != words.end()){
        string lines = "";
        for (int i: iter->second.lines) {
           lines.append(" " + to_string(i) + ",");
        }
        lines.pop_back();
        cout << iter->first << " " << iter->second.qty << ":" << lines <<  endl;
        iter++;
    }

    return EXIT_SUCCESS;
}
