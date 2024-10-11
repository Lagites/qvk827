#include "familytree.hh"


Familytree::Familytree()
{

}

void Familytree::addNewPerson(const std::string &id, int height, std::ostream &output)
{
    shared_ptr<Person> new_ptr
            = make_shared<Person>(Person{id,height, {}, {}});

    persons[new_ptr->id_] = new_ptr;
}

void Familytree::addRelation(const std::string &child, const std::vector<std::string> &parents, std::ostream &output)
{

}

void Familytree::printPersons(Params, std::ostream &output) const
{
    auto iter = persons.begin();
    while(iter != persons.end()){
        output << iter->second->id_ << ", " << iter->second->height_ << endl;
        iter++;
    }
}

void Familytree::printChildren(Params params, std::ostream &output) const
{

}

void Familytree::printParents(Params params, std::ostream &output) const
{

}

void Familytree::printSiblings(Params params, std::ostream &output) const
{

}

void Familytree::printCousins(Params params, std::ostream &output) const
{

}

void Familytree::printTallestInLineage(Params params, std::ostream &output) const
{

}

void Familytree::printShortestInLineage(Params params, std::ostream &output) const
{

}

void Familytree::printGrandChildrenN(Params params, std::ostream &output) const
{

}

void Familytree::printGrandParentsN(Params params, std::ostream &output) const
{

}

Person *Familytree::getPointer(const std::string &id) const
{

}

void Familytree::printNotFound(const std::string &id, std::ostream &output) const
{

}

IdSet Familytree::vectorToIdSet(const std::vector<Person *> &container) const
{

}

void Familytree::printGroup(const std::string &id, const std::string &group, const IdSet &container, std::ostream &output) const
{

}
