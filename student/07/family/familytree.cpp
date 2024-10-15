#include "familytree.hh"


Familytree::Familytree()
{

}

void Familytree::addNewPerson(const std::string &id, int height, std::ostream &output)
{
    std::shared_ptr<Person> new_ptr
            = std::make_shared<Person>(Person{id,height, {}, {}});

    if(persons.find(id) != persons.end()){
        output << "Error. Person already added." << std::endl;
        return;
    }
    persons[new_ptr->id_] = new_ptr;
}

void Familytree::addRelation(const std::string &child, const std::vector<std::string> &parents, std::ostream &output)
{
    Person* person = getPointer(child);
    if(person != nullptr){
        int i = 0;
        //Loops parents-vector and parents to person and person as a child to each parent
        for(const std::string &parentId : parents){
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
        output << iter->second->id_ << ", " << iter->second->height_ << std::endl;
        iter++;
    }
}

void Familytree::printChildren(Params params, std::ostream &output) const
{
    std::string id = params[0];
    IdSet children = {};
    Person* person = getPointer(id);
    if(person == nullptr){
        printNotFound(id,output);
        return;
    }

    //collect ids of each child
    for (Person* child : person->children_ )
        children.insert(child->id_);

    printGroup(id, "children", children, output);
}

void Familytree::printParents(Params params, std::ostream &output) const
{
    std::string id = params[0];
    IdSet parents = {};
    Person* person = getPointer(id);
    if(person == nullptr){
        printNotFound(id,output);
        return;
    }

    //collect ids of each parent
    for (Person* parent : person->parents_ )
        parents.insert(parent->id_);

    printGroup(id, "parents", parents, output);
}

void Familytree::printSiblings(Params params, std::ostream &output) const
{
    std::string id = params[0];
    IdSet siblings = {};
    Person* person = getPointer(id);
    if(person == nullptr){
        printNotFound(id,output);
        return;
    }

    //loop through each parent's children
    for (Person* parent : person->parents_ ){
        //collect ids of each sibling
        for (Person* sibling : parent->children_)
            siblings.insert(sibling->id_);

    }

    //Remove self from list
    siblings.erase(id);
    printGroup(id, "siblings", siblings, output);
}

void Familytree::printCousins(Params params, std::ostream &output) const
{
    std::string id = params[0];
    IdSet cousins = {};
    Person* person = getPointer(id);
    if(person == nullptr){
        printNotFound(id,output);
        return;
    }

    //loop through each grandparench's grandchildren to find cousins
    for (Person* grandParent : getGrandParents(person, 1) ){
        //collect ids of each child
        for (Person* grandChild : getGrandChildren(grandParent, 1)){
            cousins.insert(grandChild->id_);
        }
    }

    //Filter out self and siblings (relatives with same parents).
    for (Person* parent : person->parents_ ){
        for (Person* child : parent->children_ ){
            cousins.erase(child->id_);
        }
    }

    printGroup(id, "cousins", cousins, output);
}

void Familytree::printTallestInLineage(Params params, std::ostream &output) const
{
    std::string id = params[0];
    std::string resultId = params[0];
    IdSet cousins = {};
    Person* person = getPointer(id);
    if(person == nullptr){
        printNotFound(id,output);
        return;
    }
    Person* tallestPerson = findChildByHeight(person,false,person);

    printComparison(id, tallestPerson->id_, "tallest", tallestPerson->height_, output);
}

void Familytree::printShortestInLineage(Params params, std::ostream &output) const
{
    std::string id = params[0];
    std::string resultId = params[0];
    IdSet cousins = {};
    Person* person = getPointer(id);
    if(person == nullptr){
        printNotFound(id,output);
        return;
    }
    Person* shortestPerson = findChildByHeight(person,true,person);

    printComparison(id, shortestPerson->id_, "shortest", shortestPerson->height_, output);
}

void Familytree::printGrandChildrenN(Params params, std::ostream &output) const
{
    std::string id = params[0];
    int n = stoi(params.at(1));
    std::string greats = "";
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

    //loop through each grandchildren in Nth generation and collect ids
    for (Person* grandChild : getGrandChildren(person, n) )
        parents.insert(grandChild->id_);
    //add great- to print function for each generation
    for(int i = 0 ; i < n - 1; i ++)
        greats.append("great-");
    printGroup(id, greats + "grandchildren", parents, output);
}

void Familytree::printGrandParentsN(Params params, std::ostream &output) const
{
    std::string id = params[0];
    int n = stoi(params.at(1));
    std::string greats = "";
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
    //loop through each grandparent in Nth generation and collect ids
    for (Person* grandParent : getGrandParents(person, n) )
        parents.insert(grandParent->id_);
    //add great- to print function for each generation
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
   output << "Error. " << id <<" not found." << std::endl;
}

void Familytree::printLevelError(std::ostream &output) const
{
   output << "Error. Level can't be less than 1." << std::endl;
}

IdSet Familytree::vectorToIdSet(const std::vector<Person *> &container) const
{
    IdSet set;
    for(Person *person : container){
        set.insert(person->id_);
    }
    return set;
}

void Familytree::printGroup(const std::string &id, const std::string &group,
                const IdSet &container, std::ostream &output) const
{
    if(container.size() == 0){
        output << id << " has no " << group << "." << std::endl;
        return;
    }

    output << id << " has " << container.size() << " " << group << ":" << std::endl;

    for(const std::string& content : container){
        output << content << std::endl;
    }
}

void Familytree::printComparison(const std::string &baseId, const std::string &resultId,
                const std::string &compareParam, const int &height, std::ostream &output) const
{
    if(baseId.compare(resultId) == 0)
        output << "With the height of "<< height << ", " << resultId << " is the "
            << compareParam << " person in his/her lineage."  << std::endl;
    else
        output << "With the height of "<< height << ", " << resultId << " is the "
            << compareParam << " person in "<< baseId << "'s lineage."  << std::endl;

}

std::vector<Person *> Familytree::getGrandChildren(Person *person, int level) const
{
    if(level == 0)
        return person->children_;
    std::vector<Person *> children = {};
    //loop function recursively to get to Nth level children
    for(Person* child : person->children_){
        for(Person* grandChild : getGrandChildren(child, level - 1)){
            children.push_back(grandChild);
        }
    }
    return children;
}

std::vector<Person *> Familytree::getGrandParents(Person *person, int level) const
{
    if(level == 0)
        return person->parents_;
    std::vector<Person *> parents = {};
    //loop function recursively to get to Nth level parents
    for(Person* parent : person->parents_){
        for(Person* grandParent : getGrandParents(parent, level - 1)){
            parents.push_back(grandParent);
        }
    }
    return parents;
}

Person *Familytree::findChildByHeight(Person *person, bool shortest, Person *compareTarget) const
{
    //loop function recursively to find the shortest/tallest child,
    // store current shortest/tallest to compareTarget for each recursion
    for(Person* child : person->children_){
        if(shortest && child->height_ < compareTarget->height_)
            compareTarget = child;
        if(!shortest && child->height_ > compareTarget->height_)
            compareTarget= child;
        compareTarget = findChildByHeight(child, shortest, compareTarget);

    }
    return compareTarget;
}
