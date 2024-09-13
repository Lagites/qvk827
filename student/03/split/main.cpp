#include <iostream>
#include <string>
#include <vector>

std::vector< std::string > split(std::string& line, char separator, bool ignoreEmpty = false)
{
    std::vector< std::string > result = { };
    std::string::size_type index = 0;
    std::string::size_type prevPos = 0;
    while(true){
        index  = line.find(separator,index);
        if(index != std::string::npos){
            std::string subStr = line.substr(prevPos,index - prevPos);
            //std::cout << "index: " << index << " subStr " << subStr << " Size:" << subStr.size() <<  std::endl;
            if(!ignoreEmpty || subStr.size() > 0 )
                result.push_back(subStr);
        }
        else{
            std::string subStr = line.substr(prevPos,line.size() - prevPos);
            if(!ignoreEmpty || subStr.size() > 0 )
                result.push_back(subStr);
            break;
        }
        index++;
        prevPos = index;
    }
    line.find(separator);
    return result;
}

int main()
{
    std::string line = "";
    std::cout << "Enter a string: ";
    getline(std::cin, line);
    std::cout << "Enter the separator character: ";
    char separator = getchar();

    std::vector< std::string > parts  = split(line, separator);
    std::cout << "Splitted string including empty parts: " << std::endl;
    for( auto part : parts ) {
        std::cout << part << std::endl;
    }

    std::vector< std::string > parts_no_empty  = split(line, separator, true);
    std::cout << "Splitted string ignoring empty parts: " << std::endl;
    for( auto part : parts_no_empty ) {
        std::cout << part << std::endl;
    }
}
