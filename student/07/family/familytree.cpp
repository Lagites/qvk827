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
    Person* person = getPointer(child);
    if(person != nullptr){
        int i = 0;
        for(const string &parentId : parents){
            Person* parent = getPointer(parentId);
            if(parent != nullptr){
                person->parents_.push_back(parent);
                parent->children_.push_back(person);
                i++;
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
    Person* person = getPointer(id);
    if(person == nullptr){
        printNotFound(id,output);
        return;
    }

    for (Person* child : person->children_ )
        children.insert(child->id_);

    printGroup(id, "children", children, output);
}

void Familytree::printParents(Params params, std::ostream &output) const
{
    string id = params[0];
    IdSet parents = {};
    Person* person = getPointer(id);
    if(person == nullptr){
        printNotFound(id,output);
        return;
    }
    for (Person* parent : person->parents_ )
        parents.insert(parent->id_);
    printGroup(id, "parents", parents, output);
}

void Familytree::printSiblings(Params params, std::ostream &output) const
{
    string id = params[0];
    IdSet siblings = {};
    Person* person = getPointer(id);
    if(person == nullptr){
        printNotFound(id,output);
        return;
    }
    for (Person* parent : person->parents_ ){
        for (Person* sibling : parent->children_)
            siblings.insert(sibling->id_);

    }

    //Remove self from list
    siblings.erase(id);
    printGroup(id, "siblings", siblings, output);
}

void Familytree::printCousins(Params params, std::ostream &output) const
{
    string id = params[0];
    IdSet cousins = {};
    Person* person = getPointer(id);
    if(person == nullptr){
        printNotFound(id,output);
        return;
    }
    for (Person* grandParent : getParents(person, 1) ){
        for (Person* grandChild : getChildren(grandParent, 1))
            //Filter out siblings (relatives with same parents).
            if(person->parents_.at(0)->id_.compare(grandChild->parents_.at(0)->id_) != 0)
                cousins.insert(grandChild->id_);
    }

    printGroup(id, "cousins", cousins, output);
}

void Familytree::printTallestInLineage(Params params, std::ostream &output) const
{

}

void Familytree::printShortestInLineage(Params params, std::ostream &output) const
{

}

void Familytree::printGrandChildrenN(Params params, std::ostream &output) const
{
    string id = params[0];
    int n = stoi(params.at(1));
    string greats = "";
    IdSet parents = {};
    Person* person = getPointer(id);
    if(person == nullptr){
        printNotFound(id,output);
        return;
    }
    if(n < 1){
        printLevelError(output);
        return;
    }
    for (Person* grandChild : getChildren(person, n) )
        parents.insert(grandChild->id_);
    for(int i = 0 ; i < n - 1; i ++)
        greats.append("great-");
    printGroup(id, greats + "grandchildren", parents, output);
}

void Familytree::printGrandParentsN(Params params, std::ostream &output) const
{
    string id = params[0];
    int n = stoi(params.at(1));
    string greats = "";
    IdSet parents = {};
    Person* person = getPointer(id);
    if(person == nullptr){
        printNotFound(id,output);
        return;
    }
    if(n < 1){
        printLevelError(output);
        return;
    }
    for (Person* grandParent : getParents(person, n) )
        parents.insert(grandParent->id_);
    for(int i = 0 ; i < n - 1; i ++)
        greats.append("great-");
    printGroup(id, greats + "grandparents", parents, output);
}

Person *Familytree::getPointer(const std::string &id) const
{
    if(persons.find(id) != persons.end())
        return persons.find(id)->second.get();
    return nullptr;
}

void Familytree::printNotFound(const std::string &id, std::ostream &output) const
{
   output << "Error. " << id <<" not found." << endl;
}

void Familytree::printLevelError(std::ostream &output) const
{
   output << "Error. Level can't be less than 1." << endl;
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

    for(const string& content : container){
        output << content << endl;
    }
}

vector<Person *> Familytree::getChildren(Person *person, int level) const
{
    if(level == 0)
        return person->children_;
    vector<Person *> children = {};
    for(Person* child : person->children_){
        for(Person* grandChild : getChildren(child, level - 1)){
            children.push_back(grandChild);
        }
    }
    return children;
}

vector<Person *> Familytree::getParents(Person *person, int level) const
{
    if(level == 0)
        return person->parents_;
    vector<Person *> parents = {};
    for(Person* parent : person->parents_){
        for(Person* grandParent : getParents(parent, level - 1)){
            parents.push_back(grandParent);
        }
    }
    return parents;
}
