#include <iostream>
#include <vector>
#include <set>

using namespace std;

struct Student
{
    string name_;
    string birth_day_;
};

// Prints the given student and preceding text if such is given.
void print(Student* student, const string& pre_text = "")
{
    cout << pre_text;
    if(student)
    {
        cout << student->name_ << " --- " << student->birth_day_ << endl;
    }
    else
    {
        cout << "None" << endl;
    }
}

void find_same(vector<Student*> prog1, vector<Student*> prog2){
    vector<Student*> duplicates = {};
    for(Student* student : prog1){
        if(student != nullptr){
            for(Student* student2 : prog2){
                if(student2 != nullptr && student == student2)
                    duplicates.push_back(student);
            }
        }
    }
    for(Student* student : duplicates){
        print(student,"* Same student in two courses: ");
    }
}

void find_identical(vector<Student*> prog1){
    set<Student*> duplicates = {};
    set<string> displayed = {};
    for(Student* student : prog1){
        if(student != nullptr){
            for(Student* student2 : prog1){
                if(student2 != nullptr && student != student2 && student->name_.compare(student2->name_) == 0 && student->birth_day_.compare(student2->birth_day_) == 0)
                    duplicates.insert(student);
            }
        }
    }
    for(Student* student : duplicates){
        if(displayed.find(student->name_ + student->birth_day_) == displayed.end()){
            print(student,"* Identical students in a course: ");
            displayed.insert(student->name_ + student->birth_day_);
        }
    }
}

Student* find_first_occurrence(string name, string birth_day, vector<Student*> students){
    for(Student* student : students){
        if(student != nullptr && student->name_.compare(name) == 0 && student->birth_day_.compare(birth_day) == 0)
            return student;
    }
    return nullptr;
}

// Don't remove! Needed for tests.
#ifndef POINTERS_TEST
#define POINTERS_TEST
// Don't remove! Needed for tests.

// Main function (an example test case)
int main()
{
    // Students
    Student stud1{"Mortti", "2001-01-01"};
    Student stud2{"Vertti", "2002-02-02"};
    Student stud3{"Mortti", "2001-01-01"};

    // Assigning students to courses
    vector<Student*> prog1 = {nullptr, &stud1, &stud2};
    vector<Student*> prog2 = {&stud1, &stud2, &stud3};
    vector<Student*> prog3 = {&stud1, &stud3};

    // Different seaches
    cout << "Seaching for same students from two different courses" << endl;
    find_same(prog1, prog2);

    cout << endl << "Searching for identical students from a course" << endl;
    find_identical(prog3);

    cout << endl << "Searching for a certain student from a course" << endl;
    Student* wanted = find_first_occurrence("Mortti", "2001-01-01", prog1);
    print(wanted, "* ");
    wanted = find_first_occurrence("Mortti", "2002-02-02", prog1);
    print(wanted, "* ");

    return 0;
}

// Don't remove! Needed for tests.
#endif //POINTERS_TEST
// Don't remove! Needed for tests.
