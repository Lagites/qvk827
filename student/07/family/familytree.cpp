#include "familytree.hh"


Familytree::Familytree()
{

}

void Familytree::addNewPerson(const std::string &id, int height, std::ostream &output)
{
    shared_ptr<Person> new_ptr
            = make_shared<Person>(Person{id,height, {}, {}});

    if(persons.find(id) != persons.end()){
        output << "Error. " << id <<" already added." << endl;
        return;
    }
    persons[new_ptr->id_] = new_ptr;
}

void Familytree::addRelation(const std::string &child, const std::vector<std::string> &parents, std::ostream &output)
{
    auto iter = persons.find(child);
    if(iter != persons.end()){
        int i = 0;
        for(const string &parent : parents){
            auto iter2 = persons.find(parent);
            if(iter2 != persons.end()){
                iter->second->parents_.assign(i,iter2->second.get());
                iter2->second->children_.push_back(iter->second.get());
            }
        }
    }
    else{
        printNotFound(child,output);
    }
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
    string id = params[0];
    IdSet children = {};
    auto iter = persons.find(id);
    if(iter == persons.end()){
        printNotFound(id,output);
        return;
    }
    else{
        for(Person* child : iter->second->children_){
            children.insert(child->id_);
        }
    }
    printGroup(id, "children", children, output);
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
    return persons.find(id)->second.get();
}

void Familytree::printNotFound(const std::string &id, std::ostream &output) const
{
   output << "Error. " << id <<" not found." << endl;
}

IdSet Familytree::vectorToIdSet(const std::vector<Person *> &container) const
{
    IdSet set;
    for(Person *person : container){
        set.insert(person->id_);
    }
    return set;
}

void Familytree::printGroup(const std::string &id, const std::string &group, const IdSet &container, std::ostream &output) const
{
    if(container.size() == 0){
        output << id << " has no " << group << endl;
        return;
    }

    output << id << " has " << container.size() << " " << group << ":" << endl;

    for(string content : container){
        output << content << endl;
    }
}
