#include <iostream>
#include <cstring>

using namespace std;

#define MAX_SIZE    (50)

class Person {
    int id; // all members are private by default


    public:

    size_t name_size;
    char *name;

    virtual void about_me()
    {
        cout << "I am a generic person" << endl;
    }

    void static_bound_function()
    {
        cout << "I am Person's Statically bound function." << endl;
    }

    virtual void dynamic_bound_function()
    {
        cout << "I am Person's Dynamically bound function." << endl;
    }

    // The : id(id) will assigns the data member, id, before the rest of the object is created and
    // the rest of the constructor is run
    Person(int i, char *nm, size_t sz) : id(i), name_size(sz)
    {
        if (name_size < MAX_SIZE)
        {
            name = new char[name_size];
            if (name)
            {
                cout << "Creating a Person object with your name" << endl;
                (void)strcpy(name, nm);
            }
        }
        else
        {
            cout << "Your name is too long, cant allocate space for it" << endl;
        }
    }

    virtual ~Person()
    {
        cout <<"Freeing space allocated for Person's Name" << endl;
        delete[] name;
    }
};

class Student : public Person
{
    public:

    void about_me()
    {
        cout << "I am a student, " << name << endl;
    }

    void static_bound_function()
    {
        cout << "I am Students's Statically bound function." << endl;
    }

    void dynamic_bound_function()
    {
        cout << "I am Student's Dynamically bound function." << endl;
    }

    Student(int i, char *nm, size_t sz) : Person(i, nm, sz)
    {
        cout << "Creating a Student object." << endl;
    }

    ~Student()
    {
        cout << "Deleting a Student" << endl;
    }
};

int main(void)
{
    cout << "Review of Classes" << endl;

    char my_name[] = "Caspian";
    Person *p = new Person(10, my_name, strlen(my_name));
    p->about_me();
    p->static_bound_function();
    p->dynamic_bound_function();
    delete p;

    char your_name[] = "Rabbit";
    Person *q = new Student(12, your_name, strlen(your_name));
    q->about_me();
    q->static_bound_function();
    q->dynamic_bound_function();
    delete q;

    char their_name[] = "Abbott";
    Student *r = new Student(12, their_name, strlen(their_name));
    r->about_me();
    r->static_bound_function();
    r->dynamic_bound_function();
    delete r;

    return 0;
}