#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

const std::string HELP_TEXT = "S = store id1 i2\nP = print id\n"
                              "C = count id\nD = depth id\n";

struct Person{
    std::string id;
    std::vector<Person> persons;
};



std::vector<std::string> split(const std::string& s,
                               const char delimiter,
                               bool ignore_empty = false)
{
    std::vector<std::string> result;
    std::string tmp = s;

    while(tmp.find(delimiter) != std::string::npos)
    {
        std::string new_part = tmp.substr(0, tmp.find(delimiter));
        tmp = tmp.substr(tmp.find(delimiter) + 1, tmp.size());
        if(not (ignore_empty and new_part.empty()))
        {
            result.push_back(new_part);
        }
    }
    if(not (ignore_empty and tmp.empty()))
    {
        result.push_back(tmp);
    }
    return result;
}

bool addPerson(std::vector<Person>& persons, std::string target, std::string user){
    std::vector<Person>::iterator iter = persons.begin();
    while(iter != persons.end()){
        if(iter->id.compare(target) == 0){
            iter->persons.push_back(Person{user,{}});
            return true;
        }

        if(addPerson(iter->persons,target,user))
            return true;
        iter++;
    }
    return false;
}

void printPersons(std::vector<Person>& persons, std::string target, std::string dots){
    std::vector<Person>::iterator iter = persons.begin();
    while(iter != persons.end()){
        if(iter->id.compare(target) == 0){
            std::cout << dots << iter->id << std::endl;
            printPersons(iter->persons,"",dots + "..");
            return;
        }
        else if(target.compare("") == 0){
            std::cout << dots << iter->id << " " << std::endl;
            printPersons(iter->persons,"",dots + "..");
        }
        else
            printPersons(iter->persons,target,dots);
        iter++;
    }
}

void countPersons(std::vector<Person>& persons, std::string target, int& qty){
    std::vector<Person>::iterator iter = persons.begin();
    while(iter != persons.end()){
        if(iter->id.compare(target) == 0){
            countPersons(iter->persons,"",qty);
            return;
        }
        else if(target.compare("") == 0){
            qty++;
            countPersons(iter->persons,"",qty);
        }
        else
            countPersons(iter->persons,target,qty);
        iter++;
    }
}

int depthPersons(std::vector<Person>& persons, std::string target, int depth){
    std::vector<Person>::iterator iter = persons.begin();
    int tempDepth = depth;
    if(target.compare("") == 0 && iter != persons.end())
        depth++;
    while(iter != persons.end()){
        if(iter->id.compare(target) == 0){
            depth++;
            depth = depthPersons(iter->persons,"",depth);
            return depth;
        }
        else if(target.compare("") == 0){
            int newDepth = depthPersons(iter->persons,"",depth);
            if(newDepth > tempDepth)
                tempDepth = newDepth;
        }
        else
            depth = depthPersons(iter->persons,target,depth);
        iter++;
    }
    if(tempDepth > depth)
        return tempDepth;
    return depth;
}


int main()
{
    std::vector<Person> persons = {};


    while(true)
    {
        std::string line;
        std::cout << "> ";
        getline(std::cin, line);
        std::vector<std::string> parts = split(line, ' ', true);

        // Allowing empty inputs
        if(parts.size() == 0)
        {
            continue;
        }

        std::string command = parts.at(0);

        if(command == "S" or command == "s")
        {
            if(parts.size() != 3)
            {
                std::cout << "Erroneous parameters!" << std::endl << HELP_TEXT;
                continue;
            }
            std::string id1 = parts.at(1);
            std::string id2 = parts.at(2);

            if(!addPerson(persons, id1, id2)){
                persons.push_back(Person{id1, {Person{id2,{}}}});
            }

        }
        else if(command == "P" or command == "p")
        {
            if(parts.size() != 2)
            {
                std::cout << "Erroneous parameters!" << std::endl << HELP_TEXT;
                continue;
            }
            std::string id = parts.at(1);

            printPersons(persons, id, "");

        }
        else if(command == "C" or command == "c")
        {
            if(parts.size() != 2)
            {
                std::cout << "Erroneous parameters!" << std::endl << HELP_TEXT;
                continue;
            }
            std::string id = parts.at(1);

            int qty = 0;
            countPersons(persons, id, qty);
            std::cout << qty << std::endl;

        }
        else if(command == "D" or command == "d")
        {
            if(parts.size() != 2)
            {
                std::cout << "Erroneous parameters!" << std::endl << HELP_TEXT;
                continue;
            }
            std::string id = parts.at(1);

            int depth = depthPersons(persons, id, 0);
            std::cout << depth << std::endl;

        }
        else if(command == "Q" or command == "q")
        {
           return EXIT_SUCCESS;
        }
        else
        {
            std::cout << "Erroneous command!" << std::endl << HELP_TEXT;
        }
    }
}
